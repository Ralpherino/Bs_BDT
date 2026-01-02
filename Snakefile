# configfile: "path/to/config/file"
configfile: "config/config.json"

indir_sig = os.path.abspath(config["IN_DIR_SIG"])
indir_bkg = os.path.abspath(config["IN_DIR_BKG"])
outdir = os.path.abspath(config["OUT_DIR"])
input_plots = os.path.abspath(config["INPUT_PLOTS"])
bdt_plots = os.path.abspath(config["BDT_PLOTS"])

# Important directories
dir_script = "scripts"
dir_log = "log"
dir_weight=f"dataset/weights"
weight="TMVAClassification"

wildcard_constraints:
    selection="(3pi|Ds|Bs|BsNorm|BdNorm)"

# Dependency mapping
deps = {
    "3pi" : [],
    "Ds": ["3pi"], # not related with analysis flow, just to save running time
    "Bs": ["3pi", "Ds"],
    "BsNorm": ["3pi", "Ds", "Bs"],
    "BdNorm": ["3pi", "Ds", "Bs", "BsNorm"], # here "BsNorm" is not related with analysis flow, just to save running time
    "plots": ["3pi", "Ds", "Bs", "BsNorm", "BdNorm"]
}

def get_targets(sel):
    if sel not in ["BsNorm", "BdNorm"]:
        return f"{outdir}/Output_tmva_{sel}.root" 
    else:
        return f"{outdir}/Input_tmva_{sel}.root"

def collect_all_targets(sel):
    targets = []
    for dep in deps.get(sel, []):
        #print(f"sel:{sel}, dep:{dep}")
        targets += collect_all_targets(dep)
    if (sel=="plots"):
        targets += [ f"{input_plots}/{plt_sel}_input_var_plots" for plt_sel in ["3pi", "Ds", "Bs"] ]
        targets += [ f"{bdt_plots}/{plt_sel}_BDT_plots" for plt_sel in ["3pi", "Ds", "Bs"] ]
    else:
        targets.append(get_targets(sel))
    return list(dict.fromkeys(targets))

def get_requested_selection():
    sel = config.get("selection")
    if not sel:
        raise ValueError(
            "To pass the selection on the command line kindly run using the following command:\n"
            "snakemake --cores <n> --config selection=<type>"
        )
    return sel

def str_input(w):
    pre = "rds_preprocess"
    config = "mc"
    year = "2012"
    eventtype = "13563002"
    sign = "rs"

    if w.selection == "BsNorm":
        eventtype = "13266069"
        sign = "None"

    elif w.selection == "BdNorm":
        eventtype = "11266009"
        sign = "None"

    sig_up=f"{indir_sig}/{pre}_{config}_{year}_{eventtype}_magup_{sign}.root"
    sig_dw=f"{indir_sig}/{pre}_{config}_{year}_{eventtype}_magdown_{sign}.root"
    pre = "rds_background"
    config = "lhcb"
    eventtype = "90000000"

    bkgrs_up=f"{indir_bkg}/{pre}_{config}_{year}_{eventtype}_magup_rs.root"
    bkgrs_dw=f"{indir_bkg}/{pre}_{config}_{year}_{eventtype}_magdown_rs.root"
    bkgws_up=f"{indir_bkg}/{pre}_{config}_{year}_{eventtype}_magup_ws.root"
    bkgws_dw=f"{indir_bkg}/{pre}_{config}_{year}_{eventtype}_magdown_ws.root"
    return sig_up, sig_dw, bkgrs_up, bkgrs_dw, bkgws_up, bkgws_dw

# This function provides inputs for the initial variable plots.
def plot_input_files(w):
    base = f"{outdir}/Input_tmva_{w.selection}.root"
    nch1 = f"{outdir}/Input_tmva_BdNorm.root"
    nch2 = f"{outdir}/Input_tmva_BsNorm.root"    
    return [base, nch1, nch2]

# This function provides inputs for the BDT output plots.
def plot_bdt_files(w):
    base = f"{outdir}/Output_tmva_{w.selection}.root"
    nch1 = f"{outdir}/Input_tmva_BdNorm.root"
    nch2 = f"{outdir}/Input_tmva_BsNorm.root"
    return [base, nch1, nch2]

# The main entry point for the workflow.
rule all:
    input:
        lambda wildcards: collect_all_targets(get_requested_selection())

rule prepare_bdt:
    input:
        lambda wildcards: str_input(wildcards)
    output:
        f"{outdir}/Input_tmva_{{selection}}.root"
    log:
        f"{dir_log}/prepare_bdt_{{selection}}.log"
    shell:
        'root -l -b \'{dir_script}/rds_BDT_inputs.cc("{wildcards.selection}", {{"{input[0]}", "{input[1]}"}}, {{"{input[2]}", "{input[3]}"}}, {{"{input[4]}", "{input[5]}"}}, "{output}", {{"{dir_weight}/{weight}_3pi", "{dir_weight}/{weight}_Ds", "{dir_weight}/{weight}_Bs"}}, "{outdir}/Output_tmva")\' | tee {log}'

rule run_bdt:
    input:
        f"{outdir}/Input_tmva_{{selection}}.root"
    output:
        f"{outdir}/Output_tmva_{{selection}}.root"
    log:
        f"{dir_log}/run_bdt_{{selection}}.log"
    shell:
        'root -l -b \'{dir_script}/TMVAClassification.cc("{wildcards.selection}", "{input}", "{output}", "{weight}_{wildcards.selection}", "BDT,BDTG")\' | tee {log}'

rule input_plots:
    input:
        lambda wildcards: plot_input_files(wildcards)
    output:
        directory(f"{input_plots}/{{selection}}_input_var_plots")
    log:
        f"{dir_log}/{{selection}}_input_plots.log"
    shell:
        """
        if [ -n "{input}" ]; then
            python scripts/variables_plot.py \
                --input {input[0]} \
                --nch1 {input[1]} \
                --nch2 {input[2]} \
                --selection {wildcards.selection} \
                --outdir {input_plots}/{wildcards.selection}_input_var_plots \
                &> {log}
        else
            echo "Skipping input variable plots for {wildcards.selection}" > {log}
        fi
        """

rule bdt_plots:
    input:
        lambda wildcards: plot_bdt_files(wildcards)
    output:
        directory(f"{bdt_plots}/{{selection}}_BDT_plots")
    log:
        f"{dir_log}/{{selection}}_BDT_plots.log"
    shell:
      """
      if [ -n "{input}" ]; then
          python scripts/bdt_plot.py \
              --input {input[0]} \
              --nch1 {input[1]} \
              --nch2 {input[2]} \
              --selection {wildcards.selection} \
              --outdir {bdt_plots}/{wildcards.selection}_BDT_plots \
              &> {log}
      else
          echo "Skipping BDT plots for {wildcards.selection}" > {log}
      fi
      """
