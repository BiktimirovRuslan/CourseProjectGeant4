#include "generator.hh"
#include "G4RandomDirection.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	//G4String particleName="e";
	G4ParticleDefinition *particle = particleTable->FindParticle("e-");
	
	G4ThreeVector pos(0.,0.10*m,0.);
	G4ThreeVector mom(0.,-1.,0.);
	
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	//fParticleGun->SetParticleMomentum(*MeV);
	fParticleGun->SetParticleEnergy(1.0*MeV);//1.333
	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->GeneratePrimaryVertex(anEvent);
}
