#include "construction.hh"
#include "MySensitiveDetector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4SDManager.hh"
#include "HPGeSD.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
    fMesesenger = new G4GenericMessenger(this,"/detector/","Detector Construction");

    fMesesenger->DeclareProperty("Thickness",Thickness,"Thcikness of Target");
    Thickness = 15.;
    //G4cout<<"Thickness: "<<Thickness<<G4endl;

    fMesesenger->DeclareProperty("SideThickness",SideThickness,"Side Thcikness of CupTarget");
    SideThickness = 5.;

    fMesesenger->DeclareProperty("FrontThickness",FrontThickness,"Front Thcikness of CupTarget");
    FrontThickness = 5.;

    DefineMaterials();
    DefineMaterialsFromAndi();
    isAndyGeDet = true; 
    if(isAndyGeDet) 
    {
      andiDet = new GeometryGeDet(GeometryGeDet::Iktp_nType, false);
      //andiDet->SetDefaults();
    }
   
}

MyDetectorConstruction::~MyDetectorConstruction()
{}	

void MyDetectorConstruction::DefineMaterials()
{

    G4NistManager * nist = G4NistManager::Instance();
    worldMat = nist->FindOrBuildMaterial("G4_AIR");

/*    
    G4Isotope* isotopeTe124 = new G4Isotope("Te124",52,124,123.904*g / mole);   
    G4Element* elementTe124 = new G4Element("Tellurium124","Te124",1);
    elementTe124->AddIsotope(isotopeTe124,1);   
    pureTe_material = new G4Material("Te_material",6.24*g/cm3,1);
    pureTe_material->AddElement(elementTe124,1.0);
*/

    Te_material = nist->FindOrBuildMaterial("G4_Te");
    


    ScintillatordetectorMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    //Pb_material = nist->FindOrBuildMaterial("G4_Pb");
    Pb_material = nist->FindOrBuildMaterial("G4_CONCRETE");

}



