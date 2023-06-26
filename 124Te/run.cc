#include "run.hh"
#include <iostream>
#include <fstream>
//#include "G4VAnalysisManager.hh"

//MyrunAction::MyrunAction() : fHowManyMuMinusCapturesDidWeHave(0)
MyrunAction::MyrunAction()
{


 //   fMuMinusCaptures = 0;


  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //analysisManager->SetFileName("TEST.root"); 
            
  G4int nbins = 200;
  G4double vmin = 0.;
  G4double vmax = 2.;

  analysisManager->SetHistoDirectoryName("histo");
  analysisManager->SetFirstHistoId(1);

  G4int id = analysisManager->CreateH1("h1.1","Gamma kinetic energy", nbins, vmin, vmax);
  analysisManager->SetH1Activation(id, false);

  //id = analysisManager->CreateH1("h1.2","Gamma time spectrum", nbins, vmin, vmax);
  id = analysisManager->CreateH1("h1.2","Gamma time spectrum", nbins, 0, 800);
  analysisManager->SetH1Activation(id, false);

  //id = analysisManager->CreateH1("h1.3","Gamma azimuth angle distribution", nbins, vmin, vmax);
  id = analysisManager->CreateH1("h1.3","Gamma azimuth angle distribution", nbins, 0, 6.5);
  analysisManager->SetH1Activation(id, false);

  //id = analysisManager->CreateH1("h1.3","Gamma cos#theta distribution", nbins, vmin, vmax);
  id = analysisManager->CreateH1("h1.4","Gamma cos#theta distribution", nbins, -1, 1);
  analysisManager->SetH1Activation(id, false);

  id = analysisManager->CreateH1("h1.5","Signal Gamma Energy", nbins, 0, 10);
  analysisManager->SetH1Activation(id, false);

  id = analysisManager->CreateH1("h1.6","Background Gamma Energy", nbins, 0, 10);
  analysisManager->SetH1Activation(id, false);



  // nTuples


  analysisManager->SetFirstNtupleId(1);       
  analysisManager->CreateNtuple("Escaped", "all secondary particles that escaped from the surface of target which produced by muon capture");
  analysisManager->CreateNtupleDColumn("E");    //column 0
  analysisManager->CreateNtupleDColumn("T");          //column 1
  analysisManager->CreateNtupleDColumn("phi");          //column 2
  analysisManager->CreateNtupleDColumn("cost");          //column 3
  analysisManager->CreateNtupleDColumn("Theta");          //column 4
//  analysisManager->CreateNtupleIColumn("Flag");          //column  5
  analysisManager->CreateNtupleSColumn("particleName");          //column 5
  analysisManager->CreateNtupleDColumn("EscapedXdirection");    //column 6
  analysisManager->CreateNtupleDColumn("EscapedYdirection");    //column 7
  analysisManager->CreateNtupleDColumn("EscapedZdirection");    //column 8
  analysisManager->FinishNtuple(1);

  analysisManager->CreateNtuple("Nmuon", "Number of Muon Stopped");
  analysisManager->CreateNtupleDColumn("Nmuons");    //column 0
  analysisManager->FinishNtuple(2);

  analysisManager->CreateNtuple("EGammaSignal", "Signal Gamma Energy");
  analysisManager->CreateNtupleDColumn("EGammaSig");    //column 0
  analysisManager->FinishNtuple(3);

  analysisManager->CreateNtuple("EGammaBackground", "Background Gamma Energy");
  analysisManager->CreateNtupleDColumn("EGammaBkg");    //column 0
  analysisManager->FinishNtuple(4);

  analysisManager->CreateNtuple("NmuonScintillator", "Number of Muon Stopped in Scintillator");
  analysisManager->CreateNtupleDColumn("NmuonScintillator");    //column 0
  analysisManager->FinishNtuple(5);

  analysisManager->CreateNtuple("NmuonTarget", "Number of Muon Stopped in Target");
  analysisManager->CreateNtupleDColumn("NmuonTarget");    //column 0
  analysisManager->FinishNtuple(6);

  analysisManager->CreateNtuple("NmuonWorld", "Number of Muon Stopped in World");
  analysisManager->CreateNtupleDColumn("NmuonWorld");    //column 0
  analysisManager->FinishNtuple(7);

  analysisManager->CreateNtuple("MuonStoppedDepth", "Muon Stopped Depth in Target");
  analysisManager->CreateNtupleDColumn("MuonStoppedDepthXdirection");    //column 0
  analysisManager->CreateNtupleDColumn("MuonStoppedDepthYdirection");    //column 1
  analysisManager->CreateNtupleDColumn("MuonStoppedDepthZdirection");    //column 2
  analysisManager->FinishNtuple(8);

  analysisManager->CreateNtuple("EGammaSpectrumInHPGeactiveCrystal", "Gamma Energy Spectrum in HPGe activeCrystal");
  analysisManager->CreateNtupleDColumn("EGammaSpectrumInHPGeactiveCrystal");    //column 0
  analysisManager->FinishNtuple(9);


  analysisManager->CreateNtuple("Stopped", " all secondary particles produced by muon capture in target");
  analysisManager->CreateNtupleDColumn("E");    //column 0
  analysisManager->CreateNtupleDColumn("T");          //column 1
  analysisManager->CreateNtupleDColumn("StoppedXposition");    //column 2
  analysisManager->CreateNtupleDColumn("StoppedYposition");    //column 3
  analysisManager->CreateNtupleDColumn("StoppedZposition");    //column 4
  analysisManager->CreateNtupleSColumn("particleName");          //column 5
  analysisManager->FinishNtuple(10);


}

