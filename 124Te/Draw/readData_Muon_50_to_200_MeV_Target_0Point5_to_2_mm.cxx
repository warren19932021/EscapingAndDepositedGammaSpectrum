#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int SIZE = 64;
double Ratio[SIZE];
double RunNumber[SIZE];


const int Size = 16;


Double_t px[Size]  = {0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0}; 

double Ratio1[Size];
double Ratio2[Size];
double Ratio3[Size];
double Ratio4[Size];

double RunNumber1[Size];
double RunNumber2[Size];
double RunNumber3[Size];
double RunNumber4[Size];


void readData_Muon_50_to_200_MeV_Target_0Point5_to_2_mm() {

//-----------------The following code is used to put date into arrays------------------------------

    string inFileName = "deal_readData_Muon_50_to_200_MeV_Target_0Point5_to_2_mm.txt";
    //string inFileName = "deal.txt";
    ifstream inFile;
    inFile.open(inFileName.c_str());

    if (inFile.is_open())
    {
	    

	for (int i = 0; i < Size; i++)
        {
            inFile >> Ratio1[i] >> RunNumber1[i];
            //cout << "Ratio1["<<i<<"]: "<<Ratio1[i] <<" "<<RunNumber1[i]<< " \n";
	}
      
        for (int i = Size; i < 2*Size; i++)
        {
            inFile >> Ratio2[i - Size] >> RunNumber2[i - Size];
            //cout << "Ratio2["<<i-Size<<"]: "<<Ratio2[i - Size] <<" "<<RunNumber2[i - Size]<< " \n";
	}
      
        for (int i = 2*Size; i < 3*Size; i++)
        {
            inFile >> Ratio3[i - 2*Size] >> RunNumber3[i - 2*Size];
            //cout << "Ratio3["<<i - 2*Size<<"]: "<<Ratio3[i - 2*Size] <<" "<<RunNumber3[i - 2*Size]<< " \n";
	}
      
        for (int i = 3*Size; i < 4*Size; i++)
        {
            inFile >> Ratio4[i - 3*Size] >> RunNumber4[i - 3*Size];
	    //cout << "Ratio4["<<i - 3*Size<<"]: "<<Ratio4[i - 3*Size] <<" "<<RunNumber4[i - 3*Size]<< " \n";
	}
     


        inFile.close(); 


    }
    else 
    { 
        cerr << "Can't find input file " << inFileName << endl;
    }




//-------------------------The following code is used to draw Graph------------------

   const Int_t Colors[11] = {602, 856, 865, 870, 844, 417, 800, 802, 632, 891, 880};
   //gr1->SetLineColor(2);
   //gr2->SetLineColor(3);
   //gr3->SetLineColor(4);

   auto c3 = new TCanvas("c3","c3",2200, 1800);
   gStyle->SetOptFit(0001);
 
   auto mg = new TMultiGraph("mg","mg");
 
   
   auto gr4 = new TGraph( Size, px, Ratio4 );
   gr4->SetName("gr4");
   gr4->SetTitle("E_{#mu}=200MeV");
   gr4->SetMarkerStyle(20);
   gr4->SetDrawOption("AP");
   gr4->SetLineColor(Colors[3]);
   gr4->SetLineWidth(4);
   gr4->SetFillStyle(0);
 
   auto gr3 = new TGraph( Size, px, Ratio3 );
   gr3->SetName("gr3");
   gr3->SetTitle("E_{#mu}=150MeV");
   gr3->SetMarkerStyle(21);
   gr3->SetDrawOption("AP");
   gr3->SetLineColor(Colors[2]);
   gr3->SetLineWidth(4);
   gr3->SetFillStyle(0);
 
   auto gr2 = new TGraph( Size, px, Ratio2 );
   gr2->SetName("gr2");
   gr2->SetTitle("E_{#mu}=100MeV");
   gr2->SetMarkerStyle(22);
   gr2->SetMarkerColor(2);
   gr2->SetDrawOption("P");
   gr2->SetLineColor(Colors[1]);
   gr2->SetLineWidth(4);
   gr2->SetFillStyle(0);
 
   auto gr1 = new TGraph( Size, px, Ratio1 );
   gr1->SetName("E_{#mu}=50MeV");
   gr1->SetTitle("E_{#mu}=50MeV");
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
   mg->Add( gr3 );
   mg->Add( gr4 );
   mg->Draw("LP");

   c3->BuildLegend();
   c3->Print("Test.jpg");

}

