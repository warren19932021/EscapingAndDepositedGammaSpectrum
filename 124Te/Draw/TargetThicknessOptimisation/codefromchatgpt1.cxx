void codefromchatgpt1(){

   TFile *_file0 = TFile::Open("TEST0withoutlead.root");
   TTree *tree0 = (TTree*)gDirectory->Get("MuonStoppedDepth");
   TH1F *haha = new TH1F("h1", "h1 title", 500, -500, 500);
   tree0->Draw("MuonStoppedDepth>>h1");

   TFile *_file1 = TFile::Open("TEST0withlead.root");
   TTree *tree1 = (TTree*)gDirectory->Get("MuonStoppedDepth");
   tree1->Draw("MuonStoppedDepth>>+h1");

   haha->Draw();

}

