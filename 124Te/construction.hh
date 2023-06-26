#ifndef CONSTRUCTION_HH
#define CONDTRUCTION_HH
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "GeometryGeDet.hh"
#include "G4SubtractionSolid.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{

	public:
	MyDetectorConstruction();
        ~MyDetectorConstruction();

        virtual G4VPhysicalVolume* Construct();    
  	
        private:


        virtual void ConstructSDandField();
        void DefineMaterials();



        G4double Thickness;        
        G4double SideThickness;        
        G4double FrontThickness;        


        G4Box * solidWorld;
        //G4Tubs * Te_target;
        G4Box * Te_target;
        G4SubtractionSolid* cup_TargetSolid;
        G4Box * Pb_SlowDownLayer;
        G4Box * solidScintillatorDetector;

        G4LogicalVolume * logicalWorld;
        G4LogicalVolume * logical_Te_target;
        G4LogicalVolume * logical_Te_cup_target;
        G4LogicalVolume * logical_Pb_SlowDownLayer;
        G4LogicalVolume * logicalScintillatorDetector;
        G4LogicalVolume * logicalAndyDetector;
        
        G4VPhysicalVolume * physWorld;
        G4VPhysicalVolume * physTarget;
        G4VPhysicalVolume * phys_cup_Target;
        G4VPhysicalVolume * physPb_SlowDownLayer;
        G4VPhysicalVolume *physScintillatorDetector1;
        G4VPhysicalVolume *physScintillatorDetector2;
        G4VPhysicalVolume *physScintillatorDetector3;

        G4GenericMessenger *fMesesenger;

        G4Material * worldMat;
        G4Material* Te_material; 
        G4Material * pureTe_material;
        G4Material* Pb_material; 
        G4Material *ScintillatordetectorMat;

        G4bool isAndyGeDet;
        void DefineMaterialsFromAndi();
        void ConstructAndyGeDet();
        GeometryGeDet* andiDet;

};

#endif
