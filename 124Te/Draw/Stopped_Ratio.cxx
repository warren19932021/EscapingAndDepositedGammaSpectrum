#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int Size = 10;

Double_t px[Size]  = {1,2,3,4,5,6,7,8,9,10}; 

Double_t Ratio2[Size]  = {23,23,12,17,20,20,18,19,15,19};
Double_t Ratio1[Size]  = {2.0,5.0,6.0,7,10,4,7,3,5,3};
Double_t Ratio3[Size]  = {0,1,1,0,0,1,0,0,0,0};


void Stopped_Ratio() {


    for (int i=0;i<10;i++)
     {
        //cout<<"Ratio1[Size]: "<<Ratio1[i]<<endl;
        //cout<<"Ratio2[Size]: "<<Ratio2[i]<<endl;
        cout<<"Ratio3[Size]: "<<Ratio3[i]<<endl;
     }


//-------------------------The following code is used to draw Graph------------------

   const Int_t Colors[11] = {16, 432, 1, 870, 844, 417, 800, 802, 632, 891, 880};

   auto c3 = new TCanvas("c3","c3",2200, 1800);
   gStyle->SetOptFit(0001);
 
   auto mg = new TMultiGraph("mg","mg");
 
   
   auto gr3 = new TGraph( Size, px, Ratio3 );
   gr3->SetName("gr3");
   gr3->SetTitle("Air");
   gr3->SetMarkerStyle(21);
   gr3->SetDrawOption("P");
   gr3->SetLineColor(Colors[2]);
   gr3->SetLineWidth(4);
   gr3->SetFillStyle(0);
 

   auto gr1 = new TGraph( Size, px, Ratio1 );
   gr1->SetName("Target");
   gr1->SetTitle("Target");
   gr1->SetMarkerStyle(22);
   //gr1->SetMarkerColor(2);
   gr1->SetDrawOption("P");
   gr1->SetLineColor(Colors[0]);
   gr1->SetLineWidth(4);
   gr1->SetFillStyle(0);


   auto gr2 = new TGraph( Size, px, Ratio2 );
   gr2->SetName("Scintillator");
   gr2->SetTitle("Scintillator");
   gr2->GetXaxis()->SetTitle("Thickness(mm)");
   gr2->GetXaxis()->CenterTitle(true); 
   gr2->GetYaxis()->SetTitle("Number of muon stopped");
   gr2->GetYaxis()->CenterTitle(true); 
   gr2->GetYaxis()->SetRangeUser(0, 25);

   gr2->SetMarkerStyle(23);
   gr2->SetLineColor(Colors[1]);
   gr2->SetLineWidth(4);
   gr2->SetFillStyle(0);

   gr2->SetTitle("");
   gr2->Draw("ALP");

   mg->Add( gr1 );
   mg->Add( gr3 );
   mg->Draw("LP");



   c3->BuildLegend();
   c3->Print("Test.jpg");

}

