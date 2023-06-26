//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file HPGeSD.cc
/// \brief Implementation of the HPGeSD class

#include "HPGeSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4UnitsTable.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "G4Gamma.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HPGeSD::HPGeSD(const G4String& name,
                         const G4String& hitsCollectionName) 
 : G4VSensitiveDetector(name),
   fHitsCollection(NULL)
{
  collectionName.insert(hitsCollectionName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HPGeSD::~HPGeSD() 
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HPGeSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection

  fHitsCollection 
    = new HPGeHitsCollection(SensitiveDetectorName, collectionName[0]); 

  // Add this collection in hce

  G4int hcID 
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection ); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool HPGeSD::ProcessHits(G4Step* aStep, 
                                     G4TouchableHistory*)
{           

          // energy deposit
          G4double edep = aStep->GetTotalEnergyDeposit() / MeV;
          if (edep==0.) return false;

          G4Track * track =  aStep->GetTrack();

    
          std::ifstream readFlagForRealSignalInHPGeSD("FlagForRealSignal.txt");
          G4int FlagForRealSignalValueInHPGeSD;
          readFlagForRealSignalInHPGeSD >> FlagForRealSignalValueInHPGeSD;
       
  if (FlagForRealSignalValueInHPGeSD == 1)
    {
        G4cout<<"In HPGeSD::ProcessHits, It is signal from muon capture!\n"<<G4endl;

       if(track->GetDefinition()==G4Gamma::GammaDefinition())
       {

            G4cout<<"In HPGeSD::ProcessHits, It is signal Gamma from muon capture!\n"<<G4endl;

            G4String LogicalVolumeName = track->GetLogicalVolumeAtVertex()->GetName();
            
            if(LogicalVolumeName.compare("logical_Te_target")==0)
            {

               G4cout<<"In HPGeSD::ProcessHits, It is Gamma from muon capture and produced in target !\n"<<G4endl;

               G4cout << "DEBUG: Hit with energy " << G4BestUnit(edep, "Energy") << G4endl;
         
         
               HPGeHit* newHit = new HPGeHit();
             
               newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
               newHit->SetVolumeNb(aStep->GetPreStepPoint()->GetTouchableHandle()
                                                            ->GetCopyNumber());
               newHit->SetEdep(edep);
               newHit->SetPos (aStep->GetPostStepPoint()->GetPosition());
             
               fHitsCollection->insert( newHit );
             
               //newHit->Print();
         
           }
       }
    } 


  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HPGeSD::EndOfEvent(G4HCofThisEvent*)
{ // Do summary of one event using its HitsCollection
//  G4int nofHits = fHitsCollection->entries();
//  G4double totEdep = 0.0;
//  for (G4int i = 0; i < nofHits; i++) {
//    HPGeHit *hit = (*fHitsCollection)[i];
//    hit->Print();
//    totEdep += hit->GetEdep();
//    G4cout << "total Edep: " << totEdep << G4endl;
//  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
