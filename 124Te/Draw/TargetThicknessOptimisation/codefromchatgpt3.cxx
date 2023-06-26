void codefromchatgpt3(){

   TCanvas *c1 = new TCanvas("c1","c1",800,600);
   TH1F *haha = new TH1F("h1", "Muon Stopping Depth", 500, -500, 500);
   
   TFile *file0 = TFile::Open("TEST0withoutlead.root");
   TTree *tree0 = (TTree*)file0->Get("MuonStoppedDepth");
   tree0->Draw("MuonStoppedDepth>>h1");
   haha->SetLineColor(kRed);
   
   TFile *file1 = TFile::Open("TEST0withlead.root");
   TTree *tree1 = (TTree*)file1->Get("MuonStoppedDepth");
   tree1->Draw("MuonStoppedDepth>>+h1");
   haha->SetLineColor(kBlue);

   haha->Draw();

   TLegend *leg = new TLegend(0.7,0.8,0.9,0.9);
   leg->AddEntry(haha,"Without Lead","l");
   leg->AddEntry((TObject*)0,"With Lead","");
   leg->Draw();
   
}

