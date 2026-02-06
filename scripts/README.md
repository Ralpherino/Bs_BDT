# Scripts directory

### 1. def_var.h
This script defines the branches (variables) used for preparing the input root files that will be trained.

### 2. def_branch.cc
This script adds the branches to their respective root files.

### 3. TMVA_input_preparation.cc
This script prepares the input files that will be used for training. Normalization channel root files will also be generated to reduce systematic uncertainty. They have similar topology as the signal samples. The expected outputs will be found in the output directory as Input_tmva_{selection}.root or Input_tmva_{B*_norm}.root

### 4. TMVAClassification.cc
This script uses a TMVA (Toolkit for Multivariate Data Analysis) to help distinguish between signal and background. The expected outputs are found in the output directory as Output_tmva_{selection}.root

### 5. rds_BDT_inputs.cc
This script is to follow the analysis flow to run the preparation script for the 3 selections (Ds, 3pi and Bs). It is used to collect the signal and background samples into 1 file. 

### 6. variables_plot.py
This script plots the input variables selected for the TMVA.

### 7. bdt_plot.py

This script is used to plot the final BDT outputs for the corresponding selections (Ouput root files + normalization channel root files)

### 8. def_optcut.cc

This script determines and stores the working-pint cuts for each selection (Ds, 3pi, Bs)

### 9. rds_data_BDTwgt.cc

This script applies the trained TMVA model to the samples and writes out a ROOT tree with the BDT response added as a new branch. 
