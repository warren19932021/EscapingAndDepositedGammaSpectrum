#include "stepping.hh"
#include "construction.hh"
#include "G4RunManager.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4Gamma.hh"
#include "G4PhysicalConstants.hh"

class PrimaryGeneratorAction * Primaryhaha;

//MySteppingAction::MySteppingAction(MyEventAction * eventAction, const G4Step *step)
MySteppingAction::MySteppingAction(MyEventAction * eventAction) 
//  MySteppingAction::MySteppingAction(MyEventAction * eventAction) :
//  G4UserSteppingAction()
//  , fCorrectPostStepPointerToSphere(NULL)
//:i(0)
{
   fEventAction = eventAction;



   //SourceParticleEnergy = 0;

 //GetParticleEnergy();

  // G4cout<<"haha I get it!: " <<Primaryhaha->GetSourceParticleEnergy()<<G4endl;

 //  G4cout<<"heihei: "<<fPrimary->GetSourceParticleEnergy()<<G4endl;

 
  //G4Track* currentTrack = step->GetTrack(); 
  //currentTrack->SetTrackStatus(fStopButAlive);
  //currentTrack->SetTrackStatus(fStopAndKill);
  //currentTrack->SetTrackStatus(fKillTrackAndSecondaries);
  //currentTrack->SetTrackStatus(fAlive);
  //G4cout <<"Step:--------------------------   in MySteppingAction constructor function  "  <<G4endl;

}

MySteppingAction::~MySteppingAction()
{}



//double GetParticleEnergy( PrimaryGeneratorAction* Primary)
//{   
//    fPrimary = Primary;
//    return  Primary->GetSourceParticleEnergy();
//}


//double MySteppingAction::GetParticleEnergy()
//{
//   return  Primaryhaha->GetSourceParticleEnergy();
//   G4cout<<"Primaryhaha->GetSourceParticleEnergy() : "<<Primaryhaha->GetSourceParticleEnergy()<<G4endl;
//}



