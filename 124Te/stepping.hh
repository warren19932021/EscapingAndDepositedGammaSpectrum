#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

#include "PrimaryGeneratorAction.hh"

//#include "construction.hh"
#include "event.hh"
//class MyDetectorConstruction;

class MySteppingAction : public G4UserSteppingAction
{ 
    public:
    MySteppingAction(MyEventAction* eventAction);
    //MySteppingAction(MyEventAction* eventAction, const G4Step*);
    ~MySteppingAction();

    virtual void UserSteppingAction(const G4Step*);
  
  
   //  virtual double GetParticleEnergy( PrimaryGeneratorAction* Primary);
   // double GetParticleEnergy( PrimaryGeneratorAction* Primary);
   // double GetParticleEnergy();
   
   


    private:
 
    MyEventAction * fEventAction;

 //   PrimaryGeneratorAction* fPrimary;

 //   double SourceParticleEnergy;

    G4LogicalVolume* fCorrectPostStepPointerToTarget;


};


#endif
