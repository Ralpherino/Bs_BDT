#include "TMVA_input_preparation.cc"
//#include "TMVAClassification.cc"

void rds_BDT_inputs(string selection, vector<string> inputs_sig, vector<string> inputs_bkgrs, vector<string> inputs_bkgws, string output, vector<string> inputs_weight, string input_bdt) {
    //string output_dir = "./output/";
    //gSystem->Exec(("mkdir -p " + output_dir).c_str());

    if (selection == "3pi") {
      // BDT 3pi
      // TMVA_input_preparation(sample type, input, output, weight input if need)
      TMVA_input_preparation("SIG", inputs_sig, output, inputs_weight, input_bdt); 
      TMVA_input_preparation("BKG_3pi", inputs_bkgrs, output, inputs_weight, input_bdt);
      // TMVAClassification(selection type, input, output, weight output, TMVA method)
      //TMVAClassification(selection, output, output_dir+"Output_tmva_"+selection, "TMVAClassification_"+selection, "BDT"); 
    }
    else if (selection == "Ds") {
      // BDT Ds
      // TMVA_input_preparation(sample type, input, output, weight input if need)
      TMVA_input_preparation("SIG", inputs_sig, output, inputs_weight, input_bdt); 
      TMVA_input_preparation("BKG_Ds", inputs_bkgrs, output, inputs_weight, input_bdt);
      //TMVAClassification(selection, output, output_dir+"Output_tmva_"+selection, "TMVAClassification_"+selection, "BDT"); 
    }
    else if (selection == "Bs") {
      if (gSystem->AccessPathName((input_bdt+"_3pi.root").c_str())) {
        cout << "no " << input_bdt << "_3pi.root file found: terminate" << endl;
        return;
      }
      if (gSystem->AccessPathName((input_bdt+"_Ds.root").c_str())) {
        cout << "no " << input_bdt << "_Ds.root file found: terminate" << endl;
        return;
      }
      // BDT Bs
      // TMVA_input_preparation(sample type, input, output, weight input if need)
      TMVA_input_preparation("SIG", inputs_sig, output, inputs_weight, input_bdt); 
      TMVA_input_preparation("BKG_3pi", inputs_bkgrs, output, inputs_weight, input_bdt);
      TMVA_input_preparation("BKG_Ws", inputs_bkgws, output, inputs_weight, input_bdt);
      //TMVAClassification(selection, output, output_dir+"Output_tmva_"+selection, "TMVAClassification_"+selection, "BDT"); 
    }
    else if (selection == "BsNorm") {
      // Bs Norm
      // TMVA_input_preparation(sample type, input, output, weight input if need)
      TMVA_input_preparation("BsNorm", inputs_sig, output, inputs_weight, input_bdt); 
    }    
    else if (selection == "BdNorm") {
      // Bd Norm
      // TMVA_input_preparation(sample type, input, output, weight input if need)
      TMVA_input_preparation("BdNorm", inputs_sig, output, inputs_weight, input_bdt); 
    }
    else if (selection == "data") {
      TMVA_input_preparation("BdNorm", inputs_sig, output, inputs_weight, input_bdt); 
    }
    else {cout << "cannot find selection type: nothing to be done" << endl;}

    gROOT->ProcessLine(".q");

}	
