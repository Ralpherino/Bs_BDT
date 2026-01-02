# This script is used to plot the output of the BDT implemented for the 3pi, Ds, B selection.
# It produces: (a) BDT variable distributions from training, (b) efficiency curves with optimal cut.

import numpy as np
import uproot
from matplotlib import pyplot as plt
from matplotlib.offsetbox import AnchoredText
import argparse
import os

def parse_args():
    '''Parse command-line arguments for input ROOT file and output plot path.'''
    parser = argparse.ArgumentParser(description="Plot BDT output for 3pi selection.")
    parser.add_argument('--input', required=True, help="Input file prepared for TMVA Classification.")
    parser.add_argument('--nch1', required=True, help='Normalization channel 1 ROOT file')
    parser.add_argument('--nch2', required=True, help='Normalization channel 2 ROOT file')
    parser.add_argument('--selection', required=True, choices=['3pi', 'Ds', 'Bs'], help="Selection type")
    parser.add_argument('--outdir', required=True, help="Output directory for plots")
    return parser.parse_args()

def get_hist_data(hist):
    '''Extract bin edges and bin contents from a histogram object.'''
    bin_edges = hist.axis().edges()
    bin_contents = hist.values()
    return bin_edges, bin_contents

def normalize_hist(bin_edges, bin_contents):
    '''Normalize a histogram so that its area is 1.'''
    bin_widths = np.diff(bin_edges)
    total = np.sum(bin_contents * bin_widths)
    if total > 0:
        bin_contents = bin_contents / total
    return bin_contents

def main():
    '''Main function to load data, plot BDT output, and save the plot to the specified file.'''
    args = parse_args()
    os.makedirs(args.outdir, exist_ok=True)

    tmva_file = uproot.open(args.input)
    norm_ch1_file = uproot.open(args.nch1)
    norm_ch2_file = uproot.open(args.nch2)

    # Histogram paths inside TMVA file
    signal_path = "dataset/Method_BDT/BDT/MVA_BDT_S"
    background_path = "dataset/Method_BDT/BDT/MVA_BDT_B"
    effS_path = "dataset/Method_BDT/BDT/MVA_BDT_effS"
    effB_path = "dataset/Method_BDT/BDT/MVA_BDT_effB"

    # Get the trees from normalization channel root files
    if args.selection == 'Bs':
        norm_ch1_tree = norm_ch1_file["TreeSig_SIG_afWgt"]
        norm_ch2_tree = norm_ch2_file["TreeSig_SIG_afWgt"]
    else:
        norm_ch1_tree = norm_ch1_file["TreeSig_SIG_afWgt_noBDTcut"]
        norm_ch2_tree = norm_ch2_file["TreeSig_SIG_afWgt_noBDTcut"]

    # Reat BDT data from normalization channel trees
    norm_ch1_data = norm_ch1_tree[f"BDT_{args.selection}"].array(library="np")
    norm_ch2_data = norm_ch2_tree[f"BDT_{args.selection}"].array(library="np")

    # Remove NaN values (if any)
    norm_ch1_data = norm_ch1_data[~np.isnan(norm_ch1_data)]
    norm_ch2_data = norm_ch2_data[~np.isnan(norm_ch2_data)]

    # Load and normalize histograms
    signal_hist = tmva_file[signal_path]
    background_hist = tmva_file[background_path]
    bin_edges_sig, bin_contents_sig = get_hist_data(signal_hist)
    bin_edges_bkg, bin_contents_bkg = get_hist_data(background_hist)
    bin_contents_sig = normalize_hist(bin_edges_sig, bin_contents_sig)
    bin_contents_bkg = normalize_hist(bin_edges_bkg, bin_contents_bkg)

    # Create histograms for normalization channels using the same bins as TMVA
    bin_contents_ch1, _ = np.histogram(norm_ch1_data, bins=bin_edges_sig, density=True)
    bin_contents_ch2, _ = np.histogram(norm_ch2_data, bins=bin_edges_sig, density=True)

    # Load efficiency histograms
    effS = tmva_file[effS_path]
    effB = tmva_file[effB_path]
    bin_edges_effS = effS.axis().edges()
    values_effS = effS.values()
    bin_edges_effB = effB.axis().edges()
    values_effB = effB.values()

    # Calculate optimal cut
    bin_centers = 0.5 * (bin_edges_effS[:-1] + bin_edges_effS[1:])
    if args.selection == "3pi" or args.selection == "Ds":
        target = 0.95
    else:
        target = 0.9
    opt_idx = np.argmin(np.abs(values_effS - target))
    optimal_cut = bin_centers[opt_idx]
    eff_sig = values_effS[opt_idx]
    eff_bkg = values_effB[opt_idx]

    # Plot
    fig, axs = plt.subplots(1, 2, figsize=(14, 6))

    # (a) BDT variable distributions
    ax = axs[0]
    ax.step(bin_edges_sig[:-1], bin_contents_sig, where='post', color='black', linewidth=1.5, label='Signal')
    ax.step(bin_edges_bkg[:-1], bin_contents_bkg, where='post', color='red', linewidth=1.5, linestyle='--', label='Background')
    ax.step(bin_edges_sig[:-1], bin_contents_ch1, where='post', linewidth=1.5, color='green', label='Normalization Channel 1')
    ax.step(bin_edges_sig[:-1], bin_contents_ch2, where='post', linewidth=1.5, color='blue', label='Normalization Channel 2')

    ax.set_xlabel(f"BDT_{args.selection}")
    ax.set_ylabel(r'$(1/N)\ dN/dx$')
    ax.set_title(f"{args.selection}")
    ax.grid(True, alpha=0.3)
    ax.legend()

    # (b) Efficiency curves and optimal cut
    ax = axs[1]
    ax.step(bin_edges_effS[:-1], values_effS, where='post', color='blue', label=f'eff. sig: {eff_sig:.6f}')
    ax.step(bin_edges_effB[:-1], values_effB, where='post', color='red', label=f'eff. bkg: {eff_bkg:.6f}')
    ax.axvline(optimal_cut, color='black', linestyle='-', linewidth=1, label=f'Optimal cut: {optimal_cut:.6f}')
    ax.set_xlabel("BDT output")
    ax.set_ylabel("Efficiency")
    ax.set_title("Cut efficiencies and optimal cut value")
    ax.legend()
    ax.grid(True, alpha=0.3)

    # Save
    out_dir = args.outdir
    os.makedirs(out_dir, exist_ok=True)

    outfile = os.path.join(out_dir, f"{args.selection}_BDT_plots.png")
    plt.savefig(outfile)
    plt.close()

if __name__ == "__main__":
    main()
