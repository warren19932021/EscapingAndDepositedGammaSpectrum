#include "event.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"


#include "G4EventManager.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"

/*
MyEventAction::MyEventAction(MyrunAction* fRunAction)
{

}
*/


MyEventAction::MyEventAction(MyrunAction* run)
{
    fRunAction = run;
    
  //  ContainsSb124 = 0;

}


MyEventAction::~MyEventAction()
{
}

void MyEventAction::BeginOfEventAction(const G4Event* evt)
{
   // G4cout<<"\nNow BeginOfEventAction start to run "<<G4endl;
  //  G4cout<<"\nContainsSB124 in BeginOfEventAction: "<<ContainsSb124<<G4endl;
    isFirstMuonTrackContainingSb124 = false;
  
G4TrajectoryContainer* TrajectoryContainer = evt->GetTrajectoryContainer();

if(TrajectoryContainer)
{
    G4VTrajectory* firstTrajectory = (*TrajectoryContainer)[0];
    //const G4Step* lastStep = firstTrajectory->Get

}
   //(*(evt->GetTrajectoryContainer()))[0]->;

  //G4TrackingManager* trackingManager = G4EventManager::GetEventManager()->GetTrackingManager();
  // Get the primary track

    //if(isFirstMuonTrackContainingSb124)
    //{G4cout<<}

   // G4cout<<"\nNow BeginOfEventAction finished! "<<G4endl;
    

}

void MyEventAction::EndOfEventAction(const G4Event* evt)
{

   // G4cout<<"\nNow EndOfEventAction start to run "<<G4endl;
  //  G4cout<<"\nContainsSB124 in EndOfEventAction: "<<ContainsSb124<<G4endl;


G4int nVertex = evt->GetNumberOfPrimaryVertex();
//G4cout<<"nVertex: "<<nVertex<<G4endl;
    // Loop over all primary vertices
    for (G4int iVertex = 0; iVertex < nVertex; ++iVertex) {
        G4PrimaryVertex* vertex = evt->GetPrimaryVertex(iVertex);
        G4PrimaryParticle* primaryParticle = vertex->GetPrimary();

        // Check if the primary particle is a muon
        if (primaryParticle->GetPDGcode() == 13) {
            G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();

            if (trajectoryContainer) {
                // Loop over the trajectories and save secondary particle IDs
                for (G4int i = 0; i < trajectoryContainer->size(); ++i) {
                    G4cout<<"trajectoryContainer->size(): "<<trajectoryContainer->size()<<G4endl;
                    G4VTrajectory* currentTrajectory = dynamic_cast<G4VTrajectory*>((*trajectoryContainer)[i]);

                    // Check if the trajectory is a secondary particle
                    if (currentTrajectory && currentTrajectory->GetParentID() == 1) {
                        G4int particleID = currentTrajectory->GetPDGEncoding();

                        // Check if the particle is not a muon and save its ID
                        if (particleID != 13) {
                            secondaryParticleIDs.push_back(particleID);
                        }
                    }
                }
            }
        }
    }

    // Output the secondary particle IDs
  //  G4cout << "Secondary Particle IDs: ";
  //  for (size_t i = 0; i < GetSecondaryParticleIDs().size(); ++i) {
  //      G4cout << GetSecondaryParticleIDs()[i] << " ";
  //  }
  //  G4cout << G4endl;




/*
    
G4int nVertex = evt->GetNumberOfPrimaryVertex();

    // Loop over all primary vertices
    for (G4int iVertex = 0; iVertex < nVertex; ++iVertex) {
        G4PrimaryVertex* vertex = evt->GetPrimaryVertex(iVertex);
        G4PrimaryParticle* primaryParticle = vertex->GetPrimary();
        //const G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
         G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
        G4int nTrajectories = trajectoryContainer->entries();  
      
       if (primaryParticle->GetPDGcode() == 13  )
         if (trajectoryContainer){
           
          for(G4int i =0; i< trajectoryContainer->size(); ++i){

          G4VTrajectory* trajectory = dynamic_cast<G4VTrajectory*>((*trajectoryContainer)[i])

          //G4VTrajectory* trajectory = dynamic_cast<G4VTrajectory*>(trajectoryContainer->GetTrajectory(i));

          }

           //G4TrajectoryContainer::iterator it;
          //for (auto looptrajectory : *trajectoryContainer)
          //G4VTrajectory* trajectory = dynamic_cast<G4VTrajectory*>((*trajectoryContainer)[i])
                    
           
         }

      
        for (G4int i = 0; i < nTrajectories;i++)
        {
          //(*trajectoryContainer)[i]->GetTrack();
          G4VTrajectory * trajectory = (*trajectoryContainer)[i];
          G4VTrajectory* trajectory = dynamic_cast<G4VTrajectory*>((*trajectoryContainer)[i])
        }

        //const G4TrackVector* secondaries = evt->GetTrajectoryContainer()->GetVector();
        G4EventManager* eventManager = G4EventManager::GetEventManager();
        






  // Check if the primary particle is a muon
        if (primaryParticle->GetPDGcode() == 13) {
            const G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();

            if (trajectoryContainer) {
                // Loop over the trajectories and save the secondary particle IDs
                for (size_t i = 0; i < trajectoryContainer->size(); ++i) {
                    G4VTrajectory* trajectory = (*trajectoryContainer)[i];
                    G4int trackID = trajectory->GetTrackID();
                    G4int parentID = trajectory->GetParentID();

                    // Check if the secondary particle is not a muon and save its ID
                    if (parentID == 1 && trackID != 1) {
                        int particleID = trajectory->GetPDGEncoding();
                        secondaryParticleIDs.push_back(particleID);
                    }
                }
            }
        }
    }

    // Output the secondary particle IDs
    G4cout << "Secondary Particle IDs: ";
    for (size_t i = 0; i < GetSecondaryParticleIDs().size(); ++i) {
        G4cout << GetSecondaryParticleIDs()[i] << " ";
    }
    G4cout << G4endl;






        // Check if the primary particle is a muon
        if (primaryParticle->GetPDGcode() == 13) {
            const G4ParticleDefinition* particleDef = primaryParticle->GetG4code();

            // Check if the muon captures at rest
            if (particleDef->GetProcessManager()->GetProcess()->GetProcessName() == "muMinusCaptureAtRest") {
                // Get the secondary particles from the primary particle
              

                // Loop over the secondary particles and save their IDs
                for (size_t i = 0; i < secondary->size(); ++i) {
                    G4Track* track = (*secondary)[i]->GetTrack();
                    int particleID = track->GetDefinition()->GetPDGEncoding();
                    secondaryParticleIDs.push_back(particleID);
                }
            }
        }
    }

    // Output the secondary particle IDs
    G4cout << "Secondary Particle IDs: ";
    for (size_t i = 0; i < GetSecondaryParticleIDs().size(); ++i) {
        G4cout << GetSecondaryParticleIDs()[i] << " ";
    }
    G4cout << G4endl;









        // Get the secondary particles from the primary particle
       const G4ParticleDefinition* particleDef = primaryParticle->GetG4code();
       particleDef->GetProcessManager()->GetProcess()->GetProcessName();

        // Loop over the secondary particles and save their IDs
        for (size_t i = 0; i < secondary->size(); ++i) {
            G4Track* track = (*secondary)[i]->GetTrack();
            G4int parentID = track->GetParentID();

            // Check if the parent particle ID is 1
            if (parentID == 1) {
                int particleID = track->GetDefinition()->GetPDGEncoding();
                secondaryParticleIDs.push_back(particleID);
            }
        }
    }

    // Output the secondary particle IDs
    G4cout << "Secondary Particle IDs: ";
    for (size_t i = 0; i < GetSecondaryParticleIDs().size(); ++i) {
        G4cout << GetSecondaryParticleIDs()[i] << " ";
    }
    G4cout << G4endl;


*/

    G4String HCName = "HPGeHitsCollection";
    HPGeHitsCollection *HPGe_HC;
    fHPGe_HCID = G4SDManager::GetSDMpointer()->GetCollectionID(HCName);
    // Get hits collection
    HPGe_HC = GetHitsCollection(fHPGe_HCID, evt);
    //get through all hits of this event
    G4int nofHits = HPGe_HC->entries();
   //G4cout<<"in EndOfEventAction, nofHits: "<<nofHits<<G4endl;
    
    if (nofHits == 0) 
        return;
    
  //  G4cout << "* DEBUG: event " << evt->GetEventID() << ", HC " << HPGe_HC->GetName() << ": " << nofHits << " hits" << G4endl;
    G4double totEdep = 0.0 * CLHEP::MeV;
    for (G4int i = 0; i < nofHits; i++) {
        HPGeHit *hit = (*HPGe_HC)[i];
    //    hit->Print();
        totEdep += hit->GetEdep();
  //      G4cout << "total Edep: " << totEdep << G4endl;
    }

  //      G4cout << "total Edep When event round ended: " <<std::setw(6) << G4BestUnit(totEdep,"Energy") << G4endl;

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleDColumn(9, 0,totEdep);   
  analysisManager->AddNtupleRow(9);


  //  G4cout<<"\nNow EndOfEventAction finished! "<<G4endl;


}


