#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh" 
#include "G4GenericMessenger.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
//#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();
	
	G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }
	
	virtual G4VPhysicalVolume *Construct();
	
private:
	G4LogicalVolume *logicDetector;	
	//virtual void ConstructSDandField();
	
	G4int nCols, nRows;
	
	G4Tubs *solidDetector;
	G4Box *solidWorld, *solidRadiator, *solidScintillator;
	G4LogicalVolume *logicWorld, *logicRadiator, *logicScintillator;
	G4VPhysicalVolume *physWorld, *physRadiator, *physDetector1, *physDetector2, *physDetector3, *physDetector4, *physScintillator;
    G4RotationMatrix *rm;

	G4GenericMessenger *fMessenger;
	
	G4LogicalVolume *fScoringVolume;
	
	G4Material *SiO2, *H2O, *Aerogel, *worldMat, *NaI, *xilol, *water;
	G4Element *C, *Na, *I, *H;
	
	void DefineMaterials();
	void ConstructCherenkov();
	void ConstructScintillator();
	
	G4double xWorld, yWorld, zWorld;
	G4bool isCherenkov, isScintillator;
	
	G4OpticalSurface *mirror;
};

#endif