void MyDetectorConstruction::DefineMaterialsFromAndi(){
  // get NIST-Material-Manager
  G4NistManager* nist = G4NistManager::Instance();


  // defining Materials
  // ------------------------------  
  //here one should define the material he/she wants to use 
  //in the geometry, if not read from the DB
  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4double density, fractionmass, abundance;
  G4String name, symbol;
  G4int ncomponents, natoms;


  // >>>>>>>> Elements
  G4Element* elH = nist->FindOrBuildElement("H");
  G4Element* elO = nist->FindOrBuildElement("O");
  G4Element* elC = nist->FindOrBuildElement("C");
  G4Element* elB = nist->FindOrBuildElement("B");
  G4Element* elN = nist->FindOrBuildElement("N");
  G4Element* elAr = nist->FindOrBuildElement("Ar");
  G4Element* elSi = nist->FindOrBuildElement("Si");
  G4Element* elCr = nist->FindOrBuildElement("Cr");
  G4Element* elMn = nist->FindOrBuildElement("Mn");
  G4Element* elFe = nist->FindOrBuildElement("Fe");
  G4Element* elNi = nist->FindOrBuildElement("Ni");
  G4Element* elLi = nist->FindOrBuildElement("Li");
  G4Element* elPb = nist->FindOrBuildElement("Pb");
  G4Element* elAl = nist->FindOrBuildElement("Al");
  G4Element* elMg = nist->FindOrBuildElement("Mg");
  G4Element* elCu = nist->FindOrBuildElement("Cu");

  G4Isotope* Ge70 = new G4Isotope(name = "Ge70", 32, 70, 69.92*g / mole);
  G4Isotope* Ge72 = new G4Isotope(name = "Ge72", 32, 72, 71.92*g / mole);
  G4Isotope* Ge73 = new G4Isotope(name = "Ge73", 32, 73, 73.0*g / mole);
  G4Isotope* Ge74 = new G4Isotope(name = "Ge74", 32, 74, 74.0*g / mole);
  G4Isotope* Ge76 = new G4Isotope(name = "Ge76", 32, 76, 76.0*g / mole);

  a = 75.71*g / mole;
  G4int nIsotopes = 5;
  G4Element* elGeNat = new G4Element(name = "naturalGermanium", symbol = "GeNat", nIsotopes);
  elGeNat->AddIsotope(Ge70, abundance = 20.9*perCent);
  elGeNat->AddIsotope(Ge72, abundance = 27.5*perCent);
  elGeNat->AddIsotope(Ge73, abundance = 7.7*perCent);
  elGeNat->AddIsotope(Ge74, abundance = 36.3*perCent);
  elGeNat->AddIsotope(Ge76, abundance = 7.6*perCent);

  G4Element* elGeEnr = new G4Element(name = "enrichedGermanium", symbol = "GeEnr", nIsotopes);
  elGeEnr->AddIsotope(Ge70, abundance = 0.0*perCent);
  elGeEnr->AddIsotope(Ge72, abundance = 0.1*perCent);
  elGeEnr->AddIsotope(Ge73, abundance = 0.2*perCent);
  elGeEnr->AddIsotope(Ge74, abundance = 13.1*perCent);
  elGeEnr->AddIsotope(Ge76, abundance = 86.6*perCent);


  // >>>>>>>> Materials
  // StainlessSteel
  G4Material* StainlessSteel = new G4Material("StainlessSteel", density = 8.06*g / cm3, ncomponents = 6);
  StainlessSteel->AddElement(elC, fractionmass = 0.001);
  StainlessSteel->AddElement(elSi, fractionmass = 0.007);
  StainlessSteel->AddElement(elCr, fractionmass = 0.18);
  StainlessSteel->AddElement(elMn, fractionmass = 0.01);
  StainlessSteel->AddElement(elFe, fractionmass = 0.712);
  StainlessSteel->AddElement(elNi, fractionmass = 0.09);

  // Vacuum
  a = 14.000674*g / mole;
  density = 1.E-10*g / cm3;
  G4Material* Vacuum = new G4Material(name = "Vacuum", z = 7., a, density);

  // Natural Germanium
  density = 5.32*g / cm3;
  G4Material* NaturalGe = new G4Material(name = "NaturalGe", density, 1);
  NaturalGe->AddElement(elGeNat, natoms = 1);

  // Enriched Germanium
  density = 5.54*g / cm3;
  G4Material* EnrichedGe = new G4Material(name = "EnrichedGe", density, 1);
  EnrichedGe->AddElement(elGeEnr, natoms = 1);

  // Germanium/Lithium mixture (1%, det-dead layer)
  density = 5.323*g / cm3;
  G4Material* GeLi = new G4Material(name = "GeLi", density, ncomponents = 2);
  GeLi->AddElement(elGeNat, fractionmass = 0.99);
  GeLi->AddElement(elLi, fractionmass = 0.01);

  // Germanium/Bor mixture (1%, det-dead layer)
  density = 5.323*g / cm3;
  G4Material* GeB = new G4Material(name = "GeB", density, ncomponents = 2);
  GeB->AddElement(elGeNat, fractionmass = 0.99);
  GeB->AddElement(elB, fractionmass = 0.01);

  // PolyEthylen Terephthalat  (PET, Mylar)
  G4Material* PET = new G4Material(name = "PET", density = 1370 * kg / m3, ncomponents = 3);
  PET->AddElement(elC, natoms = 10);
  PET->AddElement(elH, natoms = 8);
  PET->AddElement(elO, natoms = 4);

  // Polylactide  ---- TODO: density!!!
  G4Material* PLA = new G4Material(name = "PLA", density = 1400 * kg / m3, ncomponents = 3);
  PLA->AddElement(elC, natoms = 3);
  PLA->AddElement(elH, natoms = 4);
  PLA->AddElement(elO, natoms = 2);

  // Nylon  ---- TODO: Density, better source (wikipedia right now)
  // PA 6 : [NH−(CH2)5−CO]n || AUCH MOEGLICH: G4_NYLON-6/6   (ist das Selbe T_T)
  G4Material* Nylon = new G4Material(name = "Nylon", density = 1150 * kg / m3, ncomponents = 4);
  Nylon->AddElement(elC, natoms = 6);
  Nylon->AddElement(elH, natoms = 11);
  Nylon->AddElement(elO, natoms = 1);
  Nylon->AddElement(elN, natoms = 1);

  // Styropor
  G4Material* Styropor = new G4Material(name = "Styropor", density = 20 * kg / m3, ncomponents = 2);
  Styropor->AddElement(elH, fractionmass = 12.8*perCent);
  Styropor->AddElement(elC, fractionmass = 87.2*perCent);

  // Polycarbonate
  G4Material* Polycarbonate = new G4Material(name = "Polycarbonate", density = 1200 * kg / m3, ncomponents = 3);
  Polycarbonate->AddElement(elH, fractionmass = 5.5491*perCent);
  Polycarbonate->AddElement(elC, fractionmass = 75.5751*perCent);
  Polycarbonate->AddElement(elO, fractionmass = 18.8758*perCent);
  
  // CRFP (Carbon Fiber Reinforced Polymer): M55 Quasiisotropic Layup  ---------------------------- TODO?!
  G4Material* CFRP = new G4Material("CFRP", 1.66*g / cm3, 1);
  CFRP->AddElement(elC, 1);

  // Impure Aluminium (test with 0,5% Pb as impurity)
  density = 2.7*g / cm3;
  G4Material* ImpureAl = new G4Material(name = "ImpureAl", density, ncomponents = 2);
  // FractionMass_A = Abundance_A * AtomicMass_A / ( Abundance_A * AtomicMass_A + Abundance_B * AtomicMass_B)
  // std::cout << "Atomasse Al.: " << elAl->GetAtomicMassAmu() << " | Atommasse Pb: " << elPb->GetAtomicMassAmu() << std::endl;
  ImpureAl->AddElement(elAl, fractionmass = 0.96284);
  ImpureAl->AddElement(elPb, fractionmass = 0.03716);

  // Impure Aluminium2 - See Norm (test with 0,5% Pb as impurity)
  density = 2.7*g / cm3;
  G4Material* ImpureAl2 = new G4Material(name = "ImpureAl2", density, ncomponents = 7);
  // FractionMass_A = Abundance_A * AtomicMass_A / ( Abundance_A * AtomicMass_A + Abundance_B * AtomicMass_B)
  // std::cout << "Atomasse Al.: " << elAl->GetAtomicMassAmu() << " | Atommasse Pb: " << elPb->GetAtomicMassAmu() << std::endl;
  ImpureAl2->AddElement(elAl, fractionmass = 0.99);
  ImpureAl2->AddElement(elSi, fractionmass = 0.0027);
  ImpureAl2->AddElement(elFe, fractionmass = 0.0027);
  ImpureAl2->AddElement(elCu, fractionmass = 0.0006);
  ImpureAl2->AddElement(elCr, fractionmass = 0.0006);
  ImpureAl2->AddElement(elMn, fractionmass = 0.0017);
  ImpureAl2->AddElement(elMg, fractionmass = 0.0017); 

  // Customized Air
  // Option 1: Calculate Density manually with general Gas-Equation; (air_temp and air_pressure are going to be iggnored in constructor)
  // use customized Air-Components etc!
  G4double air_temp = 293.0*kelvin;
  G4double air_pressure = 1.0205 * bar;
  density = (air_pressure / pascal) * 1.0 / ((air_temp / kelvin) * 287.058) * kg / m3;
  G4Material* Custom_Air_01 = new G4Material("Custom_Air_01", density, ncomponents = 4, kStateGas, air_temp, air_pressure);
  Custom_Air_01->AddElement(elN, fractionmass = 0.781);
  Custom_Air_01->AddElement(elO, fractionmass = 0.209);
  Custom_Air_01->AddElement(elAr, fractionmass = 0.0093);
  Custom_Air_01->AddElement(elC, fractionmass = 0.0007);

  // Option 2: G4-Intern calcualtion of density; only give pressure and temperature!!
  // use Standard-G4-Air Components
  G4Material* Custom_Air_02 = nist->ConstructNewGasMaterial("Custom_Air_02", "G4_AIR", air_temp, air_pressure);

  // Nist-Basic Materials
  G4Material* Copper = nist->FindOrBuildMaterial("G4_Cu");
  G4Material* Beryllium = nist->FindOrBuildMaterial("G4_Be");
  G4Material* Air = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* Helium = nist->FindOrBuildMaterial("G4_He");
  G4Material* Aluminium = nist->FindOrBuildMaterial("G4_Al");
  G4Material* Tungsten = nist->FindOrBuildMaterial("G4_W");
  G4Material* Tin = nist->FindOrBuildMaterial("G4_Sn");

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;  
}


