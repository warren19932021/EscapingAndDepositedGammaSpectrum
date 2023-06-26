#include <math.h>

void DrawTypicalEnergyPeak(){



   TH1D * h11 = new TH1D("h11","h11",1000,0,10);

   TFile *_file0 = TFile::Open("NEWTEST0SeeTypicalEnergyPeak.root");
   TTree * Tree0 = (TTree*)_file0->FindObjectAny("EGammaSignal;1");
   cout<<"Tree0->GetEntries(): "<<Tree0->GetEntries()<<endl;




   double EGammaSig = 0; 
   Tree0->SetBranchAddress("EGammaSig", &EGammaSig); 
    

   for (int i=0; i<Tree0->GetEntries();i++)
   {
      Tree0->GetEntry(i);
      h11->Fill(EGammaSig);
   }	   




    auto c1 = new TCanvas("c1", "the title", 900, 700);
    //c1->SetLogy();

    h11->SetTitle("Typical Gamma Signal Spectrum");
    h11->GetXaxis()->CenterTitle();
    h11->GetYaxis()->CenterTitle();
    h11->GetXaxis()->SetTitleOffset(1.10);
    h11->GetYaxis()->SetTitleOffset(1.20);
    h11->GetXaxis()->SetTitle("E_{#gamma}(MeV)");
    h11->GetYaxis()->SetTitle("Event Number");

    //h11->SetFillColor(1);
    //h22->SetFillColor(2);
    h11->SetLineColor(1);
    h11->SetLineColor(2);
    h11->SetStats(0); 

   int yMax;
    yMax = h11->GetMaximum()*1.5;
    h11->GetYaxis()->SetRangeUser(0,yMax);


    //h11->Scale(1 / (float)nentries);
    //h22->Scale(1 / (float)nentries);

    h11->Draw("hist");


    TLegend* leg = new TLegend(0.60,0.68,0.89,0.86);
    leg->AddEntry(h11, "Gamma","L");
    leg->SetFillColor(0);
    leg->SetLineColor(0);
    leg->SetTextFont(22);
    leg->SetTextSize(0.04);
    leg->Draw();


    c1->SaveAs("TypicalEnergyPeak.png");


}

















