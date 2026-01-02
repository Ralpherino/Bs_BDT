void branching_in(TChain &t, string sampletype) {
// Add any other additional variables following this pattern.
// Example format:
// t.SetBranchAddress("branch_name_in_tree", &variable);

    // Mass variables
    t.SetBranchAddress("B_MM", &B_MM);
    t.SetBranchAddress("Xc_MM", &Xc_MM);

    if (sampletype == "SIG" || sampletype == "BsNorm" || sampletype == "BdNorm"){

    // TRUEIDs MC

    t.SetBranchAddress("p1_fromXc_TRUEID", &p1_fromXc_TRUEID);
    t.SetBranchAddress("p2_fromXc_TRUEID", &p2_fromXc_TRUEID);
    t.SetBranchAddress("p3_fromXc_TRUEID", &p3_fromXc_TRUEID);

    t.SetBranchAddress("p1_fromY_TRUEID", &p1_fromY_TRUEID);
    t.SetBranchAddress("p2_fromY_TRUEID", &p2_fromY_TRUEID);
    t.SetBranchAddress("p3_fromY_TRUEID", &p3_fromY_TRUEID);

    t.SetBranchAddress("Xc_TRUEID", &Xc_TRUEID);

    // BKGCAT flags

    t.SetBranchAddress("B_BKGCAT", &B_BKGCAT);
    t.SetBranchAddress("Xc_BKGCAT", &Xc_BKGCAT);
    t.SetBranchAddress("Y_BKGCAT", &Y_BKGCAT);

    // preliminary selection flag
    t.SetBranchAddress("Xc_Selection", &Xc_Selection);
    }
    // Does not need to be stored in output file ^^

    // Xc daughters (p1, p2, p3) kinematics

    t.SetBranchAddress("p1_fromXc_PT", &p1_fromXc_PT);
    t.SetBranchAddress("p2_fromXc_PT", &p2_fromXc_PT);
    t.SetBranchAddress("p3_fromXc_PT", &p3_fromXc_PT);
    t.SetBranchAddress("p1_fromXc_PE", &p1_fromXc_PE);
    t.SetBranchAddress("p1_fromXc_PX", &p1_fromXc_PX);
    t.SetBranchAddress("p1_fromXc_PY", &p1_fromXc_PY);
    t.SetBranchAddress("p1_fromXc_PZ", &p1_fromXc_PZ);
    t.SetBranchAddress("p2_fromXc_PE", &p2_fromXc_PE);
    t.SetBranchAddress("p2_fromXc_PX", &p2_fromXc_PX);
    t.SetBranchAddress("p2_fromXc_PY", &p2_fromXc_PY);
    t.SetBranchAddress("p2_fromXc_PZ", &p2_fromXc_PZ);
    t.SetBranchAddress("p3_fromXc_PE", &p3_fromXc_PE);
    t.SetBranchAddress("p3_fromXc_PX", &p3_fromXc_PX);
    t.SetBranchAddress("p3_fromXc_PY", &p3_fromXc_PY);
    t.SetBranchAddress("p3_fromXc_PZ", &p3_fromXc_PZ);

    // Xc daughters PID

    t.SetBranchAddress("p1_fromXc_PIDK", &p1_fromXc_PIDK);
    t.SetBranchAddress("p1_fromXc_PIDp", &p1_fromXc_PIDp);
    t.SetBranchAddress("p2_fromXc_PIDK", &p2_fromXc_PIDK);
    t.SetBranchAddress("p2_fromXc_PIDp", &p2_fromXc_PIDp);
    t.SetBranchAddress("p3_fromXc_PIDK", &p3_fromXc_PIDK);
    t.SetBranchAddress("p3_fromXc_PIDp", &p3_fromXc_PIDp);

    // Xc vertexing 

    t.SetBranchAddress("Xc_DOCA1", &Xc_DOCA1);
    t.SetBranchAddress("Xc_DOCA2", &Xc_DOCA2);
    t.SetBranchAddress("Xc_DOCA3", &Xc_DOCA3);
    t.SetBranchAddress("Xc_ENDVERTEX_CHI2", &Xc_ENDVERTEX_CHI2);

    // Y daughters (p1, p2, p3) kinematics

    t.SetBranchAddress("p1_fromY_P", &p1_fromY_P);
    t.SetBranchAddress("p2_fromY_P", &p2_fromY_P);
    t.SetBranchAddress("p3_fromY_P", &p3_fromY_P);
    t.SetBranchAddress("p1_fromY_PT", &p1_fromY_PT);
    t.SetBranchAddress("p2_fromY_PT", &p2_fromY_PT);
    t.SetBranchAddress("p3_fromY_PT", &p3_fromY_PT);

    // Y DOCA and vertexing

    t.SetBranchAddress("Y_DOCA1", &Y_DOCA1);
    t.SetBranchAddress("Y_DOCA2", &Y_DOCA2);
    t.SetBranchAddress("Y_DOCA3", &Y_DOCA3);
    t.SetBranchAddress("Y_ENDVERTEX_CHI2", &Y_ENDVERTEX_CHI2);

    // Y eta

    t.SetBranchAddress("Y_ETA", &Y_ETA);
    t.SetBranchAddress("p1_fromY_ETA", &p1_fromY_ETA);
    t.SetBranchAddress("p2_fromY_ETA", &p2_fromY_ETA);
    t.SetBranchAddress("p3_fromY_ETA", &p3_fromY_ETA);

    // Xc eta

    t.SetBranchAddress("Xc_ETA", &Xc_ETA);

    // B eta
    t.SetBranchAddress("B_ETA", &B_ETA);

    // Event info

    t.SetBranchAddress("eventNumber", &eventNumber);

    // Primary vertex info
    // Y_*_OWNPV
    t.SetBranchAddress("Y_IP_OWNPV", &Y_IP_OWNPV);
    t.SetBranchAddress("Y_IPCHI2_OWNPV", &Y_IPCHI2_OWNPV);
    t.SetBranchAddress("p1_fromY_IPCHI2_OWNPV", &p1_fromY_IPCHI2_OWNPV);
    t.SetBranchAddress("p2_fromY_IPCHI2_OWNPV", &p2_fromY_IPCHI2_OWNPV);
    t.SetBranchAddress("p3_fromY_IPCHI2_OWNPV", &p3_fromY_IPCHI2_OWNPV);

    // Xc_*_OWNPV
    t.SetBranchAddress("p1_fromXc_IPCHI2_OWNPV", &p1_fromXc_IPCHI2_OWNPV);
    t.SetBranchAddress("p2_fromXc_IPCHI2_OWNPV", &p2_fromXc_IPCHI2_OWNPV);
    t.SetBranchAddress("p3_fromXc_IPCHI2_OWNPV", &p3_fromXc_IPCHI2_OWNPV);
    t.SetBranchAddress("Xc_FD_OWNPV", &Xc_FD_OWNPV);
    t.SetBranchAddress("Xc_FD_ORIVX", &Xc_FD_ORIVX);

    // B_*_OWNPV
    t.SetBranchAddress("B_FD_OWNPV", &B_FD_OWNPV);

    // Ghost probabilities

    t.SetBranchAddress("p1_fromY_TRACK_GhostProb", &p1_fromY_TRACK_GhostProb);
    t.SetBranchAddress("p2_fromY_TRACK_GhostProb", &p2_fromY_TRACK_GhostProb);
    t.SetBranchAddress("p3_fromY_TRACK_GhostProb", &p3_fromY_TRACK_GhostProb);

    t.SetBranchAddress("p1_fromXc_TRACK_GhostProb", &p1_fromXc_TRACK_GhostProb);
    t.SetBranchAddress("p2_fromXc_TRACK_GhostProb", &p2_fromXc_TRACK_GhostProb);
    t.SetBranchAddress("p3_fromXc_TRACK_GhostProb", &p3_fromXc_TRACK_GhostProb);

    // Other event variables

    t.SetBranchAddress("Xc_PT", &Xc_PT);
    t.SetBranchAddress("Y_MINIPCHI2NEXTBEST", &Y_MINIPCHI2NEXTBEST);
    t.SetBranchAddress("nPV", &nPV);

}
void branching_out(TTree *tout, string sampletype) {
// Add any other additional variables following this pattern.
// Example format:
// tout->Branch("branch_name_in_tree", &variable);

    // Mass variables

    tout->Branch("B_MM", &B_MM); 
    tout->Branch("Xc_MM", &Xc_MM);

    if (sampletype == "SIG" || sampletype == "BsNorm" || sampletype == "BdNorm"){

    // preliminary selection flag
    tout->Branch("Xc_Selection", &Xc_Selection);
    }
    // Does not need to be stored in output file ^^

    // Xc daughters (p1, p2, p3) kinematics

    tout->Branch("p1_fromXc_PT", &p1_fromXc_PT);
    tout->Branch("p2_fromXc_PT", &p2_fromXc_PT);
    tout->Branch("p3_fromXc_PT", &p3_fromXc_PT);
    tout->Branch("p1_fromXc_PE", &p1_fromXc_PE);
    tout->Branch("p1_fromXc_PX", &p1_fromXc_PX);
    tout->Branch("p1_fromXc_PY", &p1_fromXc_PY);
    tout->Branch("p1_fromXc_PZ", &p1_fromXc_PZ);
    tout->Branch("p2_fromXc_PE", &p2_fromXc_PE);
    tout->Branch("p2_fromXc_PX", &p2_fromXc_PX);
    tout->Branch("p2_fromXc_PY", &p2_fromXc_PY);
    tout->Branch("p2_fromXc_PZ", &p2_fromXc_PZ);
    tout->Branch("p3_fromXc_PE", &p3_fromXc_PE);
    tout->Branch("p3_fromXc_PX", &p3_fromXc_PX);
    tout->Branch("p3_fromXc_PY", &p3_fromXc_PY);
    tout->Branch("p3_fromXc_PZ", &p3_fromXc_PZ);

    // Xc daughters PID

    tout->Branch("p1_fromXc_PIDK", &p1_fromXc_PIDK);
    tout->Branch("p1_fromXc_PIDp", &p1_fromXc_PIDp);
    tout->Branch("p2_fromXc_PIDK", &p2_fromXc_PIDK);
    tout->Branch("p2_fromXc_PIDp", &p2_fromXc_PIDp);
    tout->Branch("p3_fromXc_PIDK", &p3_fromXc_PIDK);  
    tout->Branch("p3_fromXc_PIDp", &p3_fromXc_PIDp);

    // Xc vertexing 

    tout->Branch("Xc_DOCA1", &Xc_DOCA1);
    tout->Branch("Xc_DOCA2", &Xc_DOCA2);
    tout->Branch("Xc_DOCA3", &Xc_DOCA3);
    tout->Branch("Xc_ENDVERTEX_CHI2", &Xc_ENDVERTEX_CHI2);

    // Y daughters (p1, p2, p3) kinematics

    tout->Branch("p1_fromY_P", &p1_fromY_P);
    tout->Branch("p2_fromY_P", &p2_fromY_P);
    tout->Branch("p3_fromY_P", &p3_fromY_P);
    tout->Branch("p1_fromY_PT", &p1_fromY_PT);
    tout->Branch("p2_fromY_PT", &p2_fromY_PT);
    tout->Branch("p3_fromY_PT", &p3_fromY_PT);

    // Y DOCA and vertexing

    tout->Branch("Y_DOCA1", &Y_DOCA1);
    tout->Branch("Y_DOCA2", &Y_DOCA2);
    tout->Branch("Y_DOCA3", &Y_DOCA3);
    tout->Branch("Y_ENDVERTEX_CHI2", &Y_ENDVERTEX_CHI2);

    // Y eta

    tout->Branch("Y_ETA", &Y_ETA);
    tout->Branch("p1_fromY_ETA", &p1_fromY_ETA); //
    tout->Branch("p2_fromY_ETA", &p2_fromY_ETA); //
    tout->Branch("p3_fromY_ETA", &p3_fromY_ETA); //

    // Xc eta

    tout->Branch("Xc_ETA", &Xc_ETA);

    // B eta
    tout->Branch("B_ETA", &B_ETA);

    // Primary vertex info
    // Y_*_OWNPV
    tout->Branch("Y_IP_OWNPV", &Y_IP_OWNPV);
    tout->Branch("Y_IPCHI2_OWNPV", &Y_IPCHI2_OWNPV);
    tout->Branch("p1_fromY_IPCHI2_OWNPV", &p1_fromY_IPCHI2_OWNPV);
    tout->Branch("p2_fromY_IPCHI2_OWNPV", &p2_fromY_IPCHI2_OWNPV);
    tout->Branch("p3_fromY_IPCHI2_OWNPV", &p3_fromY_IPCHI2_OWNPV);

    // Xc_*_OWNPV
    tout->Branch("p1_fromXc_IPCHI2_OWNPV", &p1_fromXc_IPCHI2_OWNPV);
    tout->Branch("p2_fromXc_IPCHI2_OWNPV", &p2_fromXc_IPCHI2_OWNPV);
    tout->Branch("p3_fromXc_IPCHI2_OWNPV", &p3_fromXc_IPCHI2_OWNPV);
    tout->Branch("Xc_FD_OWNPV", &Xc_FD_OWNPV);
    tout->Branch("Xc_FD_ORIVX", &Xc_FD_ORIVX);

    // B_*_OWNPV
    tout->Branch("B_FD_OWNPV", &B_FD_OWNPV);

    // Ghost probabilities

    tout->Branch("p1_fromY_TRACK_GhostProb", &p1_fromY_TRACK_GhostProb);
    tout->Branch("p2_fromY_TRACK_GhostProb", &p2_fromY_TRACK_GhostProb);
    tout->Branch("p3_fromY_TRACK_GhostProb", &p3_fromY_TRACK_GhostProb);

    tout->Branch("p1_fromXc_TRACK_GhostProb", &p1_fromXc_TRACK_GhostProb);
    tout->Branch("p2_fromXc_TRACK_GhostProb", &p2_fromXc_TRACK_GhostProb);
    tout->Branch("p3_fromXc_TRACK_GhostProb", &p3_fromXc_TRACK_GhostProb);

    // Other event variables

    tout->Branch("Xc_PT", &Xc_PT);
    tout->Branch("Y_MINIPCHI2NEXTBEST", &Y_MINIPCHI2NEXTBEST);
    tout->Branch("nPV", &nPV);
    tout->Branch("index", &INDEX);

    // BDT variables
    tout->Branch("BDT_3pi", &BDT_3pi);
    tout->Branch("BDT_Ds", &BDT_Ds);
    tout->Branch("BDT_Bs", &BDT_Bs);
}

