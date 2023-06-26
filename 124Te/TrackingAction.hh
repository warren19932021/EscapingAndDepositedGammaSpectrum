#ifndef TrackingAction_h
#define TrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"
#include "MyGunPrimaryGenerator.hh"
#include "event.hh"

class MyTrackingAction : public G4UserTrackingAction {

  public:  


 //------ with particle gun generator member variable------- 
 // MyTrackingAction(MyGunPrimaryGenerator* Gen);


 MyTrackingAction();
   ~MyTrackingAction() {};
   
    virtual void PreUserTrackingAction(const G4Track*);   
    virtual void PostUserTrackingAction(const G4Track*);


   std::vector<int>& GetSecondaryParticleIDs();

   void SetContainsSb124inTrackingAction();

   G4int GetFlagForRealSignal() const;
    
  private:

  MyEventAction * fEventAction;

  std::vector<int> secondaryParticleIDs;

  MyGunPrimaryGenerator* fPrimary;
  
  G4int FlagForRealSignal;


};

#endif
