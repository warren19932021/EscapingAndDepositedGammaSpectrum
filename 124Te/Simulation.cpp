#include <iostream>
using namespace std;
#include <fstream>
#include "stdio.h"
#include <string>
#include <cstdio>
#include <vector>
#include <iomanip>
#include "TLegend.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TTree.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TFile.h"
#include "TStyle.h"
#include "TRandom3.h"
#include "TDatime.h"
#include "TLine.h"
#include "TSystem.h"
#include "TString.h"
#include <TUUID.h>
#include "TLegend.h"
#include "TPaveStats.h"
#include "TFile.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TLatex.h"
#include "TMath.h"
#include "TStopwatch.h"
#include "THStack.h"


const TString dir = "/soft/users/seibt/Geant4/TU5/build/results/";
const Int_t Colors[11] = {602, 856, 865, 870, 844, 417, 800, 802, 632, 891, 880};

TFile* File(TString run){
	TFile* rootFile = new TFile(dir+run+".root","UPDATE");
	return rootFile;
	}
// Histogram Data Structured (more canvas data)
typedef struct HistData {
	TCanvas* Canvas;													//Canvas containing the respective Histograms
	vector<TH1D*> Histograms;											//Histograms within the canvas
	vector<Double_t> Integral;											//Integrals of Histograms over whole spectrum
	vector<Double_t> Integral2to10keV;									//Integrals of Histograms from 2 to 10 keV
} HistogramData;

/* Creating multiple related Histograms */
HistData* EnergyHist(
	TString HistName,													//Title
	vector<TString> runs,												//run ID's for the files
	vector<TString> Thickness,											//'Thickness' is an artifact, it means the label/legend entry of each run 
	bool Rebin = true
){
	HistData* Data = new HistData;
	Data->Canvas = new TCanvas(HistName, HistName, 100, 10, 1400, 700);
	if(runs.size() == 0){return 0;}										//Return NULL if no runs are given
	TLegend* leg = new TLegend(0.6,0.8,0.9,0.9);
	//Empty vectors
	vector<TFile*> files = {};
	Data->Histograms = {};
	Data->Integral = {};
	Data->Integral2to10keV = {};
	for(int i = 0; i < runs.size(); i++){								//Iterate over all given runs
		files.push_back(File(runs[i]));
		Data->Histograms.push_back((TH1D*)files[i]->Get("Edep"));
		Data->Integral.push_back(Data->Histograms[i]->Integral());
		Data->Integral2to10keV.push_back(Data->Histograms[i]->Integral(2, 10));
		if (i == 0){													//First Histogram (i = 0) needs different/ additional settings than following histograms
			Data->Histograms[i]->SetTitle(HistName);
			Data->Histograms[i]->SetXTitle("E / keV");
			Data->Histograms[i]->SetYTitle("Counts / 0.1 keV");
			Data->Histograms[i]->SetLineColor(Colors[i]);
			if (Rebin) {Data->Histograms[i]->Rebin(5);
				Data->Histograms[i]->SetYTitle("Counts / 0.5 keV");
			}
			Data->Histograms[i]->GetXaxis()->SetRangeUser(0.9, 1000);
			Data->Histograms[i]->SetStats(0);
			leg->AddEntry(Data->Histograms[i], Thickness[i],"l");
			Data->Histograms[i]->Draw();
		} else {
			Data->Histograms[i]->SetLineColor(Colors[i]);
			if (Rebin) {Data->Histograms[i]->Rebin(5);}
			Data->Histograms[i]->SetStats(0);
			leg->AddEntry(Data->Histograms[i], Thickness[i],"l");
			Data->Histograms[i]->Draw("same");
		}
	}
	leg->Draw("same");
	gPad->SetLogy(1);
	gPad->Update();
	return Data;														//Return Pointer of Struct
}