void MyDetectorConstruction:: ConstructAndyGeDet()
{

//--------------------------------------  construct Andy detector
   andiDet->CreateGeometry(logicalWorld);
   logicalAndyDetector = andiDet->GetActiveLogical();
   G4cout<<"logicalAndyDetector->GetName(): "<<logicalAndyDetector->GetName()<<G4endl;
} 




G4VPhysicalVolume* MyDetectorConstruction::Construct()
{

//---- World------
   solidWorld =  new G4Box("SolidWorld",4.0*m,4.0*m,4.0*m); 

   logicalWorld = new G4LogicalVolume(solidWorld, worldMat,"logicWorld");

   physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicalWorld,"physWolrd",0,false,0,true); 

//---- Pb_SlowDownLayer------

   Pb_SlowDownLayer = new G4Box("Target",3*m,3*m,10*cm);
   logical_Pb_SlowDownLayer  = new G4LogicalVolume(Pb_SlowDownLayer,Pb_material,"logical_Pb_SlowDownLayer");
   physPb_SlowDownLayer = new G4PVPlacement(0,G4ThreeVector(0.*m,0.*m,(0.3+0.2)*m),   logical_Pb_SlowDownLayer,"physPb_SlowDownLayer ",logicalWorld,false,111,true);   
    