HPGeHitsCollection* MyEventAction::GetHitsCollection(G4int hcID, const G4Event* event) const
{

    
  HPGeHitsCollection* hitsCollection
    = static_cast<HPGeHitsCollection*>(
        event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("EventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }

  return hitsCollection;


}


const std::vector<int>& MyEventAction::GetSecondaryParticleIDs() const
{
    return secondaryParticleIDs;
}



void MyEventAction::PlusOneMinusCaptureInEvent()
{
   // G4cout<<"\nTest Output in MyEventAction!\n"<<G4endl;
   // G4cout << "fRunAction pointer: " << fRunAction << G4endl;
    fRunAction->PlusOneMinusCaptureInRun();
}

void MyEventAction::PlusOneMinusCaptureInEventInScintillator()
{
    fRunAction->PlusOneMinusCaptureInRunInScintillator();
}

void MyEventAction::PlusOneMinusCaptureInEventInTarget()
{
    fRunAction->PlusOneMinusCaptureInRunInTarget();
}

void MyEventAction::PlusOneMinusCaptureInEventInWorld()
{
    fRunAction->PlusOneMinusCaptureInRunInWorld();
}

/*
void MyEventAction::SetContainsSb124()
{
    ContainsSb124 =1;
    G4cout<<"MyEventAction::SetContainsSb124 was called!"<<G4endl;
}

*/

void MyEventAction::SetFristMuonContainingSb124(bool value){

   isFirstMuonTrackContainingSb124 = value;

}
