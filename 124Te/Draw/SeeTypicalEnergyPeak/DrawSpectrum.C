#include "TString.h"

void DrawSpectrum()
// Draw a 1D spectrum with user-defined binning. Spectrum is given as a tree in a root file
{
    // Data selection
    TString filename = "/home/iktp/Geant4-Work/NewStart/TargetGeoOptimisation/build/Tellurium230622.root";
    TString treename = "Stopped";
    TString leafname = "E";
    // Axis properties
    TString Eunit = "MeV";
    Double_t Ebinwidth = 0.001;
    Double_t Emax = 7;

    // Open the root file
    TFile* infile = TFile::Open(filename.Data(), "READ");
    if (!infile) cout << "Could not open " << filename << endl;

    // Get the tree
    TTree* tree = (TTree*)infile->Get(treename.Data());
    if (!tree) cout << "Could not get " << treename << " from file " << infile->GetName() << endl;

    // Create an empty histogram with preferred binning
    TString histname = "hist";
    stringstream titlestream;
    titlestream << "; E / " << Eunit << "; counts per " << Ebinwidth << " " << Eunit;
    TH1D* hist = new TH1D(histname.Data(), titlestream.str().c_str(), Emax/Ebinwidth, 0, Emax);

    // Fill the histogram with tree entries
    TString varexp = leafname + ">>" + histname; // variable expression. Here we define which leaf is drawn into which histogram. A "+" at the end adds entries to an already filled histogram.
    TString selection = ""; // selection string. Defines conditions on which entries to draw
    TString option = "goff"; // draw option. With "goff" the histogram is not shown automatically.
    tree->Draw(varexp.Data(), selection.Data(), option.Data());

    // Draw histogram
    TCanvas* c = new TCanvas();
    gPad->SetLogy();
    gPad->SetTicks(1,1);
    hist->SetStats(0);
    hist->Draw("hist");
}