/*

//---- Target------
   G4double fDetAngle = 0.*deg;
   G4RotationMatrix rotMatrix;
   rotMatrix.rotateX(-fDetAngle);
  // G4ThreeVector positionDetVolume(0,0,0);
   G4ThreeVector positionDetVolume(0.*m,0.*m,0.48*m);

   //Te_target = new G4Tubs("Target", 0.*m, 0.2*m, Thickness*mm, 0.*deg,360.*deg);
   Te_target = new G4Box("Target",0.5*m,0.5*m,2*cm);
   //Te_target = new G4Box("Target",0.5*m,0.5*m,0.5*m);

   logical_Te_target  = new G4LogicalVolume(Te_target,Te_material,"logical_Te_target");

   physTarget = new G4PVPlacement( G4Transform3D(rotMatrix, positionDetVolume),logical_Te_target,"physTarget",logicalWorld,false,0,true);


*/

//----Start of Cup shape Target------

// Define the dimensions of the inner cylinder
G4double innerRadius = 5.0 * cm;

// Define the dimensions of the outer cylinder
//G4double outerRadius = 10.0 * cm;
G4double outerRadius = innerRadius + SideThickness * cm;

G4cout<<"outerRadius: "<<outerRadius<<G4endl;
G4cout<<"FrontThickness: "<<FrontThickness<<G4endl;

G4double startAngle = 0.0;
G4double spanningAngle = 360.0 * degree;
G4double innerHeight = 30.0 * cm;
G4double outerHeight = 30.0 * cm;
//G4ThreeVector innerCylinderPosition = G4ThreeVector(0, 0, -5.0 * cm);
G4ThreeVector innerCylinderPosition = G4ThreeVector(0, 0, -FrontThickness * cm);


// Create the outer cylinder solid
G4Tubs* outerCylinderSolid = new G4Tubs("OuterCylinder", 0, outerRadius, outerHeight/2, startAngle, spanningAngle);

// Create the inner cylinder solid
G4Tubs* innerCylinderSolid = new G4Tubs("InnerCylinder", 0, innerRadius, innerHeight/2, startAngle, spanningAngle);

// Create the hollow cylinder by subtracting the inner cylinder from the outer cylinder
cup_TargetSolid = new G4SubtractionSolid("phys_cup_Target", outerCylinderSolid, innerCylinderSolid,0,innerCylinderPosition);

// Create the logical volume for the hollow cylinder
 logical_Te_cup_target = new G4LogicalVolume(cup_TargetSolid, Te_material, "logical_Te_target");
 //logical_Te_cup_target = new G4LogicalVolume(cup_TargetSolid, pureTe_material, "logical_Te_target");

// Define the position of the hollow cylinder
G4ThreeVector phys_cup_TargetPosition = G4ThreeVector(0.*cm,0.*cm, 15.*cm);

