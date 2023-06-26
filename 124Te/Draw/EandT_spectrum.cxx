void EandT_spectrum(){


   gStyle->SetOptFit(111);	


   TCanvas *t0 = new TCanvas("t0", "test canvas", 800, 700);
   gStyle->SetOptStat("");
   t0->SetGrid();
   //t0->SetLogz();

   //TFile *_file0 = TFile::Open("DrawTEST9.root","read");
   TFile *_file0 = TFile::Open("NewDrawTEST9.root","read");
   TTree * a  = (TTree*)_file0->Get("Ntuple");
   TH2D *  bbb = new TH2D("bbb","bbb",50000,0,500,100,0,25);
   a->Draw("E:T>>bbb","Flag==0","LEGO2Z");
  
  
   bbb->GetYaxis()->SetTitle("Energy(MeV)"); 
   bbb->GetXaxis()->SetTitle("Time(ns)"); 
   //bbb->GetYaxis()->SetRangeUser(0, 8);
   //bbb->GetXaxis()->SetRangeUser(0, 6);
   bbb->SetTitle("Gamma Energy and Time Spectrum");

   bbb->GetXaxis()->CenterTitle();
   bbb->GetXaxis()->SetTitleOffset(1.50);
   bbb->GetXaxis()->SetTitleSize(0.05);

   bbb->GetYaxis()->CenterTitle();
   bbb->GetYaxis()->SetTitleOffset(1.50);
   bbb->GetYaxis()->SetTitleSize(0.05);




}
