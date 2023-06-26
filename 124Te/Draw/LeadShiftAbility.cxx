#include <math.h>

void LeadShiftAbility(){


    auto c1 = new TCanvas("c1", "the title", 900, 700);
    //c1->SetLogy();
   //gPad->SetLogy(1);

   TH1D * h11 = new TH1D("h11","h11",1000,-500,500);
   TH1D * h22 = new TH1D("h22","h22",1000,-500,500);
   TFile *_file0 = TFile::Open("TEST0withlead.root"); 
   TTree * TreeSig = (TTree*)_file0->FindObjectAny("MuonStoppedDepth;1");
   TreeSig->Draw("MuonStoppedDepth>>h11");
   _file0->Close();
   TFile *_file1 = TFile::Open("TEST0withoutlead.root"); 
   TTree * TreeBkg = (TTree*)_file1->FindObjectAny("MuonStoppedDepth;1");
   //TreeBkg->Draw("MuonStoppedDepth>>h22");

   TreeSig->Print();
    





  // h11->Draw("hist");


/*
    h11->SetTitle("Gamma energy spectrum");
    h11->GetXaxis()->CenterTitle();
    h11->GetYaxis()->CenterTitle();
    h11->GetXaxis()->SetTitleOffset(1.10);
    h11->GetYaxis()->SetTitleOffset(1.20);
    h11->GetXaxis()->SetTitle("E_{#mu}(MeV)");
    h11->GetYaxis()->SetTitle("Event Number");

    //h11->SetFillColor(1);
    //h22->SetFillColor(2);
    h11->SetLineColor(1);
    h11->SetLineColor(2);
    h11->SetStats(0); 

   int yMax;
    if ( h22->GetMaximum() >=  h11->GetMaximum() )
    yMax = h22->GetMaximum()*1.5;
    if ( h11->GetMaximum() >  h22->GetMaximum() )
    yMax = h11->GetMaximum()*1.5;
    h11->GetYaxis()->SetRangeUser(0,yMax);


    //h11->Scale(1 / (float)nentries);
    //h22->Scale(1 / (float)nentries);

    h11->Draw();
    h22->Draw("same");


    TLegend* leg = new TLegend(0.60,0.68,0.89,0.86);
    leg->AddEntry(h11, "Signal","L");
    leg->AddEntry(h22, " Bkg","L");
    leg->SetFillColor(0);
    leg->SetLineColor(0);
    leg->SetTextFont(22);
    leg->SetTextSize(0.04);
    leg->Draw();

*/
    c1->SaveAs("try.png");

}

















