void EandT_spectrumnew(){


   gStyle->SetOptFit(111);	



   TCanvas *t0 = new TCanvas("t0", "test canvas", 800, 700);
   gStyle->SetOptStat("");
   t0->SetGrid();
   //t0->SetLogz();


   //TFile *_file0 = TFile::Open("DrawTEST9.root","read");
   TFile *_file0 = TFile::Open("NewDrawTEST9.root","read");
   TTree * a  = (TTree*)_file0->Get("Ntuple");
   TH2D *  bbb = new TH2D("bbb","bbb",500,0,10000,80,0,40);
   a->Draw("E:T>>bbb","","LEGO2Z");
  
  
   bbb->GetYaxis()->SetTitle("Energy(MeV)"); 
   bbb->GetXaxis()->SetTitle("Time(ns)"); 
   bbb->GetZaxis()->SetTitle("Number of events"); 
   bbb->SetTitle("Gamma Energy and Time Spectrum");

   bbb->GetXaxis()->CenterTitle();
   bbb->GetXaxis()->SetTitleOffset(1.50);
   bbb->GetYaxis()->CenterTitle();
   bbb->GetYaxis()->SetTitleOffset(1.50);
   bbb->GetZaxis()->CenterTitle();
   bbb->GetZaxis()->SetTitleOffset(1.50);




}
