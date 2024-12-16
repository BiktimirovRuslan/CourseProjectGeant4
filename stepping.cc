#include "stepping.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4RootAnalysisManager.hh"
#include "construction.hh"
#include "G4Step.hh"
#include <G4VProcess.hh>

int Nphoton1=0;


MySteppingAction::MySteppingAction(MyEventAction *eventAction)
 : G4UserSteppingAction(),
  fEventAction(eventAction)
{
	fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{

        G4Track *track = step->GetTrack();
        //G4double edep = step->GetTotalEnergyDeposit();
       // fEventAction->AddEdep(edep);
        G4RootAnalysisManager *man = G4RootAnalysisManager::Instance();
        
	G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	//const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	
	G4double energy = track->GetTotalEnergy();
	G4double time = step->GetPostStepPoint()->GetLocalTime();
	G4double stime = 0;
	
	if (track->GetTrackStatus() == fStopAndKill) {
	
	  if (track->GetDefinition()->GetParticleName() == "opticalphoton")
	{
	   
	    if (volume->GetName()=="logicDetector") 
	    {	  
	    	  //fEventAction->AddEdep(edep);
	    	  stime+=time;
	    	  man->FillNtupleDColumn(1, 0, stime);
	          Nphoton1++;
	           man->AddNtupleRow(1);
	         // G4cout << edep << G4endl;
	    }
	//G4cout << Nphoton1 << G4endl;
	}
	}
	
	
}
