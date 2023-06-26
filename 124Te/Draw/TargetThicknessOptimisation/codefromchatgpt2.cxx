void codefromchatgpt2(){

   TFile *_file0 = TFile::Open("TEST0withoutlead.root");
   TTree *tree0 = (TTree*)gDirectory->Get("MuonStoppedDepth");
   TH1F *haha = new TH1F("h1", "h1 title", 500, -500, 500);
   tree0->Draw("MuonStoppedDepth>>h1");
   haha->SetLineColor(kBlue);   
   
   TFile *_file1 = TFile::Open("TEST0withlead.root");
   TTree *tree1 = (TTree*)gDirectory->Get("MuonStoppedDepth");
   tree1->Draw("MuonStoppedDepth>>+h1");
   haha->SetLineColor(kRed);

   haha->Draw();

   TLegend *leg = new TLegend(0.7,0.8,0.9,0.9);
   leg->AddEntry(haha,"Without Lead","l");
   leg->AddEntry((TObject*)0,"With Lead","");
   leg->Draw();
   
}

