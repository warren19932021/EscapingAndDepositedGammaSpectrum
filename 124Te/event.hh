#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "g4root.hh"
#include "run.hh"


#include "HPGeSD.hh"
#include "HPGeHit.hh"

class MyEventAction: public G4UserEventAction
{
    public:
    //MyEventAction(MyrunAction* fRunAction);
    MyEventAction(MyrunAction* run);
    ~MyEventAction();



    virtual void EndOfEventAction(const  G4Event* evt);    
    virtual void BeginOfEventAction(const  G4Event* evt);    

    //virtual void EndOfEventAction(const  G4Event*);    
    //virtual void BeginOfEventAction(const  G4Event*);

    void PlusOneMinusCaptureInEvent();
    void PlusOneMinusCaptureInEventInScintillator();
    void PlusOneMinusCaptureInEventInTarget();
    void PlusOneMinusCaptureInEventInWorld();

    const std::vector<int>& GetSecondaryParticleIDs() const;



   // void SetContainsSb124();

    //void SetContainsSb124 (int value);
    
    void SetFristMuonContainingSb124 (bool value);

    private:
    std::vector<int> secondaryParticleIDs;
    MyrunAction * fRunAction;
    HPGeHitsCollection* GetHitsCollection(G4int hcID, const G4Event* event) const;
    G4int  fHPGe_HCID;

   // int ContainsSb124;

    bool isFirstMuonTrackContainingSb124; 

};
#endif
