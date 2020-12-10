#include <Riostream.h> 
#include <TMath.h>
#include <TRandom3.h>
#include <TTree.h>
#include <TBranch.h>
#include <TFile.h>
#include <TClonesArray.h>
#include <TString.h>
#include <TH1.h>
#include "Generator.h"


ClassImp(Generator)
 
Generator::Generator(int mult, double xyrms, double zrms, double psdraprng):
TObject(),
  fMult(mult),
  fXYrms(xyrms),
  fZrms(zrms),
  fDist(false),
  fPsdrapRng(psdraprng),
  fEtaDist(NULL),
  fMultDist(NULL),
  fGenP(0,0,0)
{
  
}
 
Generator::Generator(double xyrms, double zrms,TH1F* multdist, TH1F* etadist):
   TObject(),
   fXYrms(xyrms),
   fZrms(zrms),
   fPsdrapRng(0.),
   fMult(0),
   fDist(true),
   fGenP(0,0,0)
   {
 			fEtaDist=etadist;
 			fMultDist=multdist;
   }
 
Generator::~Generator(){
//default destructor
	cout<<"default destructor"<<endl;
}


void Generator::SetMult(double mult){
	fMult=mult;
}

void Generator::SetXYrms(double xyrms){
	fXYrms=xyrms;
}

void Generator::SetZrms(double zrms){
	fZrms=zrms;
}

void Generator::SetPsdrapRng(double psdraprng){
	fPsdrapRng=psdraprng;
}

void Generator::SimulateEvent(TClonesArray &genparts){
  double eta,theta,phi;
  fGenP=Point(gRandom->Gaus(0,fXYrms),gRandom->Gaus(0,fXYrms),gRandom->Gaus(0,fZrms));
  if(fMultDist) fMult=RndmMult();
  if (fMult>0){
    for(int j =0;j<fMult;j++){
      if (fEtaDist) eta=fEtaDist->GetRandom();
      else eta=(gRandom->Rndm()*2-1)*fPsdrapRng;
      theta=PsdrapInv(eta);
      phi=2*acos(-1)*gRandom->Rndm();
      new(genparts[j]) Particle(fGenP,theta,phi);
    }
  }
  else {
	 if (fDist) cout<<"Multiplicity not extracted, try RndmMult()"<<endl;
	 cout<<"0 produced particles"<<endl;;
	 return;
  }
  
}
/*
void Generator::SaveParticlesToFile(TString filename){
	TFile file(filename, "RECREATE");
	TTree* tree = new TTree("T","PVMCTrue");
	TClonesArray* ptrparticles = new TClonesArray("Particle", 100);
	TClonesArray& particles= *ptrparticles;
	tree->Branch("Particle",&ptrparticles);
	if (fMult>0){
	 for(int j =0;j<fMult;j++){
		 cout<<"Saving Particle:"<<j<<endl;
		 new(particles[j]) Particle(fProdParticles[j]);
		 tree->Fill();
	 }
	}
	else cout<<"points array is empty"<<endl;
	file.Write();
	delete ptrparticles;
	file.Close();
	}
*/

double Generator::PsdrapInv(double eta){
	return 2*atan(TMath::Exp(-eta));
}//Returns theta given pseudorapidity eta

int Generator::RndmMult(){
	fMult=fMultDist->GetRandom();
	return fMult;
}

Point Generator::GetGenerationPoint(){
  return fGenP;
}