MyrunAction::~MyrunAction()
{
      delete G4AnalysisManager::Instance();
}

void MyrunAction::BeginOfRunAction(const G4Run* run)
{
    fMuMinusCaptures = 0;
    fMuMinusCapturesInScintillator = 0;
    fMuMinusCapturesInTarget = 0;
    fMuMinusCapturesInWorld = 0;
//    fMuMinusCapturesInRealTarget = 0;


  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();


  G4int RunID = run->GetRunID();
  std::stringstream strRunID;
  strRunID << RunID;
  G4cout<<"RunID: "<<RunID<<G4endl;
  analysisManager->OpenFile("TEST"+strRunID.str()+".root");
  //analysisManager->OpenFile();


}

void MyrunAction::EndOfRunAction(const G4Run* run)
{

   std::ofstream myfile("example.txt", std::ios_base::app | std::ios_base::out);
   myfile << "fMuMinusCaptures: "<<fMuMinusCaptures<<"   "<<fMuMinusCaptures*100./100000<<" in RunID: " <<run->GetRunID()<<G4endl;
   myfile.close();


   std::ofstream myfile1("deal.txt", std::ios_base::app | std::ios_base::out);
   myfile1 <<fMuMinusCaptures*100./100000<<"  " <<run->GetRunID()<<G4endl;
   myfile1.close();

    std::cout << "We had some captures: " << fMuMinusCaptures << " in RunID: " <<run->GetRunID()<<std::endl;





   std::ofstream myfileTarget("exampleTarget.txt", std::ios_base::app | std::ios_base::out);
   myfileTarget << "fMuMinusCapturesInTarget: "<<fMuMinusCapturesInTarget<<"   "<<fMuMinusCapturesInTarget*100./100000<<" in RunID: " <<run->GetRunID()<<G4endl;
   myfileTarget.close();


   std::ofstream myfile1Target("dealTarget.txt", std::ios_base::app | std::ios_base::out);
   myfile1Target <<fMuMinusCapturesInTarget*100./100000<<"  " <<run->GetRunID()<<G4endl;
   myfile1Target.close();

    std::cout << "We had some captures in target: " << fMuMinusCapturesInTarget << " in RunID: " <<run->GetRunID()<<std::endl;







    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
 
 
    analysisManager->FillNtupleDColumn(2, 0,fMuMinusCaptures);     
    analysisManager->AddNtupleRow(2);

    analysisManager->FillNtupleDColumn(5, 0,fMuMinusCapturesInScintillator);     
    analysisManager->AddNtupleRow(5);

    analysisManager->FillNtupleDColumn(6, 0,fMuMinusCapturesInTarget);     
    analysisManager->AddNtupleRow(6);

    analysisManager->FillNtupleDColumn(7, 0,fMuMinusCapturesInWorld);     
    analysisManager->AddNtupleRow(7);

    analysisManager->Write();
    analysisManager->CloseFile();

}


void MyrunAction::PlusOneMinusCaptureInRun()
{
    fMuMinusCaptures++;
}

void MyrunAction::PlusOneMinusCaptureInRunInScintillator()
{
    fMuMinusCapturesInScintillator++;
}

void MyrunAction::PlusOneMinusCaptureInRunInTarget()
{
    fMuMinusCapturesInTarget++;
}

void MyrunAction::PlusOneMinusCaptureInRunInWorld()
{
    fMuMinusCapturesInWorld++;
}

