float fmlr(float nSig, float nBkg, float effS, float effB) {

  float S = effS * nSig;
  float B = effB * nBkg; 

  float sgn = S/sqrt(S+B); // fom

  return sgn;

}

float optCut(string input, string method1, string method2, int nSig, int nBkg) {

  TFile *f = new TFile((input).c_str());

  TH1* effS = (TH1*) f->Get(("dataset/Method_"+method1+"/"+method2+"/MVA_"+method2+"_effS").c_str())->Clone("MVA_effS");
  TH1* effB = (TH1*) f->Get(("dataset/Method_"+method1+"/"+method2+"/MVA_"+method2+"_effB").c_str())->Clone("MVA_effB");
  TH1* sig = (TH1*) effS->Clone("significance");
  float fEffS, fEffB;
  float fSig, fSigMax;
  float fOut; // output variable of MVA classification
  float fOptCut;
  for (int i=1; i<=effS->GetNbinsX(); i++) {
    fEffS = effS->GetBinContent(i);
    fEffB = effB->GetBinContent(i);
    fOut = effS->GetXaxis()->GetBinCenter(i);
    //cout << "signal efficiency: " << fEffS << ", " << method2 << ": " << fOut << endl;
    //cout << "significance (dummy): " << sig->GetBinContent(i) << endl;
    sig->SetBinContent(i, fmlr(nSig, nBkg, fEffS, fEffB));
    //cout << "significance: " << sig->GetBinContent(i) << endl;
  }

  fSigMax = sig->GetMaximum();
  fOptCut = effS->GetXaxis()->GetBinCenter(sig->GetMaximumBin());
  //cout << "optimal cut = " << fOptCut << " (determined with maximum significance = " << fSigMax << ")" << endl;
   
  return fOptCut;

}

float optCut_vSigEff(string input, string method1, string method2, float target) {

  TFile *f = new TFile((input).c_str());

  TH1* effS = (TH1*) f->Get(("dataset/Method_"+method1+"/"+method2+"/MVA_"+method2+"_effS").c_str())->Clone("MVA_effS");
  TH1* diff = (TH1*) effS->Clone("difference");
  float fEffS;
  float fSigEff;
  float fOptCut;
  for (int i=1; i<=effS->GetNbinsX(); i++) {
    fEffS = effS->GetBinContent(i);
    diff->SetBinContent(i, abs(target-fEffS));
  }

  fSigEff = effS->GetBinContent(diff->GetMinimumBin());
  fOptCut = effS->GetXaxis()->GetBinCenter(diff->GetMinimumBin());
  cout << "optimal cut = " << fOptCut << " (determined with signal efficiency = " << fSigEff << ")" << endl;
   
  return fOptCut;

}
/*
void test() {
  
  string input = "Output_tmva_3pi.root";
  string method1 = "BDT";
  string method2 = "BDT";
  int nSig = 500;
  int nBkg = 1000;

  float fOptCut = optCut(input, method1, method2, nSig, nBkg);
  cout << "optimal cut = " << fOptCut << endl;

  gROOT->ProcessLine(".q");

}
*/
