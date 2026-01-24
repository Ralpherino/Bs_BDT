# BDT

Tested with `lb-conda default/2023-04-26`

## Note:

!Note! This workflow could be ran on the default lxplus environment.
To run workflow:$ sh run_all.sh

## General Overview

This codebase refers to the workings of Alessandro Scarabotto's paper: Test of Lepton Flavor Universality Using Bs semileptonic decays [Thesis](https://cds.cern.ch/record/2724839/).

```
git clone https://gitlab.cern.ch/lhcb-rdshad/BDT.git
cd BDT
sh run_all.sh
```

## Expected Outputs

1. Preparation:
You should expect 3 input files: Input_tmva_Ds.root, Input_tmva_3pi.root, Input_tmva_Bs.root

2. Classification:
You should expect 3 output files: Output_tmva_Ds.root, Output_tmva_3pi.root, Output_tmva_Bs.root

3. Plotting:
   1. Input Variable plot: You should expect a plots directory that contains the 3 output directories that contain the input variables that will be used for training.
   2. BDT plot: You should expect a plots directory that contains the 3 output directories that contain the output from the classification.

** Under construction   
   - Check how to impliment over general purposes not just R(Ds)
   - Impliment over general purposes not just R(Ds)
