#include "TMVA_input_preparation.cc"
//#include "TMVAClassification.cc"

void rds_data_BDTwgt() {

    vector<string> inputs_sig = {"/eos/lhcb/wg/semileptonic/RDsHad/AP/v2/ap_moreinfopid/rds_preprocess_lhcb_2012_90000000_magup_rs.root", 
	                         "/eos/lhcb/wg/semileptonic/RDsHad/AP/v2/ap_moreinfopid/rds_preprocess_lhcb_2012_90000000_magdown_rs.root"};
    string output = "../output/rds_preprocess_lhcb_2012_90000000_rs_afWgt.root";
    vector<string> inputs_weight = {"../dataset/weights/TMVAClassification_3pi", "../dataset/weights/TMVAClassification_Ds", "../dataset/weights/TMVAClassification_Bs"};
    string input_bdt = "../output/Output_tmva";

    TMVA_input_preparation("data", inputs_sig, output, inputs_weight, input_bdt); 

    gROOT->ProcessLine(".q");

}	
