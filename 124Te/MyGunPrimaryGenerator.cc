#include "MyGunPrimaryGenerator.hh"

MyGunPrimaryGenerator::MyGunPrimaryGenerator()
{


   fMesesengerinGenerator = new G4GenericMessenger(this,"/GunPrimaryGenerator/","Momentum of Muons");

   fMesesengerinGenerator->DeclareProperty("MomentumofMuon",MomentumofMuon,"Momentum of Muon");
   MomentumofMuon = 50;



   fParticleGun = new G4ParticleGun(1);

   G4ParticleTable * particleTable = G4ParticleTable::GetParticleTable();
   G4ParticleDefinition * particle = particleTable->FindParticle("mu-");
 
   G4ThreeVector pos(0.,1000.*mm,0);
   G4ThreeVector mom(0.,-1.,0.); 
 
   fParticleGun->SetParticlePosition(pos);
   fParticleGun->SetParticleMomentumDirection(mom);
   //fParticleGun->SetParticleMomentum(50.*MeV);
   fParticleGun->SetParticleMomentum(MomentumofMuon*MeV);
   fParticleGun->SetParticleDefinition(particle);

}

MyGunPrimaryGenerator::~MyGunPrimaryGenerator()
{
    delete fParticleGun;
}

void MyGunPrimaryGenerator::GeneratePrimaries(G4Event * anEvent)
{


   
   fParticleGun->GeneratePrimaryVertex(anEvent);  

}