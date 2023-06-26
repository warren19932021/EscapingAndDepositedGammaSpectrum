#include <iostream>
#include <fstream>
#include <string>

using namespace std;



void Draw(){

     
   const Int_t Colors[11] = {602, 856, 865, 870, 844, 417, 800, 802, 632, 891, 880};
   //gr1->SetLineColor(2);
   //gr2->SetLineColor(3);
   //gr3->SetLineColor(4);

   auto c3 = new TCanvas("c3","c3",600, 400);
   gStyle->SetOptFit(0001);
 
   auto mg = new TMultiGraph("mg","mg");
 
   const Int_t size = 10;
 

   Double_t px[size]  = {1.,2.,3.,4.,5.,6.,7.,8.,9.,10.};
   Double_t py1[size] = {70.1,80,90,91,92,93,94,95,96,97};
   Double_t py2[size] = {72,82,94,92,94,94,95,96,97,98};
   Double_t py3[size] = {0,22,44,62,64,74,85,91,94,100};
   
   
   auto gr3 = new TGraph( size, px, py3 );
   gr3->SetName("gr3");
   gr3->SetTitle("graph 3");
   gr3->SetMarkerStyle(21);
   gr3->SetDrawOption("AP");
   gr3->SetLineColor(Colors[0]);
   gr3->SetLineWidth(4);
   gr3->SetFillStyle(0);
 
   auto gr2 = new TGraph( size, px, py2 );
   gr2->SetName("gr2");
   gr2->SetTitle("graph 2");
   gr2->SetMarkerStyle(22);
   gr2->SetMarkerColor(2);
   gr2->SetDrawOption("P");
   gr2->SetLineColor(Colors[1]);
   gr2->SetLineWidth(4);
   gr2->SetFillStyle(0);
 
   auto gr1 = new TGraph( size, px, py1 );
   gr1->SetName("gr1");
   gr1->SetTitle("E_{#mu}=50MeV");
   gr1->GetXaxis()->SetTitle("Thickness(mm)");
   gr1->GetXaxis()->CenterTitle(true); 
   gr1->GetYaxis()->SetTitle("Percent(%)");
   gr1->GetYaxis()->CenterTitle(true); 
   gr1->SetMarkerStyle(23);
   gr1->SetLineColor(Colors[2]);
   gr1->SetLineWidth(4);
   gr1->SetFillStyle(0);
 
   mg->Add( gr3 );
   mg->Add( gr2 );
 
   gr1->Draw("ALP");
   mg->Draw("LP");
   c3->BuildLegend();
}
