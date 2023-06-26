void codefromchatgpt4(){


   TCanvas *c1 = new TCanvas("c1","c1",800,600);
   TH1F *haha1 = new TH1F("h1_1", "Muon Stopping Depth (Without Lead)", 500, -500, 500);
   TH1F *haha2 = new TH1F("h1_2", "Muon Stopping Depth (With Lead)", 500, -500, 500);

   TFile *file1 = TFile::Open("TEST0withoutlead.root");
   TTree *tree1 = (TTree*)file1->Get("MuonStoppedDepth");
   tree1->Draw("MuonStoppedDepth>>h1_1");
   haha1->SetLineColor(kRed);

   TFile *file2 = TFile::Open("TEST0withlead.root");
   TTree *tree2 = (TTree*)file2->Get("MuonStoppedDepth");
   tree2->Draw("MuonStoppedDepth>>h1_2","same");
   haha2->SetLineColor(kBlue);

   haha1->Draw();
   haha2->Draw("same");

   TLegend *leg = new TLegend(0.7,0.8,0.9,0.9);
   leg->AddEntry(haha1,"Without Lead","l");
   leg->AddEntry(haha2,"With Lead","l");
   leg->Draw();


}