void tmva_branch(vector<string> weightFile, string sampletype) {
    string weightFile_BDT_3pi, weightFile_BDT_Ds, weightFile_BDT_Bs;
    if (std::string::npos != weightFile[0].find("3pi")) {
        weightFile_BDT_3pi = weightFile[0];
        if (std::string::npos != weightFile[1].find("Ds")) {
            weightFile_BDT_Ds = weightFile[1];
            weightFile_BDT_Bs = weightFile[2];
        }   
        else {
            weightFile_BDT_Ds = weightFile[2];
            weightFile_BDT_Bs = weightFile[1];
        }   
    }   
    else if (std::string::npos != weightFile[1].find("3pi")) {
        weightFile_BDT_3pi = weightFile[1];
        if (std::string::npos != weightFile[2].find("Ds")) {
            weightFile_BDT_Ds = weightFile[2];
            weightFile_BDT_Bs = weightFile[0];
        }   
        else {
            weightFile_BDT_Ds = weightFile[0];
            weightFile_BDT_Bs = weightFile[2];
        }   
    }   
    else if (std::string::npos != weightFile[2].find("3pi")) {
        weightFile_BDT_3pi = weightFile[2];
        if (std::string::npos != weightFile[0].find("Ds")) {
            weightFile_BDT_Ds = weightFile[0];
            weightFile_BDT_Bs = weightFile[1];
        }   
        else {
            weightFile_BDT_Ds = weightFile[1];
            weightFile_BDT_Bs = weightFile[0];
        }   
    }   
    else {
        cout << "ERROR: weight files are not found" << endl;
    }

    // 3pi
    //TMVA::Reader *reader_3pi = new TMVA::Reader("!Color:!Silent");
    reader_3pi = new TMVA::Reader("!Color:!Silent");
    reader_3pi->AddVariable( "p1_fromY_ETA",                &var_3pi[0]);
    reader_3pi->AddVariable( "p2_fromY_ETA",                &var_3pi[1]);
    reader_3pi->AddVariable( "p3_fromY_ETA",                &var_3pi[2]);
    reader_3pi->AddVariable( "log(p1_fromY_IPCHI2_OWNPV)",  &var_3pi[3]);
    reader_3pi->AddVariable( "log(p2_fromY_IPCHI2_OWNPV)",  &var_3pi[4]);
    reader_3pi->AddVariable( "log(p3_fromY_IPCHI2_OWNPV)",  &var_3pi[5]);
    reader_3pi->AddVariable( "log(p1_fromY_TRACK_GhostProb)",  &var_3pi[6]);
    reader_3pi->AddVariable( "log(p2_fromY_TRACK_GhostProb)",  &var_3pi[7]);
    reader_3pi->AddVariable( "log(p3_fromY_TRACK_GhostProb)",  &var_3pi[8]);
    reader_3pi->AddVariable( "Y_DOCA1",                &var_3pi[9]);
    reader_3pi->AddVariable( "Y_DOCA2",                &var_3pi[10]);
    reader_3pi->AddVariable( "Y_DOCA3",                &var_3pi[11]);
    reader_3pi->AddVariable( "Y_ENDVERTEX_CHI2",       &var_3pi[12]);
    //
    reader_3pi->AddSpectator( "B_MM",  &spec_3pi[0]);
    reader_3pi->AddSpectator( "Xc_MM",  &spec_3pi[1]);
    //
    reader_3pi->BookMVA("BDT method",  weightFile_BDT_3pi+"_BDT.weights.xml");

    // Ds
    //TMVA::Reader *reader_Ds = new TMVA::Reader("!Color:!Silent");
    reader_Ds = new TMVA::Reader("!Color:!Silent");
    reader_Ds->AddVariable( "log(Xc_ENDVERTEX_CHI2)",&var_Ds[0]);
    reader_Ds->AddVariable( "log(Xc_FD_OWNPV)",      &var_Ds[1]);
    reader_Ds->AddVariable( "log(Xc_FD_ORIVX)",      &var_Ds[2]);
    reader_Ds->AddVariable( "Xc_ETA",                &var_Ds[3]);
    reader_Ds->AddVariable( "log(Xc_PT)",                 &var_Ds[4]);
    reader_Ds->AddVariable( "log(p1_fromXc_IPCHI2_OWNPV)",  &var_Ds[5]);
    reader_Ds->AddVariable( "log(p2_fromXc_IPCHI2_OWNPV)",  &var_Ds[6]);
    reader_Ds->AddVariable( "log(p3_fromXc_IPCHI2_OWNPV)",  &var_Ds[7]);
    reader_Ds->AddVariable( "log(p1_fromXc_PT)",  &var_Ds[8]);
    reader_Ds->AddVariable( "log(p2_fromXc_PT)",  &var_Ds[9]);
    reader_Ds->AddVariable( "log(p3_fromXc_PT)",  &var_Ds[10]);
    reader_Ds->AddVariable( "log(p1_fromXc_TRACK_GhostProb)",  &var_Ds[11]);
    reader_Ds->AddVariable( "log(p2_fromXc_TRACK_GhostProb)",  &var_Ds[12]);
    reader_Ds->AddVariable( "log(p3_fromXc_TRACK_GhostProb)",  &var_Ds[13]);
    //
    reader_Ds->AddSpectator( "B_MM",  &spec_Ds[0]);
    reader_Ds->AddSpectator( "Xc_MM",  &spec_Ds[1]);
    //
    reader_Ds->BookMVA("BDT method",  weightFile_BDT_Ds+"_BDT.weights.xml");

    if (sampletype == "BsNorm" || sampletype == "BdNorm" || sampletype == "data"){
    // Bs
    //TMVA::Reader *reader_Bs = new TMVA::Reader("!Color:!Silent");
    reader_Bs = new TMVA::Reader("!Color:!Silent");
    reader_Bs->AddVariable( "B_ETA", &var_Bs[0]);
    reader_Bs->AddVariable( "log(B_FD_OWNPV)", &var_Bs[1]);
    reader_Bs->AddVariable( "BDT_3pi", &var_Bs[2]);
    reader_Bs->AddVariable( "BDT_Ds", &var_Bs[3]);
    //
    reader_Bs->AddSpectator( "B_MM", &spec_Bs[0]);
    reader_Bs->AddSpectator( "Xc_MM", &spec_Bs[1]);
    //
    reader_Bs->BookMVA("BDT method", weightFile_BDT_Bs+"_BDT.weights.xml");
    }
}