/*Scaled histograms:*/
HistData* EnergyHistScaled(
	TString HistName,
	vector<TString> runs,
	vector<TString> Thickness,
	vector<Double_t> Scalings,
	bool Rebin = true
){
	HistData* Data = new HistData;
	Data->Canvas = new TCanvas(HistName, HistName, 100, 10, 1400, 700);
	if(runs.size() == 0){return 0;}
	TLegend* leg = new TLegend(0.6,0.8,0.9,0.9);
	vector<TFile*> files = {};
	Data->Histograms = {};
	Data->Integral = {};
	Data->Integral2to10keV = {};
	for(int i = 0; i < runs.size(); i++){
		files.push_back(File(runs[i]));
		Data->Histograms.push_back((TH1D*)files[i]->Get("Edep"));
		Data->Integral.push_back(Data->Histograms[i]->Integral());
		Data->Integral2to10keV.push_back(Data->Histograms[i]->Integral(2, 10));
		if (i == 0){
			Data->Histograms[i]->SetTitle(HistName);
			Data->Histograms[i]->SetXTitle("E / keV");
			Data->Histograms[i]->SetYTitle("Counts / N_{init} * 0.1 keV ");
			Data->Histograms[i]->SetLineColor(Colors[i]);
			if (Rebin) {Data->Histograms[i]->Rebin(5);
				Data->Histograms[i]->SetYTitle("Counts / 0.5 keV");
			}
			Data->Histograms[i]->Scale(Scalings[i]);
			Data->Histograms[i]->GetXaxis()->SetRangeUser(0.9, 1000);
			Data->Histograms[i]->SetStats(0);
			leg->AddEntry(Data->Histograms[i], Thickness[i],"l");
			Data->Histograms[i]->Draw();
		} else {
			Data->Histograms[i]->SetLineColor(Colors[i]);
			if (Rebin) {Data->Histograms[i]->Rebin(5);}
			Data->Histograms[i]->Scale(Scalings[i]);
			Data->Histograms[i]->SetStats(0);
			leg->AddEntry(Data->Histograms[i], Thickness[i],"l");
			Data->Histograms[i]->Draw("same");
		}
	}
	leg->Draw("same");
	gPad->SetLogy(1);
	gPad->Update();
	return Data;
}


/* Thickness plotted against the integral, this graph for 0 to 100 keV integration range */
TGraphErrors* ThicknessPlot0100(
	vector<Double_t> Thickness,
	HistData* Data
){
	if(Thickness.size() != Data->Integral.size()){return 0;}
	vector<Double_t> dIntegral = {};
	vector<Double_t> dThickness = {};
	for (int i = 0; i < Thickness.size(); i++){
		dIntegral.push_back(sqrt(Data->Integral[i]));					//Statistical Error on Integral
		dThickness.push_back(0);										//No Error on thickness
		}
	TGraphErrors* graph = new TGraphErrors(Thickness.size(), &Thickness[0], &Data->Integral[0], &dThickness[0], &dIntegral[0]);
	graph->SetTitle("Integral 0-100 keV; Pb thickness [mm]; Integral");
	return graph;
}

/* Thickness plotted against the integral, this graph for 2 to 10 keV integration range */
TGraphErrors* ThicknessPlot210(
	vector<Double_t> Thickness,
	HistData* Data
){
	if(Thickness.size() != Data->Integral2to10keV.size()){return 0;}
	vector<Double_t> dIntegral = {};
	vector<Double_t> dThickness = {};
	for (int i = 0; i < Thickness.size(); i++){
		dIntegral.push_back(sqrt(Data->Integral2to10keV[i]));					//Statistical Error on Integral
		dThickness.push_back(0);										//No Error on thickness
		}
	TGraphErrors* graph = new TGraphErrors(Thickness.size(), &Thickness[0], &Data->Integral2to10keV[0], &dThickness[0], &dIntegral[0]);
	graph->SetTitle("Integral 2-10 keV; Pb thickness [mm]; Integral");
	return graph;
}



TCanvas* ThicknessCanvas(
	vector<TGraphErrors*> Graphs,
	vector<TString> Energies,
	TString Name
){
	TCanvas* Canvas = new TCanvas(Name, Name, 100, 10, 1400, 700);
	TLegend* leg = new TLegend(0.6,0.8,0.9,0.9);
	if(Graphs.size() != Energies.size()){return 0;}
	for (int i = 0; i < Graphs.size(); i++){
		if (i == 0){
			Graphs[i]->SetMarkerStyle(33);
			Graphs[i]->SetMarkerSize(2);
			Graphs[i]->SetMarkerColor(Colors[i]);
			leg->AddEntry(Graphs[i], Energies[i], "lp");
			Graphs[i]->Draw("alp");
		} else {
			Graphs[i]->SetMarkerStyle(33);
			Graphs[i]->SetMarkerSize(2);
			Graphs[i]->SetMarkerColor(Colors[i]);
			leg->AddEntry(Graphs[i], Energies[i], "lp");
			Graphs[i]->Draw("lp same");
		}
	}
	leg->Draw("same");
	gPad->Update();
	return Canvas;
	
}

TF1* NormalizedFlat(
	TH1D* Histogram,
	TH1D* DivisionHist
){
	TH1D* NormalHist = (TH1D*)Histogram->Clone("normalizedhist");
	NormalHist->Divide(DivisionHist);
	TCanvas* Canvas = new TCanvas("normalizedhist", "normalizedhist", 100, 10, 1400, 700);
	TF1* SetupFunction = new TF1("Setupfunction", "[0]+[1]*x", 0, 100);
	NormalHist->SetTitle("Flat setup normalized to regular setup");
	NormalHist->GetXaxis()->SetTitle("E / keV");
	NormalHist->GetYaxis()->SetTitle("Counts(flat) / Counts(regular)");
	NormalHist->Fit("Setupfunction", "LS");
	NormalHist->Draw();
	SetupFunction->Draw("same");
	return SetupFunction;
	
	}