void MySteppingAction::UserSteppingAction(const G4Step *step)
//void UserSteppingAction(const G4Step* step,const PrimaryGeneratorAction* fPrimary)
{

 // SourceParticleEnergy = GetParticleEnergy( PrimaryGeneratorAction* Primary);

//  G4cout <<"Step:--------------------------    "  <<G4endl;

  G4Track* currentTrack = step->GetTrack(); // technically, check for validtiy, but MUST exist. Else G4 broken!
  G4int trackID = currentTrack->GetTrackID();



 /*
  G4cout<<"trackID: "<<trackID<<G4endl;
  G4cout<<"track status: "<<currentTrack->GetTrackStatus()<<G4endl;
*/


 // if(trackID != 1) return; // if not 1 (==primary), ignore rest


  G4StepPoint* preStepPoint  = step->GetPreStepPoint();  
  G4StepPoint* postStepPoint = step->GetPostStepPoint();

/*
   G4cout<<"\nPreStep global time: "<<G4BestUnit(preStepPoint->GetGlobalTime() ,"Time")
         <<"; local time: "<<G4BestUnit(preStepPoint->GetLocalTime() ,"Time")
         <<"; proper time: "<<G4BestUnit(preStepPoint->GetProperTime() ,"Time")
         <<"\n"<<G4endl;
  

   G4cout<<"\nPostStep global time: "<<G4BestUnit(postStepPoint->GetGlobalTime() ,"Time")
         <<"; local time: "<<G4BestUnit(postStepPoint->GetLocalTime() ,"Time")
         <<"; proper time: "<<G4BestUnit(postStepPoint->GetProperTime() ,"Time")
         <<"\n"<<G4endl;
  
*/

  if(!preStepPoint)  {std::cout << "preStepPoint does not exist, return!" << std::endl; return; }
  if(!postStepPoint) {std::cout << "postStepPoint does not exist, return!" << std::endl; return; }
  
  G4ThreeVector preStep = preStepPoint->GetPosition();
  G4ThreeVector postStep = postStepPoint->GetPosition();


/*

  G4cout <<"preStepPoint:  "<<std::setw(6) << G4BestUnit(preStep,"Length")
         << G4endl;
  G4cout <<"postStepPoint: "<<std::setw(6) << G4BestUnit(postStep,"Length")
         << G4endl;
*/
  // preStep
  const G4TouchableHandle& preStepPointTouchableHandle = preStepPoint->GetTouchableHandle(); // not a pointer, not dangerous
  G4VPhysicalVolume* preStepPointVolume = preStepPointTouchableHandle->GetVolume(); // pointer, check for NULL!
  if(!preStepPointVolume) {std::cout << "preStepPointVolume does not exist, return!" << std::endl; return; }
  G4LogicalVolume* preStepPointLogicalVolume = preStepPointVolume->GetLogicalVolume(); // pointer, check for NULL! // nullptr
  if(!preStepPointLogicalVolume) {std::cout << "preStepPointLogicalVolume does not exist, return!" << std::endl; return; }
  G4String preStepPointVolumeName  = preStepPointLogicalVolume->GetName();


   // --- Get process first before postStep, because we need this for investigation
  const G4VProcess* postStepProcess = postStepPoint->GetProcessDefinedStep();
  if(!postStepProcess) {std::cout << "postStepProcess does not exist, return!" << std::endl; return; }
  std::string postStepProcessName = postStepProcess->GetProcessName();
  
  // postStep
  const G4TouchableHandle& postStepPointTouchableHandle = postStepPoint->GetTouchableHandle(); // not a pointer, not dangerous
  G4VPhysicalVolume* postStepPointVolume = postStepPointTouchableHandle->GetVolume(); // pointer, check for NULL! 
  //if(!postStepPointVolume) {std::cout << "postStepPointVolume does not exist, return!" << std::endl; return; }
 
 
   if(!postStepPointVolume)
  {

 //   std::cout << "postStepPointVolume does not exist, return!" << std::endl;
 //   std::cout << " ---- More Info ----"
 //             << "    \npreStepPointVolumeName: " << preStepPointVolumeName
 //             //<< "    \npreStepProcessName: " << preStepProcessName
 //             << "    \npostStepProcessName: " << postStepProcessName
 //             <<"\n"
 //             << std::endl;
    return;
  }

  G4LogicalVolume* postStepPointLogicalVolume = postStepPointVolume->GetLogicalVolume(); // pointer, check for NULL! // nullptr
  if(!postStepPointLogicalVolume) {std::cout << "postStepPointLogicalVolume does not exist, return!" << std::endl; return; }
  G4String postStepPointVolumeName  = postStepPointLogicalVolume->GetName();
 
//    std::cout << "PreStepVolume: " << preStepPointVolumeName << " ---> Process: " << postStepProcessName << " ---> PostStepVolume: " << postStepPointVolumeName << " (Pointer: " << postStepPointLogicalVolume << ")" << std::endl;
 


/*

    G4cout<<"step in stepping Action--------------------"
          <<"\npreStep: "<<std::setw(6) << G4BestUnit(preStep,"Length")
          <<"\npreStep Z position: "<<std::setw(6) << G4BestUnit(preStep.getZ() ,"Length") 
          <<"\npreStepPointVolumeName: "<<std::setw(6) << preStepPointVolumeName 
          <<"\npostStep: "<<std::setw(6) << G4BestUnit(postStep,"Length")
          <<"\npostStepPointVolumeName: "<<std::setw(6) << postStepPointVolumeName 
          <<"\nGetTotalEnergyDeposit: "<< G4BestUnit(step->GetTotalEnergyDeposit(),"Energy")
          <<"\nTrack Kinetic Energy: "<< G4BestUnit(currentTrack->GetKineticEnergy(),"Energy")
          <<"\nTrack Total Energy: "<< G4BestUnit(currentTrack->GetTotalEnergy() ,"Energy")
          <<"\n"
          << G4endl;


*/




  if(postStepProcessName=="muMinusCaptureAtRest") 
  { 
    fEventAction->PlusOneMinusCaptureInEvent();
    
    //G4cout<<"muon energy: "<<currentTrack->GetTotalEnergy()<<G4endl;

    if(postStepPointVolumeName=="logicalScintillatorDetector")
    {
      fEventAction->PlusOneMinusCaptureInEventInScintillator();
    }

    if(postStepPointVolumeName=="logical_Te_target")
    {
      fEventAction->PlusOneMinusCaptureInEventInTarget();
    }

    if(postStepPointVolumeName=="logicWorld")
    {
      fEventAction->PlusOneMinusCaptureInEventInWorld();
    }

  }




}
