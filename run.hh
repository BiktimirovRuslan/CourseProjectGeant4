#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"

#include "G4RootAnalysisManager.hh"

class G4Run;

class MyRunAction : public G4UserRunAction
{
public:
	MyRunAction();
	virtual ~MyRunAction();
	
	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction(const G4Run*);
};

#endif
