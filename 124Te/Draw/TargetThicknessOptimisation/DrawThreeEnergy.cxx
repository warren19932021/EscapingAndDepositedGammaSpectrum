#include <math.h>

void DrawThreeEnergy(){


   //gPad->SetLogy(1);

   TH1D * h11 = new TH1D("h11","h11",10000,0,50000);
   TH1D * h22 = new TH1D("h22","h22",10000,0,50000);
   TH1D * h33 = new TH1D("h33","h33",10000,0,50000);

   TFile *_file0 = TFile::Open("TEST0.root");
   TTree * Tree0 = (TTree*)_file0->FindObjectAny("Ntuple;1");
   cout<<"Tree0->GetEntries(): "<<Tree0->GetEntries()<<endl;
   TTree * Tree1 = (TTree*)_file0->FindObjectAny("Stopped;1");
   cout<<"Tree1->GetEntries(): "<<Tree1->GetEntries()<<endl;
   TTree * Tree2 = (TTree*)_file0->FindObjectAny("EGammaSpectrumInHPGeactiveCrystal;1");
   cout<<"Tree2->GetEntries(): "<<Tree2->GetEntries()<<endl;


   double a_E = 0; 
   double EGammaSpectrumInHPGeactiveCrystal = 0; 
   Tree0->SetBranchAddress("E", &a_E); 
   Tree1->SetBranchAddress("E", &a_E); 
   Tree0->SetBranchAddress("EGammaSpectrumInHPGeactiveCrystal", &EGammaSpectrumInHPGeactiveCrystal); 


   



   for (int i=0; i<Tree0->GetEntries();i++)
   {
      cout<<"a_E: "<<a_E<<endl;
      Tree0->GetEntry(i);
      h11->Fill(a_E);
   }	   

   for (int i=0; i<Tree1->GetEntries();i++)
   {
      Tree1->GetEntry(i);
      h22->Fill(a_E);
   }	   
    

   for (int i=0; i<Tree2->GetEntries();i++)
   {
      Tree2->GetEntry(i);
      h33->Fill(EGammaSpectrumInHPGeactiveCrystal);
   }	   




    auto c1 = new TCanvas("c1", "the title", 900, 700);
    //c1->SetLogy();

    h11->SetTitle("Gamma Spectrum");
    //h11->SetTitle("Gamma Spectrum of HPGe");
    h11->GetXaxis()->CenterTitle();
    h11->GetYaxis()->CenterTitle();
    h11->GetXaxis()->SetTitleOffset(1.10);
    h11->GetYaxis()->SetTitleOffset(1.20);
    h11->GetXaxis()->SetTitle("E/MeV");
    //h11->GetXaxis()->SetTitle("E_{#gamma}(MeV)");
    h11->GetYaxis()->SetTitle("Event Number");

    //h11->SetFillColor(1);
    //h22->SetFillColor(2);
    h11->SetLineColor(1);
    h22->SetLineColor(2);
    h33->SetLineColor(3);
    h11->SetStats(0); 

    h11->GetYaxis()->SetRangeUser(0,500);


    //h11->Scale(1 / (float)nentries);
    //h22->Scale(1 / (float)nentries);

    h11->Draw("hist");
    h22->Draw("same");
    h33->Draw("same");


    TLegend* leg = new TLegend(0.60,0.68,0.89,0.86);
    leg->AddEntry(h11, "Gamma","L");
    leg->AddEntry(h22, "Gamma1","L");
    leg->AddEntry(h22, "Gamma2","L");
    leg->SetFillColor(0);
    leg->SetLineColor(0);
    leg->SetTextFont(22);
    leg->SetTextSize(0.04);
    leg->Draw();


    c1->SaveAs("ThreeTypeTypicalEnergyPeak.png");

}






















