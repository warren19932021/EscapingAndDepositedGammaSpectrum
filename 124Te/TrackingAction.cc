#include "TrackingAction.hh"

#include "run.hh"
#include "G4Electron.hh"
#include "G4Gamma.hh"
#include "G4Track.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"
#include "G4SystemOfUnits.hh"


//#include "MySensitiveDetector.hh"
//#include "G4SDManager.hh"

//------ with particle gun generator member variable------- 
//MyTrackingAction::MyTrackingAction(MyGunPrimaryGenerator* prim)
//:G4UserTrackingAction(),
// fPrimary(prim)
//{}



MyTrackingAction::MyTrackingAction()
//:G4UserTrackingAction()
:G4UserTrackingAction(), FlagForRealSignal(0)
{
  //G4cout<<"The constructor function of MyTrackingAction is called!"<<G4endl;
}

void MyTrackingAction::PreUserTrackingAction(const G4Track* aTrack )
{
//    G4cout<<"\nNow PreUserTrackingAction start to run: "<<G4endl;
//G4cout<<"FlagForRealSignal in the begin of Action: "<<FlagForRealSignal<<G4endl;



   G4int parentID = aTrack->GetParentID();
   const G4VProcess* p_process = aTrack->GetCreatorProcess();


/*
  if(p_process)
  {
    G4String secondaryName = aTrack->GetDefinition()->GetParticleName();
    auto secEkin = G4BestUnit(aTrack->GetKineticEnergy(), "Energy");
    auto position = G4BestUnit(aTrack->GetPosition(), "Length");
    G4String processName = p_process->GetProcessName();
    G4String LogicalVolumeName = aTrack->GetLogicalVolumeAtVertex()->GetName();

     if(parentID == 1) // was primary muon
      {
        if(processName.compare("muMinusCaptureAtRest") == 0)
        {
          if(LogicalVolumeName.compare("logical_Te_target")==0)
            { 
              
               G4cout<<"I get you! baby!"<<G4endl;
               G4cout<<"trackID: "<<aTrack->GetTrackID()
               <<"; secondaryName: "<<secondaryName
               <<"; LogicalVolumeName: "<<LogicalVolumeName
               <<"; secEkin: "<<secEkin
               <<"; position: "<<position
               <<G4endl;

               G4cout<<"FlagForRealSignal: "<<FlagForRealSignal<<G4endl;
               // Is relevant secondary, track this!
               // Save some variable here to mark this trjaectory and enable further stuff
              
            }
        }
      }
  }

*/


  // ---

   

//   G4double TrackKineticEnergy = aTrack->GetKineticEnergy();


/*
   G4cout<<"Track Action in Track Action--------------------"
         <<"\nTrackID: "<<aTrack->GetTrackID()
         <<"\nTrack Kinetic Energy: "<<G4BestUnit(aTrack->GetKineticEnergy(),"Energy")
         <<"\nTrack Total Energy: "<<G4BestUnit(aTrack->GetTotalEnergy(),"Energy")
         <<"\nglobal time: "<<G4BestUnit(aTrack->GetGlobalTime() ,"Time")
         <<"\nlocal time: "<<G4BestUnit(aTrack->GetLocalTime() ,"Time")
         <<"\nproper time: "<<G4BestUnit(aTrack->GetProperTime() ,"Time")
         <<"\n"<<G4endl;

*/
    //    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    //    if (aTrack->GetDefinition()==G4Gamma::GammaDefinition())
    //    {
          //  G4cout<<"aTrack->GetKineticEnergy(): "<<G4BestUnit(aTrack->GetKineticEnergy(),"Energy")<<G4endl;
          //  analysisManager->FillH1(5, aTrack->GetKineticEnergy());
          //  analysisManager->FillNtupleDColumn(1, 4,aTrack->GetKineticEnergy());     
    //    }

//    G4cout<<"Now PretUserTrackingAction finished!\n"<<G4endl;

}


