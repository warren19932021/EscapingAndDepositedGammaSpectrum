#include <math.h>

void DrawThickness(){


   //gPad->SetLogy(1);

   TH1D * h11 = new TH1D("h11","h11",250,-500,500);
   TH1D * h22 = new TH1D("h22","h22",250,-500,500);

   TFile *_file0 = TFile::Open("TEST0withlead.root");
   TTree * Tree0 = (TTree*)_file0->FindObjectAny("MuonStoppedDepth;1");
   cout<<"Tree0->GetEntries(): "<<Tree0->GetEntries()<<endl;
   TFile *_file1 = TFile::Open("TEST0withoutlead.root");
   TTree * Tree1 = (TTree*)_file1->FindObjectAny("MuonStoppedDepth;1");
   cout<<"Tree1->GetEntries(): "<<Tree1->GetEntries()<<endl;




   double MuonStoppedDepth = 0; 
   Tree0->SetBranchAddress("MuonStoppedDepth", &MuonStoppedDepth); 
   Tree1->SetBranchAddress("MuonStoppedDepth", &MuonStoppedDepth); 
    

   for (int i=0; i<Tree0->GetEntries();i++)
   {
      Tree0->GetEntry(i);
      h11->Fill(MuonStoppedDepth);
   }	   

   for (int i=0; i<Tree1->GetEntries();i++)
   {
      Tree1->GetEntry(i);
      h22->Fill(MuonStoppedDepth);
   }	   



    auto c1 = new TCanvas("c1", "the title", 900, 700);
    //c1->SetLogy();

    h11->SetTitle("Muon stopped depth");
    h11->GetXaxis()->CenterTitle();
    h11->GetYaxis()->CenterTitle();
    h11->GetXaxis()->SetTitleOffset(1.10);
    h11->GetYaxis()->SetTitleOffset(1.20);
    h11->GetXaxis()->SetTitle("Depth(mm)");
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

    h11->Draw("hist");
    h22->Draw("same");


    TLegend* leg = new TLegend(0.60,0.68,0.89,0.86);
    leg->AddEntry(h11, "with lead","L");
    leg->AddEntry(h22, " without lead","L");
    leg->SetFillColor(0);
    leg->SetLineColor(0);
    leg->SetTextFont(22);
    leg->SetTextSize(0.04);
    leg->Draw();


    c1->SaveAs("muonstopeeddepth.png");

}

















