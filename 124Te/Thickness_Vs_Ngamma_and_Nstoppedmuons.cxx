#include <iostream>
#include <fstream>
#include <string>

using namespace std;


const int Size = 40;


Double_t px[Size]  = {0};

double Nmuons[Size];
double NGammas[Size];



void Thickness_Vs_Ngamma_and_Nstoppedmuons() {

     for (int i = 0; i < Size; i++)
     {
        px[i]= i;
	cout<<"px[i]: "<<px[i]<<endl;
     }		



//-----------------The following code is used to put date into arrays------------------------------


       

    string inFileName = "NumberodMuon_exampleTarget.txt";
    ifstream inFile;
    inFile.open(inFileName.c_str());

    if (inFile.is_open())
    {
	    

	for (int i = 0; i < Size; i++)
        {
            inFile >> Nmuons[i];
	}


        inFile.close(); 

    }
    else 
    { 
        cerr << "Can't find input file " << inFileName << endl;
    }

     for (int i = 0; i < Size; i++)
     {
            cout << "Nmuons["<<i<<"]: "<<Nmuons[i] << " \n";
     }		



    string inFileName1 = "NumberGamma.txt";
    ifstream inFile1;
    inFile1.open(inFileName1.c_str());

    if (inFile1.is_open())
    {
	    

	for (int i = 0; i < Size; i++)
        {
            inFile1 >> NGammas[i];
	}


        inFile1.close(); 

    }
    else 
    { 
        cerr << "Can't find input file " << inFileName1 << endl;
    }

     for (int i = 0; i < Size; i++)
     {
            cout << "NGammas["<<i<<"]: "<<NGammas[i] << " \n";
     }		


//-------------------------The following code is used to draw Graph------------------

   const Int_t Colors[11] = {602, 856, 865, 870, 844, 417, 800, 802, 632, 891, 880};
   //gr1->SetLineColor(2);
   //gr2->SetLineColor(3);
   //gr3->SetLineColor(4);

   auto c3 = new TCanvas("c3","c3",2200, 1800);
   gStyle->SetOptFit(0001);
 
   auto mg = new TMultiGraph("mg","mg");
 
 
   auto gr2 = new TGraph( Size, px, NGammas );
   gr2->SetName("gr2");
   gr2->SetTitle("N_{#gamma}");
   gr2->SetMarkerStyle(22);
   gr2->SetMarkerColor(2);
   gr2->SetDrawOption("P");
   gr2->SetLineColor(Colors[1]);
   gr2->SetLineWidth(4);
   gr2->SetFillStyle(0);
 
   auto gr1 = new TGraph( Size, px, Nmuons );
   gr1->SetName("N_{#mu^{-}}");
   gr1->SetTitle("N_{#mu^{-}}");
   gr1->GetXaxis()->SetTitle("Thickness(mm)");
   gr1->GetXaxis()->CenterTitle(true); 
   gr1->GetYaxis()->SetTitle("Percent(%)");
   gr1->GetYaxis()->CenterTitle(true); 
   gr1->SetMarkerStyle(23);
   gr1->SetLineColor(Colors[0]);
   gr1->SetLineWidth(4);
   gr1->SetFillStyle(0);
   gr1->SetTitle("");
   gr1->Draw("ALP");
 
   mg->Add( gr2 );
   mg->Draw("LP");

   c3->BuildLegend();
   c3->Print("Test_N_gamma_and_muon.jpg");



}

