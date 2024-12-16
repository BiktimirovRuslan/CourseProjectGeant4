#include "run.hh"
#include "G4AnalysisManager.hh"

MyRunAction::MyRunAction()
{
G4RootAnalysisManager *man = G4RootAnalysisManager::Instance();	
        
        
       
        man->CreateNtuple("Hits","Hits");
	man->CreateNtupleIColumn("Photons");
	man->CreateH1("0","Ph", 1, 0 ,500);
        man->FinishNtuple(0);
        
        man->CreateNtuple("Time","Time");
        man->CreateNtupleDColumn("time");
          man->FinishNtuple(0);

	//man->CreateNtuple("Scoring", "Scoring");
	//man->CreateNtupleDColumn("fEdep");
	//man->FinishNtuple(1);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
	G4RootAnalysisManager *man = G4RootAnalysisManager::Instance();	
        
        man->OpenFile("time.root");
        
    //    man->CreateNtuple("Hits","Hits");
	//man->CreateNtupleDColumn("Photons");
     //   man->FinishNtuple(0);
	
	
	
	//man->OpenFile("output.root");
	
	
	
	
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	G4RootAnalysisManager *man = G4RootAnalysisManager::Instance();
	
	 man->Write();
	 man->CloseFile();
}
