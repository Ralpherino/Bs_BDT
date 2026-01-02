# This script is used to plot the variables used to train the BDT for the 3pi, Ds or B selection (based on your preference).
# The black, green and blue distributions represent respectively the MC samples of Bs -> Ds-tau+ (signal)
# Bd -> D3pi and Bs -> Ds3pi (normalization channels). The red distribution shows the
# Bs data sample with m(Bs) > 5450 MeV/c^2.

# Importing
import numpy as np
import uproot
from matplotlib import pyplot as plt
import pandas as pd
import argparse
import os

# -------------------------------
# Input variables by selection
# -------------------------------
pi3_input_variables = [
    'p1_fromY_ETA', 'p2_fromY_ETA', 'p3_fromY_ETA',
    'Y_DOCA1', 'Y_DOCA2', 'Y_DOCA3',
    'Y_ENDVERTEX_CHI2',
    'p1_fromY_IPCHI2_OWNPV', 'p2_fromY_IPCHI2_OWNPV', 'p3_fromY_IPCHI2_OWNPV',
    'p1_fromY_TRACK_GhostProb', 'p2_fromY_TRACK_GhostProb', 'p3_fromY_TRACK_GhostProb']

Ds_input_variables = [
    'Xc_ENDVERTEX_CHI2', 'Xc_FD_OWNPV', "Xc_FD_ORIVX", "Xc_ETA",
    'p1_fromXc_IPCHI2_OWNPV', 'p2_fromXc_IPCHI2_OWNPV', 'p3_fromXc_IPCHI2_OWNPV',
    'p1_fromXc_TRACK_GhostProb', 'p2_fromXc_TRACK_GhostProb', 'p3_fromXc_TRACK_GhostProb',
    'p1_fromXc_PT', 'p2_fromXc_PT', 'p3_fromXc_PT']

Bs_input_variables = [
    'B_ETA', 'B_FD_OWNPV', 'BDT_Ds', 'BDT_3pi']

def parse_args():
    """Parses command-line arguments for input ROOT files, selection type, and output directory."""
    parser = argparse.ArgumentParser(description="Plot TMVA input variables")
    parser.add_argument('--input', required=True, help="Base selection ROOT file")
    parser.add_argument('--nch1', required=False, help="Normalization channel 1 (BdNorm)")
    parser.add_argument('--nch2', required=False, help="Normalization channel 2 (BsNorm)")
    parser.add_argument('--selection', required=True, choices=['3pi','Ds','Bs'], help="Selection type")
    parser.add_argument('--outdir', default='plots', help="Output directory for plots")
    return parser.parse_args()

def open_tree(file_path, selection):
    """Opens the specified ROOT file and returns the appropriate signal and background trees based on the selection type."""
    f = uproot.open(file_path)
    if selection == 'Bs':
        return f["TreeSig_SIG_afWgt"], f["TreeData_BKG_afWgt"]
    else:
        return f["TreeSig_SIG"], f["TreeData_BKG"]

def get_variables(selection):
    """Returns the list of input variables required for the given BDT selection."""
    if selection == '3pi':
        return pi3_input_variables
    elif selection == 'Ds':
        return Ds_input_variables
    elif selection == 'Bs':
        return Bs_input_variables

def plot_variable(ax, data, bins, label, color):
    """Helper function to plot a normalized histogram on a given matplotlib axes, provided the data is not empty."""
    if len(data) > 0:
        hist, edges = np.histogram(data, bins=bins, density=True)
        ax.step(edges[:-1], hist, where='post', color=color, label=label, linewidth=1.5)

def get_variable_config(selection, var):
    """Determine if log-transform and/or limits are needed for each variable. 
       return var(variable), True/False(apply log), None or set limits"""
    # 3pi
    if selection == '3pi':
        if 'Y_DOCA' in var:
            return var, False, (0, 0.155)
        elif '_fromY_IPCHI2_OWNPV' in var or '_fromY_TRACK_GhostProb' in var:
            return var, True, None
        elif '_fromY_ETA' in var or 'Y_ENDVERTEX_CHI2' in var:
            return var, False, None

    # Ds
    if selection == 'Ds':
        if 'Xc_FD_ORIVX' in var or 'Xc_FD_OWNPV' in var or '_fromXc_IPCHI2_OWNPV' in var \
            or '_fromXc_TRACK_GhostProb' in var or '_fromXc_PT' in var:
            return var, True, None
        elif 'Xc_ENDVERTEX_CHI2' in var or 'Xc_ETA' in var:
            return var, False, None

    # Bs
    if selection == 'Bs':
        if 'B_ETA' in var or 'BDT_Ds' in var or 'BDT_3pi' in var:
            return var, False, None
        elif 'B_FD_OWNPV' in var:
            return var, True, None
    return var, False, None