typedef struct BgRate {
	Double_t Rate;
	Double_t dRate;
} BackgroundRate;

BgRate SimulatedRate(
	Double_t RateInCube,
	Double_t dRateInCube,
	Double_t InitParticles,
	Double_t Integral,
	Double_t SetupFactor,
	Double_t dSetupFactor
){
	BgRate Background;
	Background.Rate = RateInCube*Integral / (InitParticles*SetupFactor);
	Background.dRate = sqrt(pow(dRateInCube*Integral / (InitParticles*SetupFactor) , 2) + 
							pow(RateInCube*sqrt(Integral) / (InitParticles*SetupFactor) , 2) + 
							pow(RateInCube*Integral*dSetupFactor / (InitParticles*SetupFactor*SetupFactor) , 2));
	return Background;
	}


void Simulation(){
	/* Pb Thicknesses: */
	/* Parameters for one Energy E, including run-ID's, respective thicknesses in Double and Sting format */
	TString NamePb1 = "Pb Shield thickness comparison at 511 keV";
	vector<TString> runsPb1 = {"run016", "run019", "run022", "run025", "run028", "run031", "run034"};
	vector<Double_t> PBT1 = {5, 10, 20, 30, 40, 50, 60}; 									//Thicknesses in mm
	vector<TString> PBTString1 = {"5 mm", "10 mm", "20 mm", "30 mm", "40 mm", "50 mm", "60 mm"};
	
	/* Parameters for one Energy E, including run-ID's, respective thicknesses in Double and Sting format */
	TString NamePb2 = "Pb Shield thickness comparison at 1461 keV";
	vector<TString> runsPb2 = {"run017", "run020", "run023", "run026", "run029", "run032", "run035", "run040", "run042", "run044", "run046"};
	vector<Double_t> PBT2 = {5, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; 									//Thicknesses in mm
	vector<TString> PBTString2 = {"5 mm", "10 mm", "20 mm", "30 mm", "40 mm", "50 mm", "60 mm", "70 mm", "80 mm", "90 mm", "100 mm"};
	
	/* Parameters for one Energy E, including run-ID's, respective thicknesses in Double and Sting format */
	TString NamePb3 = "Pb Shield thickness comparison at 2615 keV";
	vector<TString> runsPb3 = {"run018", "run021", "run024", "run027", "run030", "run033", "run036", "run041", "run043", "run045", "run047"};
	vector<Double_t> PBT3 = {5, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; 									//Thicknesses in mm
	vector<TString> PBTString3 = {"5 mm", "10 mm", "20 mm", "30 mm", "40 mm", "50 mm", "60 mm", "70 mm", "80 mm", "90 mm", "100 mm"};
	
	/* Cu Thicknesses */
	TString NameCu1 = "Cu Shield thickness comparison at 2615 keV";
	vector<TString> runsCu1 = {"run039", "run056", "run057", "run058", "run059", "run060", "run062"};
	vector<Double_t> CUT1 = {0, 1, 2, 3, 4, 5, 6}; 									//Thicknesses in mm
	vector<TString> CUTString1 = {"0 mm", "1 mm", "2 mm", "3 mm", "4 mm", "5 mm", "6 mm"};
	
	/* PMMA Thicknesses */
	TString NamePMMA1 = "PMMA Shield thickness comparison at 2615 keV";
	vector<TString> runsPMMA1 = {"run060", "run061", "run063", "run064", "run065", "run066"};
	vector<Double_t> PMMAT1 = {0, 1, 2, 3, 4, 5}; 									//Thicknesses in mm
	vector<TString> PMMATString1 = {"0 mm", "1 mm", "2 mm", "3 mm", "4 mm", "5 mm"};
	
	/* Histogram Data for one energy (first parameter), for more details see typedef struct HistData*/
	HistData* DataPb511 = EnergyHist(NamePb1, runsPb1, PBTString1);			//Pb, 511 keV
	HistData* DataPb1461 = EnergyHist(NamePb2, runsPb2, PBTString2);		//Pb 1461 keV
	HistData* DataPb2615 = EnergyHist(NamePb3, runsPb3, PBTString3);		//Pb, 2615 keV

	HistData* DataCu2615 = EnergyHist(NameCu1, runsCu1, CUTString1, false);		//CU, 2615 keV
	HistData* DataPMMA2615 = EnergyHist(NamePMMA1, runsPMMA1, PMMATString1, false);	//PMMA, 2615 keV

	/* Energies Collected */
	vector<TString> EnergiesPb = {"2615 keV", "1461 keV", "511 keV"};

	
	/* Vector for Integral(thickness) graph collection */
	//First: 0 - 100 keV
	vector<TGraphErrors*> GraphsPb0100 = {};
	GraphsPb0100.push_back(ThicknessPlot0100(PBT3, DataPb2615));
	GraphsPb0100.push_back(ThicknessPlot0100(PBT2, DataPb1461));
	GraphsPb0100.push_back(ThicknessPlot0100(PBT1, DataPb511));
	//Second: 2 - 10 keV
	vector<TGraphErrors*> GraphsPb210 = {};
	GraphsPb210.push_back(ThicknessPlot210(PBT3, DataPb2615));
	GraphsPb210.push_back(ThicknessPlot210(PBT2, DataPb1461));
	GraphsPb210.push_back(ThicknessPlot210(PBT1, DataPb511));
	
	TCanvas* CanvasPb0100 = ThicknessCanvas(GraphsPb0100, EnergiesPb, "0to100keV");
	TCanvas* CanvasPb210 = ThicknessCanvas(GraphsPb210, EnergiesPb, "2to10keV");



	TString NameComp1461 = "Setup comparison at 1461 keV";
	vector<TString> runsComp1461 = {"run054", "run055"};	
	vector<Double_t> Comp1461 = {1, 0.1}; 									//Thicknesses in mm
	vector<TString> CompString1461 = {"Flat Setup", "Regular Setup"};
	HistData* ComparisonSetups1461 = EnergyHistScaled(NameComp1461, runsComp1461, CompString1461, Comp1461); 
	Double_t IntFlat1461 = ComparisonSetups1461->Integral[0];
	Double_t IntReg1461 = ComparisonSetups1461->Integral[1];
	Double_t SetupFactor1461 = 10*IntFlat1461/IntReg1461;
	Double_t dSetupFactor1461 = sqrt(pow(10*sqrt(IntFlat1461)/IntReg1461, 2) + pow(10*IntFlat1461*sqrt(IntReg1461)/pow(IntReg1461, 2), 2));
	cout << "Setup factor at 1461 keV = " << SetupFactor1461 << " +/- " << dSetupFactor1461 << endl;
	
	
	TString NameComp2615 = "Setup comparison at 2615 keV";
	vector<TString> runsComp2615 = {"run073", "run074"};	
	vector<Double_t> Comp2615 = {1, 0.1}; 									//Thicknesses in mm
	vector<TString> CompString2615 = {"Flat Setup", "Regular Setup"};
	HistData* ComparisonSetups2615 = EnergyHistScaled(NameComp2615, runsComp2615, CompString2615, Comp2615); 
	Double_t IntFlat2615 = ComparisonSetups2615->Integral[0];
	Double_t IntReg2615 = ComparisonSetups2615->Integral[1];
	Double_t SetupFactor2615 = 10*IntFlat2615/IntReg2615;
	Double_t dSetupFactor2615 = sqrt(pow(10*sqrt(IntFlat2615)/IntReg2615, 2) + pow(10*IntFlat2615*sqrt(IntReg2615)/pow(IntReg2615, 2), 2));
	cout << "Setup factor at 2615 keV = " << SetupFactor2615 << " +/- " << dSetupFactor2615 << endl;
	
	/* Spectra for the 5 mm, 4 mm, 64 mm setup from Bea's work */
	TString Name5464 = "Setup with 5 mm PMMA, 4 mm Cu, 64 mm Pb";
	vector<TString> run5464 = {"run076", "run077"};
	vector<TString> Legend5464 = {"1461 keV", "2615 keV"};
	HistData* Setup5464 = EnergyHist(Name5464, run5464, Legend5464, false);
	
	
	BgRate BeaSetup1461 = SimulatedRate(150, 80, 10000000, Setup5464->Integral[0], SetupFactor1461, dSetupFactor1461);
	BgRate BeaSetup2615 = SimulatedRate(52, 27, 10000000, Setup5464->Integral[1], SetupFactor2615, dSetupFactor2615);
	cout << "1461 keV rate for 5 mm, 4 mm, 64 mm = " << BeaSetup1461.Rate << " +/- " << BeaSetup1461.dRate << endl;
	cout << "2615 keV rate for 5 mm, 4 mm, 64 mm = " << BeaSetup2615.Rate << " +/- " << BeaSetup2615.dRate << endl;	
	
	cout << "Total gamma Bg rate = " << BeaSetup1461.Rate + BeaSetup2615.Rate << " +/- " << sqrt(pow(BeaSetup1461.dRate, 2) + pow(BeaSetup2615.dRate, 2)) << endl;
	/*
	for (int i=0;i<DataBox->Integral.size();i++){
		cout << PBTString3[i] << " " << DataBox->Integral[i] << endl;
		}
	*/
}
