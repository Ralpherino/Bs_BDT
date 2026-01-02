// a method to select true events (default is using truth-matching provided by additional script)
//#define bkgcatcut // using BKGCAT cuts 

#include "def_var.h"
#include "def_branch.cc"
#include "def_optcut.cc"

namespace fs = std::filesystem;

void TMVA_input_preparation(string sampletype, vector<string> inputs, string output, vector<string> inputs_weight, string input_bdt){

    if (sampletype != "SIG" && sampletype != "BKG_3pi" && sampletype != "BKG_Ds" && sampletype != "BKG_Ws" && sampletype != "BsNorm" && sampletype != "BdNorm" && sampletype != "data") {
	cout << "sampletype should be one of {SIG, BKG_3pi, BKG_Ds, BKG_Ws, BsNorm, BdNorm, data}!" << endl;
    }
    else {
        cout << "sampletype: " << sampletype << endl;
    }

    // read input tree
    TChain t("DecayTree");
    bool isRead = false;
    for (int i=0; i<inputs.size(); i++) {
	if (!gSystem->AccessPathName((inputs[i]).c_str())) { // file exists
	    cout << "adding " << inputs[i] << endl;
            t.Add((inputs[i]).c_str());
	    isRead = true;
	}
    }
    if (!isRead) {cout << "no file found: terminate" << endl; return;}
    
    // define output names 
    string output_option = "RECREATE";
    string outtree_name = "TreeSig_SIG";
    if (sampletype.substr(0,3) == "BKG") {
	outtree_name = "TreeData_BKG";
	output_option = "UPDATE";
    }
    TFile fout((output).c_str(),(output_option).c_str());

    // define branches to read and save
    branching_in(t, sampletype);
    TTree *tout = new TTree((outtree_name).c_str(),"");
    branching_out(tout, sampletype);

    // read weight file if needed
    bool applyWgt = true;
    int size_weightfile=2;
    if (sampletype == "BsNorm" || sampletype == "BdNorm" || sampletype == "data"){
        size_weightfile = 3;
    }
    for (int i=0; i<size_weightfile; i++) {
	if (gSystem->AccessPathName((inputs_weight[i]+"_BDT.weights.xml").c_str())) { 
	    cout << "missing weight file" << endl; // file does not exist
	    applyWgt = false;
	}
	else {
	    cout << "reading weight file: " << inputs_weight[i] << endl;
	}
    }
    TTree* tout_wgt = new TTree((outtree_name + "_afWgt").c_str(), "");
    TTree* tout_wgt_noBDTcut = new TTree((outtree_name + "_afWgt_noBDTcut").c_str(), "");
    branching_out(tout_wgt, sampletype);
    branching_out(tout_wgt_noBDTcut, sampletype);
    if (applyWgt) {
        tmva_branch(inputs_weight, sampletype);
    } else {
        cout << "No weights applied" << endl;
    }


    // cut definition
    float cut_Xc_MM = 1968; // D mass
    double BDT_3pi_cut = -0.0498; // (optimal cut based on fom, extracted from TMVA::mvaeffs("dataset","Output_tmva_3pi.root",1000,1000,true,"S/sqrt(S+B)"))
    double BDT_Ds_cut = -0.0334; // (optimal cut based on fom, extracted from TMVA::mvaeffs("dataset","Output_tmva_Ds.root",1000,1000,true,"S/sqrt(S+B)"))
    if (!gSystem->AccessPathName((input_bdt+"_3pi.root").c_str())) {
        BDT_3pi_cut = optCut(input_bdt+"_3pi.root", "BDT", "BDT", 1000, 1000);
    }
    if (!gSystem->AccessPathName((input_bdt+"_Ds.root").c_str())) {
        BDT_Ds_cut = optCut(input_bdt+"_Ds.root", "BDT", "BDT", 1000, 1000);
    }
    cout << "BDT_3pi_cut = " << BDT_3pi_cut << ", BDT_Ds_cut = " << BDT_Ds_cut << endl;
 
    // trueid definition for MC samples
    int p2_fromXc_TRUEID_def = 321;
    if (sampletype == "SIG" || sampletype == "BsNorm"){p2_fromXc_TRUEID_def = 321;}
    else if (sampletype == "BdNorm"){p2_fromXc_TRUEID_def = 211;}

    // Define counters
    int signal_after_selection=0;
    int signal_after_BDT=0;

    // Get number of entries
    int n = (int)t.GetEntries();
    cout << "total events: " << n << endl;

    // Loop over events
    for (int e = 0; e < n; e++) {
    //for (int e = 0; e < 1000; e++) {
        t.GetEntry(e);
	if ((e/5000)*5000 == e) cout << "event nr " << e << endl;

        if (eventNumber % 2 == 0) INDEX = 0;
        else INDEX = 1;

    	float factor;
       	if (sampletype == "SIG" || sampletype == "BsNorm" || sampletype == "BdNorm") {
	    factor = 0.6;
	}
       	else {
	    factor = 0;
      	}
	p1_fromXc_TRACK_GhostProb = p1_fromXc_TRACK_GhostProb * exp(factor);
	p2_fromXc_TRACK_GhostProb = p2_fromXc_TRACK_GhostProb * exp(factor);
	p3_fromXc_TRACK_GhostProb = p3_fromXc_TRACK_GhostProb * exp(factor);
       	p1_fromY_TRACK_GhostProb = p1_fromY_TRACK_GhostProb * exp(factor);
	p2_fromY_TRACK_GhostProb = p2_fromY_TRACK_GhostProb * exp(factor);
	p3_fromY_TRACK_GhostProb = p3_fromY_TRACK_GhostProb * exp(factor);

        BDT_3pi = -10;
	BDT_Ds = -10;
        BDT_Bs = -10;
        spec_3pi[0]=(Float_t) B_MM;
        spec_3pi[1]=(Float_t) Xc_MM;
        spec_Ds[0]=(Float_t) B_MM;
        spec_Ds[1]=(Float_t) Xc_MM;
        spec_Bs[0]=(Float_t) B_MM;
        spec_Bs[1]=(Float_t) Xc_MM;

	pass_event = false;
	// left parts for preliminary selection 
	if (sampletype == "SIG" || sampletype == "BsNorm" || sampletype == "BdNorm"){
            if (Xc_Selection == 1) {
#ifdef bkgcatcut
                if (abs(p1_fromXc_TRUEID) == 321 && 
		    abs(p2_fromXc_TRUEID) == p2_fromXc_TRUEID_def &&
		    abs(p3_fromXc_TRUEID) == 211 &&
		    abs(p1_fromY_TRUEID) == 211 &&
		    abs(p2_fromY_TRUEID) == 211 &&
		    abs(p3_fromY_TRUEID) == 211) {
                    if (sampletype == "SIG" && B_BKGCAT == 50 && (Xc_BKGCAT == 0 || Xc_BKGCAT ==50) && Y_BKGCAT == 50) {
                        pass_event = true; 
	            }
		    else if ((sampletype == "BsNorm" || sampletype == "BdNorm") && B_BKGCAT == 10 && Xc_BKGCAT == 0 && (Y_BKGCAT == 20 || Y_BKGCAT == 40)) {
	                pass_event = true; 
	            }
	        }
#else
	        pass_event = true;
#endif
	    }
	}
	else if (sampletype == "BKG_3pi"){
            if (B_MM > 5450 && abs(Xc_MM - cut_Xc_MM)<20){
                pass_event = true;
	    } 
        }
        else if (sampletype == "BKG_Ds"){
	    if (B_MM > 5200 && abs(Xc_MM - 1968) > 30){
	        pass_event = true;
	    }
	}
	else if (sampletype == "BKG_Ws"){
	    if (B_MM > 5300 && abs(Xc_MM - cut_Xc_MM)<20){
	        pass_event = true;
	    }
	}
	else if (sampletype == "data"){
	    pass_event = true;
	}

	// Fill tree output
	if (pass_event){
            signal_after_selection++;
            tout->Fill();
            if (applyWgt) {
		// 3pi
    	        var_3pi[0]=(Float_t)p1_fromY_ETA;
                var_3pi[1]=(Float_t)p2_fromY_ETA;
                var_3pi[2]=(Float_t)p3_fromY_ETA;
                var_3pi[3]=(Float_t)log(p1_fromY_IPCHI2_OWNPV);
                var_3pi[4]=(Float_t)log(p2_fromY_IPCHI2_OWNPV);
                var_3pi[5]=(Float_t)log(p3_fromY_IPCHI2_OWNPV);
                var_3pi[6]=(Float_t)log(p1_fromY_TRACK_GhostProb);
                var_3pi[7]=(Float_t)log(p2_fromY_TRACK_GhostProb);
                var_3pi[8]=(Float_t)log(p3_fromY_TRACK_GhostProb);
                var_3pi[9]=(Float_t)Y_DOCA1;
                var_3pi[10]=(Float_t)Y_DOCA2;
                var_3pi[11]=(Float_t)Y_DOCA3;
                var_3pi[12]=(Float_t)Y_ENDVERTEX_CHI2;
                BDT_3pi = reader_3pi->EvaluateMVA("BDT method");
		// Ds
                var_Ds[0] = log(Xc_ENDVERTEX_CHI2);
                var_Ds[1] = log(Xc_FD_OWNPV);
                var_Ds[2] = log(Xc_FD_ORIVX);
                var_Ds[3] = Xc_ETA;
                var_Ds[4] = log(Xc_PT);
                var_Ds[5] = log(p1_fromXc_IPCHI2_OWNPV);
                var_Ds[6] = log(p2_fromXc_IPCHI2_OWNPV);
                var_Ds[7] = log(p3_fromXc_IPCHI2_OWNPV);
                var_Ds[8] = log(p1_fromXc_PT);
                var_Ds[9] = log(p2_fromXc_PT);
                var_Ds[10]= log(p3_fromXc_PT);
                var_Ds[11]= log(p1_fromXc_TRACK_GhostProb);
                var_Ds[12]= log(p2_fromXc_TRACK_GhostProb);
                var_Ds[13]= log(p3_fromXc_TRACK_GhostProb);
                BDT_Ds = reader_Ds->EvaluateMVA("BDT method");

                if (sampletype == "BsNorm" || sampletype == "BdNorm" || sampletype == "data"){
                    //Bs
                    var_Bs[0]=(Float_t)B_ETA;
                    var_Bs[1]=log(B_FD_OWNPV);
                    var_Bs[2]=(Float_t)BDT_Ds;
                    var_Bs[3]=(Float_t)BDT_3pi;
                    BDT_Bs = reader_Bs->EvaluateMVA("BDT method");
                }
                
                if (BDT_3pi>BDT_3pi_cut && BDT_Ds>BDT_Ds_cut) {
		    signal_after_BDT++;
                    tout_wgt->Fill();
                }
	
                if (sampletype == "BsNorm" || sampletype == "BdNorm" || sampletype == "data") tout_wgt_noBDTcut->Fill();

            } // Applying Weights
        } // Passing Event Selection
    } // Looping over events

    // Print results
    cout << "event number after preliminary selection cuts: " << signal_after_selection << endl;
    cout << "event number after BDT cuts: " << signal_after_BDT << endl;

    fout.cd();
    tout->Write();
    if (applyWgt) {
	tout_wgt->Write();
	if (sampletype == "BsNorm" || sampletype == "BdNorm" || sampletype == "data") {
	    tout_wgt_noBDTcut->Write();
	}
    }
    fout.Close();

} // end of main function 
