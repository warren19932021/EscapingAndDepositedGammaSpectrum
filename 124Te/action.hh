#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

//#include "MyGunPrimaryGenerator.hh" //particle Gun
#include "PrimaryGeneratorAction.hh" // GPS

#include "run.hh"
#include "event.hh"
#include "TrackingAction.hh"
#include "stepping.hh"


class MyActionInitialization : public G4VUserActionInitialization
{
public:
    MyActionInitialization();
    ~MyActionInitialization();

    virtual void Build() const;

};

#endif