def main():
    """The main function that orchestrates the plotting process. It loads data, loops through variables, transforms data as needed, 
    generates and saves a plot for each variable."""
    args = parse_args()
    os.makedirs(args.outdir, exist_ok=True)

    # Load TMVA trees as pandas DataFrames
    sig_tree, bkg_tree = open_tree(args.input, args.selection)
    df_sig = sig_tree.arrays(get_variables(args.selection), library="pd")
    df_bkg = bkg_tree.arrays(get_variables(args.selection), library="pd")
    if args.selection == 'Bs':
        df_ch1 = uproot.open(args.nch1)["TreeSig_SIG_afWgt"].arrays(get_variables(args.selection), library="pd")
        df_ch2 = uproot.open(args.nch2)["TreeSig_SIG_afWgt"].arrays(get_variables(args.selection), library="pd")
    else:
        df_ch1 = uproot.open(args.nch1)["TreeSig_SIG_afWgt_noBDTcut"].arrays(get_variables(args.selection), library="pd")
        df_ch2 = uproot.open(args.nch2)["TreeSig_SIG_afWgt_noBDTcut"].arrays(get_variables(args.selection), library="pd")

    # Loop over variables
    for var in get_variables(args.selection):
        fig, ax = plt.subplots(figsize=(7,5))
        var_name, log_transform, x_limits = get_variable_config(args.selection, var)

        sig_data = df_sig[var].to_numpy()
        bkg_data = df_bkg[var].to_numpy()
        ch1_data = df_ch1[var].to_numpy()
        ch2_data = df_ch2[var].to_numpy()

        if log_transform:
            sig_data = sig_data[sig_data > 0]
            bkg_data = bkg_data[bkg_data > 0]
            ch1_data = ch1_data[ch1_data > 0]
            ch2_data = ch2_data[ch2_data > 0]
            sig_data = np.log(sig_data)
            bkg_data = np.log(bkg_data)
            ch1_data = np.log(ch1_data)
            ch2_data = np.log(ch2_data)

        # Determine x-limits automatically if not fixed
        all_data = []
        if len(sig_data) > 0: all_data.append(sig_data)
        if len(bkg_data) > 0: all_data.append(bkg_data)
        if len(ch1_data) > 0: all_data.append(ch1_data)
        if len(ch2_data) > 0: all_data.append(ch2_data)

        if x_limits is None:
            if not all_data:
                print(f"Warning: No valid data for '{var_name}'. Skipping plot.")
                plt.close(fig)
                continue
            all_data = np.concatenate(all_data)
            xmin, xmax = np.min(all_data), np.max(all_data)
            margin = 0.05*(xmax - xmin)
            xmin -= margin
            xmax += margin
        else:
            xmin, xmax = x_limits

        bins = np.linspace(xmin, xmax, 51)

        # Plot each component, only if the data is not empty
        plot_variable(ax, sig_data, bins, "Signal", "black")
        plot_variable(ax, bkg_data, bins, "Background", "red")
        plot_variable(ax, ch1_data, bins, "BsNorm", "green")
        plot_variable(ax, ch2_data, bins, "BdNorm", "blue")

        ax.set_ylabel(r'$(1/N)\ dN/dx$')

        # Adjust title to reflect log transformation
        if log_transform:
            ax.set_xlabel(f'log({var_name})')
        else:
            ax.set_xlabel(var_name)

        ax.grid(True, alpha=0.3)
        ax.legend()
        plt.tight_layout()

        # Determine the file name (if or not log transform)
        filename = f"{var_name}.png"
        if log_transform:
            filename = f"log({var_name}).png"
            
        plt.savefig(os.path.join(args.outdir, filename))
        plt.close(fig)

if __name__ == "__main__":
    main()
