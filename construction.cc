#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
	fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");
	
	fMessenger->DeclareProperty("nCols", nCols, "Number of columns");
	fMessenger->DeclareProperty("nRows", nRows, "Number of rows");
	fMessenger->DeclareProperty("isCherenkov", isCherenkov, "Toggle Cherenkov setup");
	fMessenger->DeclareProperty("isScintillator", isScintillator, "Toggle Scintillator setup");
	
	nCols = 1;
	nRows = 1;
	
	DefineMaterials();
	
	xWorld = 1.1*m;
	yWorld = 1.1*m;
	zWorld = 1.5*m;
	
	isCherenkov = true;
	isScintillator = false;
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterials()
{
	G4NistManager *nist = G4NistManager::Instance();
	
	G4double energy[2] = {1*eV, 8*eV};
	G4double rindexAerogel[2] = {1.1, 1.1};
	G4double rindexWorld[2] = {1.0, 1.0};
	G4double rindexNaI[2] = {1.59, 1.59};
	G4double rindexSi[2] = {1.5, 1.5};
	G4double reflectivity[2] = {1.0, 1.0};
	G4double abslength2[2]= {0.7*m,0.7*m}; 
	G4double abslength3[2]= {1*nm,1*nm};
	
	SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
	SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
	SiO2->AddElement(nist->FindOrBuildElement("O"), 2);
	
	G4MaterialPropertiesTable *mptSiO2 = new G4MaterialPropertiesTable();
	mptSiO2->AddProperty("ABSLENGTH", energy, abslength3, 2);
	mptSiO2->AddProperty("RINDEX", energy, rindexSi, 2);
	SiO2->SetMaterialPropertiesTable(mptSiO2);
	
	H2O = new G4Material("H2O", 1.000*g/cm3, 2);
	H2O->AddElement(nist->FindOrBuildElement("H"), 2);
	H2O->AddElement(nist->FindOrBuildElement("O"), 1);
	
	C = nist->FindOrBuildElement("C");
	
	Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
	Aerogel->AddMaterial(SiO2, 62.5*perCent);
	Aerogel->AddMaterial(H2O, 37.4*perCent);
	Aerogel->AddElement(C, 00.1*perCent);
	
	worldMat = nist->FindOrBuildMaterial("G4_AIR");
	
        water = nist->FindOrBuildMaterial("G4_POLYSTYRENE");
	
	
	G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
	mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);
	
	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
	mptWorld->AddProperty("ABSLENGTH", energy, abslength2, 2);
        
	
	Aerogel->SetMaterialPropertiesTable(mptAerogel);
	
	worldMat->SetMaterialPropertiesTable(mptWorld);
	
	Na = nist->FindOrBuildElement("Na");
	I = nist->FindOrBuildElement("I");
	NaI = new G4Material("NaI", 3.87*g/cm3, 2);
	NaI->AddElement(Na, 1);
	NaI->AddElement(I, 1);
	
	G4double fraction[2]= {1.0,1.0}; 
	G4double fraction1[2]= {0,0}; 
	G4double fraction2[2]= {0,0}; 
	G4double abslength[2]= {0.7*m,0.7*m}; 
	
	G4MaterialPropertiesTable *mptH2O = new G4MaterialPropertiesTable();
		water->SetMaterialPropertiesTable(mptH2O);
	mptH2O->AddProperty("RINDEX", energy, rindexNaI, 2);
	mptH2O->AddProperty("ABSLENGTH", energy, abslength, 2);
	mptH2O->AddProperty("SCINTILLATIONCOMPONENT1", energy, fraction, 2);
	//mptH2O->AddProperty("SCINTILLATIONCOMPONENT2", energy, fraction1, 2);
	//mptH2O->AddProperty("SCINTILLATIONCOMPONENT3", energy, fraction2, 2);
	mptH2O->AddConstProperty("SCINTILLATIONYIELD", 2000.0/MeV);
	//mptH2O->AddConstProperty("SCINTILLATIONYIELD", 0./MeV);
	//mptH2O->AddConstProperty("SCINTILLATIONYIELD", 0./MeV);
	mptH2O->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 250*ns);
	//mptH2O->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 600*ns);
	//mptH2O->AddConstProperty("SCINTILLATIONTIMECONSTANT3", 800*ns);
	mptH2O->AddConstProperty("RESOLUTIONSCALE", 1.);
	mptH2O->AddConstProperty("SCINTILLATIONYIELD1", 1.);
	//mptH2O->AddConstProperty("SCINTILLATIONYIELD2", 0.);
	//mptH2O->AddConstProperty("SCINTILLATIONYIELD3", 0.);
	water->SetMaterialPropertiesTable(mptH2O);
	water->GetIonisation()->SetBirksConstant(0.126*mm/MeV);
	
	mirror = new G4OpticalSurface("mirror");
	mirror->SetType(dielectric_metal);
	mirror->SetFinish(ground);
	mirror->SetModel(unified);
	G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();
	mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity, 2);
	mirror->SetMaterialPropertiesTable(mptMirror);
}

