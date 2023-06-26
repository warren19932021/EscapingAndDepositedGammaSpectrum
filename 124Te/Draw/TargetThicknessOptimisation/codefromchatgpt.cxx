void codefromchatgpt(){

   TH1F *haha = new TH1F("h1", "h1 title", 500, -500, 500);
   TFile *_file0 = TFile::Open("TEST0withoutlead.root");
   TTree *tree = (TTree*)gDirectory->Get("MuonStoppedDepth;1");
   tree->Draw("MuonStoppedDepth>>haha");
   
   TFile *_file1 = TFile::Open("TEST0withlead.root");
   TTree *tree1 = (TTree*)gDirectory->Get("MuonStoppedDepth;1");
   TH1F *haha1 = new TH1F("h2", "h2 title", 500, -500, 500);
   tree1->Draw("MuonStoppedDepth>>haha1");
   
   haha->Add(haha1);
   haha->Draw();
   
}