// Create the physical volume for the hollow cylinder and place it in the world
phys_cup_Target = new G4PVPlacement(0, phys_cup_TargetPosition, logical_Te_cup_target, "physTarget", logicalWorld, false, 0, true);

//---- End of Cup shape Target------



/*
//---- Scintillator------
   solidScintillatorDetector = new G4Box("solidScintillatorDetector", 1.0*m, 1.0*m, 5.0/2*cm);
   logicalScintillatorDetector = new G4LogicalVolume(solidScintillatorDetector,ScintillatordetectorMat,"logicalScintillatorDetector");

   physScintillatorDetector1 = new G4PVPlacement(0,G4ThreeVector(0.*m,0.*m,(+0.41+0.025+0.1)*m),  logicalScintillatorDetector,"physScintillatorDetector1",logicalWorld,false,9,true);   
   physScintillatorDetector2 = new G4PVPlacement(0,G4ThreeVector(0.*m,0.*m,(+0.41+0.025)*m),  logicalScintillatorDetector,"physScintillatorDetector2",logicalWorld,false,10,true);          
   physScintillatorDetector3 = new G4PVPlacement(0,G4ThreeVector(0.*m,0.*m,(-0.41-0.025)*m),   logicalScintillatorDetector,"physScintillatorDetector3",logicalWorld,false,11,true);   
*/

//---GeDet----

   if(isAndyGeDet)
      ConstructAndyGeDet();


	// ---------------------------------------------- ----------------------------------------------
	// -------------------------------------- Viss-Attributes:
	// ---------------------------------------------- ----------------------------------------------
	G4VisAttributes *InvisibleVolVisAtt = new G4VisAttributes(false);
	G4VisAttributes *WhiteWireframeVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
	WhiteWireframeVisAtt->SetForceWireframe(false);
	G4VisAttributes *BlueVisAtt = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
	G4VisAttributes *RedVisAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
	G4VisAttributes *CyanVisAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 1.0));
	G4VisAttributes *GrayVisAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5));

/*
	fLogicDetVolume->SetVisAttributes(InvisibleVolVisAtt);
	logicCrystal->SetVisAttributes(RedVisAtt);
	if (fISConsidered)
	{
		logicIS_Bot->SetVisAttributes(CyanVisAtt);
		logicIS_Side->SetVisAttributes(CyanVisAtt);
		logicIS_Top->SetVisAttributes(CyanVisAtt);
	}
	if (fOSConsidered)
	{
		logicOS_Side->SetVisAttributes(BlueVisAtt);
		logicOS_Top->SetVisAttributes(BlueVisAtt);
	}

*/
	
   logicalWorld->SetVisAttributes(InvisibleVolVisAtt);
 //  logicalScintillatorDetector->SetVisAttributes(CyanVisAtt);
 //  logical_Pb_SlowDownLayer->SetVisAttributes(BlueVisAtt);
   logical_Te_cup_target->SetVisAttributes(GrayVisAtt);
 //  logical_Te_target->SetVisAttributes(GrayVisAtt);

   return physWorld;

}	



void MyDetectorConstruction::ConstructSDandField()
{

   
    MySensitiveDetector* senDet = new MySensitiveDetector("Test");
    //logicalWorld->SetSensitiveDetector(senDet);
    //logicalAndyDetector->SetSensitiveDetector(senDet);
    //logical_Te_target->SetSensitiveDetector(senDet);
    logical_Te_cup_target->SetSensitiveDetector(senDet);
    
    
    //MySensitiveDetector* senDet2 = new MySensitiveDetector("Test2");
    //logicalAndyDetector->SetSensitiveDetector(senDet2);



  // Hans idea: Sensitive detectors

  G4String HPGeSDname = "HPGeSD";
  HPGeSD* aHPGeSD = new HPGeSD(HPGeSDname, "HPGeHitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(aHPGeSD);
  // Setting SD to a logical volume by
  //SetSensitiveDetector("crystal_logic", aHPGeSD, true);
 SetSensitiveDetector("activeCrystal", aHPGeSD, true);
 // SetSensitiveDetector("logical_Te_target", aHPGeSD, true);
 //SetSensitiveDetector("logical_Te_cup_target", aHPGeSD, true);
 

}
