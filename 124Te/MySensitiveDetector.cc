#include "MySensitiveDetector.hh"
#include "G4UnitsTable.hh"
#include "G4Gamma.hh"
#include "G4PhysicalConstants.hh"
#include "G4Neutron.hh"
#include "G4Electron.hh"
#include "G4GenericIon.hh"
#include "event.hh"
#include "G4EventManager.hh"
#include "G4SystemOfUnits.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
  
}

MySensitiveDetector::~MySensitiveDetector()
{
}

G4bool MySensitiveDetector::ProcessHits(G4Step * aStep, G4TouchableHistory * ROhist)//
{

    G4Track * track =  aStep->GetTrack();
    // track->SetTrackStatus(fStopButAlive);
    // track->SetTrackStatus(fStopAndKill);

/*
   G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
       if (track->GetDefinition()==G4Gamma::GammaDefinition())
   {
     G4cout<<"track->GetKineticEnergy() in SensitiveDetector: "
           <<G4BestUnit(track->GetKineticEnergy(),"Energy")
           <<"; global time: "<<G4BestUnit(track->GetGlobalTime() ,"Time")
           <<G4endl;
     analysisManager->FillH1(1, track->GetKineticEnergy());
     analysisManager->FillH1(2, track->GetGlobalTime());
   }

*/

    G4StepPoint * preStepPoint  =  aStep->GetPreStepPoint();
    G4StepPoint * postStepPoint = aStep->GetPostStepPoint();
    const G4VProcess* Process   =  postStepPoint->GetProcessDefinedStep();    
    std::string postStepProcessName = Process->GetProcessName();          
    const G4String& ProcessName = Process->GetProcessName();
    G4ProcessType  ProcessType  = Process->GetProcessType(); 


    const G4TouchableHandle& preStepPointTouchableHandle = preStepPoint->GetTouchableHandle(); // not a pointer, not dangerous
    G4VPhysicalVolume* preStepPointVolume = preStepPointTouchableHandle->GetVolume(); // pointer, check for NULL!
    G4LogicalVolume* preStepPointLogicalVolume = preStepPointVolume->GetLogicalVolume(); // pointer, check for NULL! // nullptr
    G4String preStepPointVolumeName  = preStepPointLogicalVolume->GetName();
  
    const G4TouchableHandle& postStepPointTouchableHandle = postStepPoint->GetTouchableHandle(); // not a pointer, not dangerous
    G4VPhysicalVolume* postStepPointVolume = postStepPointTouchableHandle->GetVolume(); // pointer, check for NULL!
    G4LogicalVolume* postStepPointLogicalVolume = postStepPointVolume->GetLogicalVolume(); // pointer, check for NULL! // nullptr
    G4String postStepPointVolumeName  = postStepPointLogicalVolume->GetName();


    G4ThreeVector preStep = preStepPoint->GetPosition();
    G4ThreeVector postStep = postStepPoint->GetPosition();
    G4ThreeVector MuonStoppedPosition (0.0,0.0,0.0);
    //postStepPoint->GetProcessDefinedStep()->GetProcessName();
    

/*
    G4cout<<"step in MySensitiveDetector --------------------"
          <<"\npreStep: "<<std::setw(6) << G4BestUnit(preStep,"Length")
          <<"\npreStepPointVolumeName: "<<std::setw(6) << preStepPointVolumeName 
          <<"\nProcessName: "<<std::setw(6) << ProcessName
          <<"\nProcessType: "<<std::setw(6) << ProcessType
          <<"\nposStep: "<<std::setw(6) << G4BestUnit(postStep,"Length")
          <<"\npostStepPointVolumeName: "<<std::setw(6) << postStepPointVolumeName 
          <<"\nGetTotalEnergyDeposit: "<< G4BestUnit(aStep->GetTotalEnergyDeposit(),"Energy")
          <<"\nTrack Kinetic Energy: "<< G4BestUnit(track->GetKineticEnergy(),"Energy")
          <<"\nTrack Total Energy: "<<  G4BestUnit(track->GetTotalEnergy(),"Energy")
          <<"\n"
          << G4endl;

*/



  G4ThreeVector direction = track->GetMomentumDirection();
  G4double theta = direction.theta(), phi = direction.phi();

  if (phi < 0.) phi += twopi;
  G4double cost = std::cos(theta);

  G4int flag = 10;

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
if(postStepProcessName=="muMinusCaptureAtRest") 
  {
    

   analysisManager->FillNtupleDColumn(8, 0,preStep.getX());   
   analysisManager->FillNtupleDColumn(8, 1,preStep.getY());   
   analysisManager->FillNtupleDColumn(8, 2,preStep.getZ());   
   analysisManager->AddNtupleRow(8);
  
  MuonStoppedPosition = preStep;

  }


          /*
           if ((track->GetDefinition() == G4Gamma::GammaDefinition() ||
                track->GetDefinition() == G4Neutron::NeutronDefinition() ||
                track->GetDefinition() == G4Electron::ElectronDefinition()||
                track->GetDefinition()->GetParticleType() == "nucleus")&&postStepPoint->GetStepStatus() == fGeomBoundary)
          */
           if (track->GetDefinition()==G4Gamma::GammaDefinition()&&postStepPoint -> GetStepStatus() == fGeomBoundary )
            {
             

             if (track->GetCreatorProcess()->GetProcessName().compare("muMinusCaptureAtRest")==0)
                 {


                        G4String LogicalVolumeName = track->GetLogicalVolumeAtVertex()->GetName();
                      if(LogicalVolumeName.compare("logical_Te_target")==0)
                      {
       
       
                         std::ifstream readFlagForRealSignal("FlagForRealSignal.txt");
                         G4int FlagForRealSignalValue;
                         //if(readFlagForRealSignal)
                         //{
                           readFlagForRealSignal >> FlagForRealSignalValue;
                         //}
       
                        //   G4cout<<"trackingAction->GetFlagForRealSignal(): "<<trackingAction->GetFlagForRealSignal()<<G4endl;
                        if (FlagForRealSignalValue == 1)
                       // if (trackingAction->GetFlagForRealSignal() ==1)
                         {  
                             G4cout<<"FlagForRealSignalValue: "<<FlagForRealSignalValue<<G4endl;     
                        
                             G4cout<<"\nCaptured! step in MySensitiveDetector--------------------"
                             <<"\npreStep: "<<std::setw(6) << G4BestUnit(preStep,"Length")
                             <<"\npostStep: "<<std::setw(6) << G4BestUnit(postStep,"Length")
                             <<"\npostStep Z position: "<<std::setw(6) << G4BestUnit(postStep.getZ() ,"Length") 
                             <<"\npreStepPointLogicalVolumeName: "<<std::setw(6) << preStepPointVolumeName 
                             <<"\nProcessName: "<<std::setw(6) << ProcessName
                             <<"\npostStepPointLogicalVolumeName: "<<std::setw(6) << postStepPointVolumeName 
                             <<"\nTrack name: "<<std::setw(6)<<track->GetDefinition()->GetParticleName()
                             <<"\ntrack->GetTotalEnergy(): "<< G4BestUnit(track->GetTotalEnergy() ,"Energy") 
                             <<"\npostStepPoint->GetTotalEnergy(): "<< G4BestUnit(postStepPoint->GetTotalEnergy() ,"Energy") 
                             <<"\ntrack->GetVertexPosition(): "<<G4BestUnit(track->GetVertexPosition() ,"Length") 
                             <<"\ntrack->GetPosition(): "<<G4BestUnit(track->GetPosition() ,"Length") 
                             <<"\n"
                             << G4endl;


           // fill ntuple and histogram
         
                 analysisManager->FillH1(1, track->GetKineticEnergy());
                 analysisManager->FillH1(3, phi);
                 analysisManager->FillH1(4, cost);
             
                 if(track->GetParentID()==1)
                 {
                   //G4cout<<"track->GetDefinition() when parents ID are 1: "<<track->GetDefinition()->GetParticleName()<<G4endl;
                   analysisManager->FillH1(5, track->GetKineticEnergy());  
                   analysisManager->FillNtupleDColumn(3, 0, track->GetKineticEnergy());     
                   analysisManager->AddNtupleRow(3);
                 }
                 else
                 {
                   analysisManager->FillH1(6, track->GetKineticEnergy());  
                   analysisManager->FillNtupleDColumn(4, 0, track->GetKineticEnergy());     
                   analysisManager->AddNtupleRow(4);
                 }
         
         
                 analysisManager->FillNtupleDColumn(1, 0,postStepPoint->GetTotalEnergy() / MeV);    
         //        analysisManager->FillNtupleDColumn(1, 0,track->GetKineticEnergy());    
                 analysisManager->FillNtupleDColumn(1, 1,track->GetGlobalTime());
                 analysisManager->FillNtupleDColumn(1, 2,phi);
                 analysisManager->FillNtupleDColumn(1, 3,cost);      
                 analysisManager->FillNtupleDColumn(1, 4,theta);      
                 analysisManager->FillNtupleSColumn(1, 5,track->GetDefinition()->GetParticleName());      
                 analysisManager->FillNtupleDColumn(1, 6,postStep.getX() / mm);      
                 analysisManager->FillNtupleDColumn(1, 7,postStep.getY() / mm);      
                 analysisManager->FillNtupleDColumn(1, 8,postStep.getZ() / mm);      
                 analysisManager->AddNtupleRow(1);
         



         //  // fill ntuple and histogram
         //
         //        analysisManager->FillH1(1, track->GetKineticEnergy());
         //        analysisManager->FillH1(2, track->GetGlobalTime());
         //        analysisManager->FillH1(3, phi);
         //        analysisManager->FillH1(4, cost);
         //    
         //        if(track->GetParentID()==1)
         //        {
         //          analysisManager->FillH1(5, track->GetKineticEnergy());  
         //          analysisManager->FillNtupleDColumn(3, 0, track->GetKineticEnergy());     
         //          analysisManager->AddNtupleRow(3);
         //        }
         //        else
         //        {
         //          analysisManager->FillH1(6, track->GetKineticEnergy());  
         //          analysisManager->FillNtupleDColumn(4, 0, track->GetKineticEnergy());     
         //          analysisManager->AddNtupleRow(4);
         //        }
         //
         //
         //        analysisManager->FillNtupleDColumn(1, 0,track->GetKineticEnergy());    
         //        analysisManager->FillNtupleDColumn(1, 1,track->GetGlobalTime());
         //        analysisManager->FillNtupleDColumn(1, 2,phi);
         //        analysisManager->FillNtupleDColumn(1, 3,cost);      
         //        analysisManager->FillNtupleDColumn(1, 4,theta);      
         //        analysisManager->FillNtupleIColumn(1, 5,flag);      
         //        analysisManager->AddNtupleRow(1);
                 }
               }            
             }
            
          } 



  return true;

}

