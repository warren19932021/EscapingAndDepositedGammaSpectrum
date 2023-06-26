#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

#include "G4GenericMessenger.hh" 


class MyGunPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
MyGunPrimaryGenerator();
~MyGunPrimaryGenerator();

virtual void GeneratePrimaries(G4Event *);

private:

G4ParticleGun *fParticleGun;

G4GenericMessenger *fMesesengerinGenerator;
 
G4double MomentumofMuon;        

};

#endif