void MyTrackingAction::PostUserTrackingAction(const G4Track* track)
{

   std::ofstream myfile("FlagForRealSignal.txt");

    
//    G4cout<<"\nNow PostUserTrackingAction start to run: "<<G4endl;

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    const G4Step* step = track->GetStep();
    const G4VProcess* process = step->GetPostStepPoint()->GetProcessDefinedStep();
    //G4String PhysicalVolumeName = step->GetPostStepPoint()->GetPhysicalVolume()->GetName();
 
 

    //MySensitiveDetector* sensitiveDetector = static_cast<MySensitiveDetector*>(G4SDManager::GetSDMpointer()->FindSensitiveDetector("logical_Te_target"));

    // Check if the track is from a muon capture process
    //if (track->GetTrackID() == 1 ) {
    //if (track->GetTrackID() == 1 &&  process &&  process->GetProcessName() == "muMinusCaptureAtRest") {
    //if (track->GetTrackID() == 1 && track->GetTrackStatus() == fStopAndKill && process &&  process->GetProcessName() == "muMinusCaptureAtRest" && PhysicalVolumeName.compare("physTarget")==0) {
    if (track->GetTrackID() == 1)
    {
     if( track->GetTrackStatus() == fStopAndKill && process &&  (process->GetProcessName()).compare("muMinusCaptureAtRest")==0) {
        // Get the number of secondaries
        G4int nSecondaries = step->GetNumberOfSecondariesInCurrentStep();
        auto secondary  = step->GetSecondaryInCurrentStep();

        if(nSecondaries){
           for (size_t i=0; i<nSecondaries;i++){
           
                 auto secstep = (*secondary)[i];
                 G4String secondaryName = secstep->GetDefinition()->GetParticleName();

               //if(secondaryName.contains("Sb124")||secondaryName.contains("Sb127")||secondaryName.contains("gamma"))
               if(secondaryName.contains("Sb124"))
               {
                 FlagForRealSignal = 1;
                 //fEventAction->SetContainsSb124();
                 break;
               }
               //else
               //{
               //  FlagForRealSignal = 0;
               //  break;
               //}

           }
       }
   


         if(nSecondaries&& FlagForRealSignal == 1){
           for (size_t i=0; i<nSecondaries;i++){
           
                 auto secstep = (*secondary)[i];
                 G4String secondaryName = secstep->GetDefinition()->GetParticleName();
                 auto secondaryID = secstep->GetTrackID();
                 auto secEkin = G4BestUnit(secstep->GetKineticEnergy(), "Energy");

                 G4cout<<"nSecondaries: "<<nSecondaries<<G4endl;
                // G4cout<<"Contains Sb124!!!"<<G4endl;
                /* 
                 if (secondaryName.compare("e-")==0||
                 secondaryName.compare("gamma")==0||
                 secondaryName.compare("neutron")==0||
                 secondaryName.compare("Sb124")==0)
                */
                 if (secondaryName.compare("gamma")==0)
                 {
                   G4cout<<"secondaryName: "<<secondaryName
                   //<<"; secondaryID: "<<secondaryID
                   //<<"; Parent ID: "<<secstep->GetParentID()
                   //<<"; trackID: "<<track->GetTrackID()
                   //<<"; TrackParentID: "<<track->GetParentID()
                   <<"; secEkin: "<<secEkin
                   <<"; secstep->GetTotalEnergy(): "<<G4BestUnit(secstep->GetTotalEnergy(), "Energy")
                   <<"; secstep->GetPosition(): "<< G4BestUnit(secstep->GetPosition(), "Length")         
                   <<G4endl;


                 analysisManager->FillNtupleDColumn(10, 0,secstep->GetTotalEnergy() / MeV);    
                 analysisManager->FillNtupleDColumn(10, 1,secstep->GetGlobalTime());
                 analysisManager->FillNtupleDColumn(10, 2,secstep->GetPosition().getX() / mm);      
                 analysisManager->FillNtupleDColumn(10, 3,secstep->GetPosition().getY()/ mm);      
                 analysisManager->FillNtupleDColumn(10, 4,secstep->GetPosition().getZ()/ mm);      
                 analysisManager->FillNtupleSColumn(10, 5,secondaryName);      
                 analysisManager->AddNtupleRow(10);
                }

           }

       }

    }
    else
    {
       FlagForRealSignal = 0;
    }
  }
     

     
 //   G4cout<<"Now PostUserTrackingAction finished!\n"<<G4endl;




/*

  if(process->GetProcessName() == "muMinusCaptureAtRest") 
  {
          const G4TrackVector* secondary = step->GetSecondary();
          G4int FlagForRealSignal = 0;
    if (secondary->size()!= 0) 
    {  
          // all secondary particles
          for (size_t i = 0; i < secondary->size(); ++i)
          {
  
            G4Track* secondaryTrack = (*secondary)[i];

            G4cout<<"test output 0 "<<G4endl;
            G4cout<<"parents ID: "<<secondaryTrack->GetParentID()<<G4endl;
            const G4ParticleDefinition* particleDefinition = secondaryTrack->GetDefinition();
            //G4cout<<"test output 1 "<<G4endl;
            const G4String&  particleName = particleDefinition->GetParticleName();
            G4cout<<"test output 2 "<<G4endl;
            if(particleName.contains("Sb124"))
                {
                  FlagForRealSignal =1;
            G4cout<<"test output 2.5 "<<G4endl;

                  break;
                }
          }
   
          for (size_t i = 0; i < secondary->size(); ++i)
          {
            G4cout<<"test output 2.9 "<<G4endl;
            G4Track* secondaryTrack = (*secondary)[i];
            G4cout<<"test output 3.0 "<<G4endl;
            const G4ParticleDefinition* particleDefinition = secondaryTrack->GetDefinition();
          //  const G4String&  particleName = particleDefinition->GetParticleName();
            G4cout<<"test output 3 "<<G4endl;
            //inline const G4Step*  secondaryStep = secondaryTrack->GetStep();
            const G4Step*  secondaryStep = secondaryTrack->GetStep();
            if(!secondaryStep) {std::cout << "secondaryStep does not exist, return!" << std::endl; continue; }
            G4cout<<"test output 3.1 "<<G4endl;
            G4StepPoint* secondaryPreStepPoint =  secondaryStep->GetPreStepPoint();
            if(!secondaryPreStepPoint ) {std::cout << "secondaryPreStepPoint  does not exist, return!" << std::endl; continue; }
            G4cout<<"test output 3.2 "<<G4endl;
            //const G4StepPoint* secondaryPretStepPoint = secondaryTrack->GetStep()->GetPreStepPoint();
            G4cout<<"test output 4 "<<G4endl;
            const G4StepPoint* secondaryPostStepPoint = secondaryStep->GetPostStepPoint();
            if(!secondaryPostStepPoint ) {std::cout << "secondaryPreStepPoint  does not exist, return!" << std::endl; continue; }
            G4cout<<"test output 5 "<<G4endl;
            //G4String preStepPointLogicalVolumeName = secondaryPreStepPoint->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetName();
            G4cout<<"test output 6 "<<G4endl;
            G4String postStepPointLogicalVolumeName = secondaryPostStepPoint->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetName();
            G4cout<<"test output 7 "<<G4endl;
            const G4VProcess* ProcessfromSecondaryTrack = secondaryPostStepPoint->GetProcessDefinedStep();    
            G4cout<<"test output 8 "<<G4endl;
            const G4String& ProcessNamefromSecondaryTrack = ProcessfromSecondaryTrack->GetProcessName();
            G4cout<<"test output 9 "<<G4endl;

          }
   }    
 }  


*/





//  G4cout<<"\nTest Output in Post MyTrackingAction!\n"<<G4endl;
    //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    //
    //G4int trackID = track->GetTrackID();
    //
    //Run* run
    //  = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    //        
    //          
    //if (trackID == 1) {
    //  G4double pr = (track->GetPosition())*
    //                (fPrimary->GetParticleGun()->GetParticleMomentumDirection());
    //  run->AddProjRange(pr);
    //  analysisManager->FillH1(9, pr);
    //}
            
//G4cout<<"FlagForRealSignal in the end of TrackingAction: "<<FlagForRealSignal<<G4endl;
   myfile <<GetFlagForRealSignal()<<G4endl;
   myfile.close(); 

}

G4int MyTrackingAction::GetFlagForRealSignal() const 
{

   return FlagForRealSignal;    

}