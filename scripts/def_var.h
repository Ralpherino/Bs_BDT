// ==========================
// Define the input variables
// ==========================

    // Common base types
    Double_t  B_MM;
    Double_t  Xc_MM;

    Int_t p1_fromXc_TRUEID;
    Int_t p2_fromXc_TRUEID;
    Int_t p3_fromXc_TRUEID;

    Int_t B_BKGCAT;
    Int_t Xc_BKGCAT;
    Int_t Y_BKGCAT;

    Int_t p1_fromY_TRUEID;
    Int_t p2_fromY_TRUEID;
    Int_t p3_fromY_TRUEID;
    Int_t Xc_TRUEID;

    // FromXc kinematics and PID
    Double_t p1_fromXc_PT, p2_fromXc_PT, p3_fromXc_PT;
    Double_t p1_fromXc_PE, p1_fromXc_PX, p1_fromXc_PY, p1_fromXc_PZ;
    Double_t p2_fromXc_PE, p2_fromXc_PX, p2_fromXc_PY, p2_fromXc_PZ;
    Double_t p3_fromXc_PE, p3_fromXc_PX, p3_fromXc_PY, p3_fromXc_PZ;

    Double_t p1_fromXc_PIDK, p1_fromXc_PIDp;
    Double_t p2_fromXc_PIDK, p2_fromXc_PIDp;
    Double_t p3_fromXc_PIDK, p3_fromXc_PIDp;

    // FromY kinematics
    Double_t p1_fromY_P, p1_fromY_PT;
    Double_t p2_fromY_P, p2_fromY_PT;
    Double_t p3_fromY_P, p3_fromY_PT;

    Double_t p1_fromY_PE, p1_fromY_PX, p1_fromY_PY, p1_fromY_PZ;
    Double_t p2_fromY_PE, p2_fromY_PX, p2_fromY_PY, p2_fromY_PZ;
    Double_t p3_fromY_PE, p3_fromY_PX, p3_fromY_PY, p3_fromY_PZ;

    Double_t p1_fromY_ETA, p2_fromY_ETA, p3_fromY_ETA;

    // DOCA and vertex chi2
    Double_t Y_DOCA1, Y_DOCA2, Y_DOCA3, Y_ENDVERTEX_CHI2;
    Double_t Xc_DOCA1, Xc_DOCA2, Xc_DOCA3, Xc_ENDVERTEX_CHI2;

    // IPCHI2 and ghost probability
    double p1_fromY_IPCHI2_OWNPV, p2_fromY_IPCHI2_OWNPV, p3_fromY_IPCHI2_OWNPV;
    double p1_fromXc_IPCHI2_OWNPV, p2_fromXc_IPCHI2_OWNPV, p3_fromXc_IPCHI2_OWNPV; // Only in Ds selection

    double p1_fromY_TRACK_GhostProb, p2_fromY_TRACK_GhostProb, p3_fromY_TRACK_GhostProb;
    //double p1_fromY_TRACK_GhostProbability, p2_fromY_TRACK_GhostProbability, p3_fromY_TRACK_GhostProbability;

    double p1_fromXc_TRACK_GhostProb, p2_fromXc_TRACK_GhostProb, p3_fromXc_TRACK_GhostProb; // Only in Ds selection
   // double p1_fromXc_TRACK_GhostProbability, p2_fromXc_TRACK_GhostProbability, p3_fromXc_TRACK_GhostProbability; // Only in Ds selection

    // Mass reconstructions
    double Xc_reco_M, Y_reco_M, B_reco_M; // Only in 3pi and Ds selections

    // Xc extra
    double Xc_FD_OWNPV;  // Only in Ds selection
    double Xc_FD_ORIVX;  // Only in Ds selection
    double Xc_ETA;       // Only in Ds selection
    double Xc_PT;        // Also appears in B selection as Xc_PT

    double Xc_Pperp;     // Only in B selection
    double Xc_DIRA_OWNPV; // Only in B selection

    double Xc_PE, Xc_PX, Xc_PY, Xc_PZ; // Only in B selection

    // Y extra
    Double_t Y_IP_OWNPV, Y_IPCHI2_OWNPV;
    double Y_MINIPCHI2NEXTBEST; // Only in 3pi and Ds selections
    Double_t Y_ETA;

    // B candidate variables
    double B_ENDVERTEX_CHI2; // Only in B Xc_Selection
    double B_IP_OWNPV, B_IPCHI2_OWNPV; // Only in B selection
    double B_FD_OWNPV, B_FDCHI2_OWNPV; // Only in B selection
    double B_DIRA_OWNPV; // Only in B selection
    double B_P, B_PT, B_ETA; // Only in B selection
    double B_DOCA1; // Only in B selection
    double B_TAU; // Only in B selection
    double B_PX, B_PY, B_PZ, B_PE; // Only in B selection

    double pt_pions; // Only in B selection
    double pt_B;     // Only in B selection

    double B_TRUEPT, B_TRUETAU; // Only in B selection

    // Extra info
    ULong64_t eventNumber;
    Int_t INDEX;
    int nPV;
    Int_t Xc_Selection;
    bool pass_event;

    // B vertex positions
    double B_OWNPV_X, B_OWNPV_Y, B_OWNPV_Z; // Only in B selection
    double B_ENDVERTEX_X, B_ENDVERTEX_Y, B_ENDVERTEX_Z; // Only in B selection

    // Trigger decisions
    bool B_L0HadronDecision_TOS;
    bool B_L0Global_TIS;
    bool B_Hlt1TrackAllL0Decision_TOS;

    // SS info
    int SS_Norm; // Only in B selection
    int SS_Sig;  // Only in B selection

// =====================
// Define TMVA variables
// =====================
    TMVA::Reader *reader_3pi, *reader_Ds, *reader_Bs;
    float var_3pi[13], var_Ds[14], var_Bs[4];
    float spec_3pi[2], spec_Ds[2], spec_Bs[2];
    double BDT_3pi, BDT_Bs, BDT_Ds;