void MyDetectorConstruction::ConstructCherenkov()
{	
G4double index=0;
G4double index2=5;
solidDetector = new G4Tubs("solidDetector", 0.*m, (0.025+0.005*index)*m, 0.01*m, 0*deg, 360*deg);
	
	logicDetector = new G4LogicalVolume(solidDetector, SiO2,"logicDetector");

G4RotationMatrix *rm = new G4RotationMatrix;// Задаем матрицу поворота для 2-х ФЭУ
rm->rotateY(90*deg);

	
	//for(G4int i = 0; i<nRows; i++)
	//{780
	//	for(G4int j = 0; j<nCols; j++)
	//	{
			physDetector1 = new G4PVPlacement(0,G4ThreeVector(0.025*m,-0.*m, ( 0.511)*m),logicDetector, "physDetector1", logicWorld, false, 0, true);// ФЭУ, расположенные по оси Z
            physDetector2 = new G4PVPlacement(0,G4ThreeVector(-0.025*m,-0.*m, (0.511)*m),logicDetector, "physDetector2", logicWorld, false, 0, true);//
            physDetector3 = new G4PVPlacement(0,G4ThreeVector(0.025*m,-0.*m, ( -0.511)*m),logicDetector, "physDetector1", logicWorld, false, 0, true);// ФЭУ, расположенные по оси Z
            physDetector4 = new G4PVPlacement(0,G4ThreeVector(-0.025*m,-0.*m, (-0.511)*m),logicDetector, "physDetector2", logicWorld, false, 0, true);//
            

            //physDetector3 = new G4PVPlacement(rm, G4ThreeVector(( 0.511)*m, 0.*m, 0.*m),logicDetector, "physDetector3", logicWorld, false, 0, true);// ФЭУ, расположенные по оси X, повернутые по оси Y на 90 град.
            //physDetector4 = new G4PVPlacement(rm, G4ThreeVector((-0.511)*m, 0.*m, 0.*m),logicDetector, "physDetector4", logicWorld, false, 0, true);//
	//	}
	//}
	
	solidScintillator = new G4Box("solidScintillator", (0.5+0.005*index)*m, (0.025+0.005*index)*m, (0.25+0.05*index2)*m);
	logicScintillator = new G4LogicalVolume(solidScintillator, water, "logicScintillator");
	for(G4double ii=0; ii<1; ii++)   //(от -1 до 2) 3*3 сцинтиллятора
	{
		for(G4double jj=0; jj<1; jj++) //(от -1 до 2) 3*3 сцинтиллятора
		{	
	physScintillator = new G4PVPlacement(0, G4ThreeVector(0.053*ii*m,0.053*jj*m,0.), logicScintillator, "physScintillator", logicWorld, false, 0, true);/*+0.005*/
		}
	}
	//physScintillator = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicScintillator, "physScintillator", logicWorld, false, 0, true);
}

void MyDetectorConstruction::ConstructScintillator()
{
	solidScintillator = new G4Box("solidScintillator", (0.025)*m, (0.025)*m, 0.035*m);
	logicScintillator = new G4LogicalVolume(solidScintillator, water, "logicScintillator");
	//G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin", logicWorld, mirror);
	//fScoringVolume =logicScintillator;
	physScintillator = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicScintillator, "physScintillator", logicWorld, false, 0, true);
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{			
	solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
	
	logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	
	physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);
	
	if(isCherenkov)
		ConstructCherenkov();
		
	if(isScintillator)
		ConstructScintillator();
		
	return physWorld;
}	

//void MyDetectorConstruction::ConstructSDandField()
//{
//	MyEventAction *evtAction = new MyEventAction();
//	
//	if(isCherenkov)
//		logicDetector->SetSensitiveDetector(sensDet);
//}
