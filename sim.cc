#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "QGSP_BERT_HP.hh"
#include "FTFP_BERT.hh"
#include "G4OpticalParameters.hh"
#include "construction.hh"
#include "action.hh"
#include "physics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4OpticalPhysics.hh"
#include "G4VModularPhysicsList.hh"

int main(int argc, char** argv)
{
	/*#ifdef G4MULTITHREADED
		G4MTRunManager *runManager = new G4MTRunManager();
	#else
		G4RunManager *runManager = new G4RunManager();
	#endif*/
	 
	 G4RunManager *runManager = new G4RunManager();
	 
	runManager->SetUserInitialization(new MyDetectorConstruction());
	//runManager->SetUserInitialization(new MyPhysicsList());

	
	G4VModularPhysicsList *physicsList = new QGSP_BERT_HP;
	G4OpticalPhysics *opticalphysics = new G4OpticalPhysics;
	
	physicsList->RegisterPhysics(opticalphysics);
	
	
	physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
	
	runManager->SetUserInitialization(physicsList);
	
	runManager->Initialize();
	
	runManager->SetUserInitialization(new MyActionInitialization());
	
	
	
	G4UIExecutive *ui = 0;
	
	if(argc == 1)
	{
		ui = new G4UIExecutive(argc, argv);
	}
	
	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();

	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	if(! ui)
	{
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
		
	}
	else
	{
		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();	
		delete ui;
		
		
	}
	
	return 0;
}
