#include <Riostream.h> 
#include <TMath.h>
#include <TRandom3.h>
#include "Generator.h"

ClassImp(Generator)

Generator* Generator::fgInstance = NULL;

//________________________________________________________________
Generator::Generator(const double xyrms, const double zrms,
		     const int mult, const double etarange):
  TObject(),
  fGenP(),
  fXYrms(xyrms),
  fZrms(zrms),
  fPsdrapRng(etarange),
  fMult(mult),
  fMultDist(NULL),
  fEtaDist(NULL){
  // standard constructor
  }
  
//________________________________________________________________
Generator::Generator(const double xyrms, const double zrms,
		     const int mult, const TH1F* etadist):
  TObject(),
  fGenP(),
  fXYrms(xyrms),
  fZrms(zrms),
  fPsdrapRng(0.),
  fMult(mult),
  fMultDist(NULL){
  // standard constructor
  fEtaDist=etadist;
}

//__________________________________________________________________
Generator::Generator(const double xyrms, const double zrms,
		     const TH1F* multdist, const TH1F* etadist):
  TObject(),
  fGenP(),
  fXYrms(xyrms),
  fZrms(zrms),
  fPsdrapRng(0.),
  fMult(0){
  //standard constructor per distribzioni
  fEtaDist=etadist;
  fMultDist=multdist;
}

//__________________________________________________________________
Generator::~Generator(){
  //default destructor
}

//_________________________________________________________________
Generator* Generator::InstanceG(const double xyrms, const double zrms,
			        const int mult, const TH1F* etadist){
  if(!fgInstance){
    fgInstance = new Generator(xyrms, zrms, mult, etadist);
  }
  return fgInstance;
}

//_________________________________________________________________
Generator* Generator::InstanceG(const double xyrms, const double zrms,
				const TH1F* multdist,const TH1F* etadist){
  if(!fgInstance){
    fgInstance = new Generator(xyrms, zrms, multdist, etadist);
  }
  return fgInstance;
}

//_________________________________________________________________
void Generator::Destroy(){
  if(fgInstance)delete fgInstance;
  fgInstance = NULL;
}

//____________________________________________________________
int Generator::GetMult() const{
  return fMult;
}

//_____________________________________________________________
Point Generator::GetGenerationPoint() const{
  return fGenP;
}

//_________________________________________________________________
void Generator::SimulateEvent(TClonesArray &genparts){
  double eta,theta,phi;
  fGenP.fX=gRandom->Gaus(0,fXYrms);
  fGenP.fY=gRandom->Gaus(0,fXYrms);
  if(!gZUNIF)
    fGenP.fZ=gRandom->Gaus(0,fZrms);
  else
    fGenP.fZ=(gRandom->Rndm())*2*fZrms-fZrms;
  
  if(fMultDist) fMult=(int) (fMultDist->GetRandom()+0.5);
  if (fMult>0){
    for(int j =0;j<fMult;j++){
      if (fEtaDist) eta=fEtaDist->GetRandom();
      else eta=(gRandom->Rndm()*2-1)*fPsdrapRng;
      theta=PsdrapInv(eta);
      phi=2*acos(-1)*gRandom->Rndm();
      new(genparts[j]) Particle(fGenP,theta,phi);
    }
  }else {
    if (fMultDist) cout<<"Multiplicity not extracted, try RndmMult()"<<endl;
    cout<<"0 produced particles"<<endl;;
    return;
  }  
}

//____________________________________________________________
void Generator::PrintStatus() const{
  cout << "X, Y rms(mm): " << fXYrms
       << "\nZ rms(mm): " << fZrms;
  if(fMultDist)
    cout << "\nMolteplicità dalla distribuzione: " << fMultDist->GetTitle()
	 << "\nPseudorapidità dalla distribuzione: " << fEtaDist->GetTitle() << "\n\n\n";
  else
    cout << "\nMolteplicità fissata a: " << fMult
	 << "\nPseudorapidità dalla distribuzione " << fEtaDist->GetTitle() << "\n\n\n";
}

//_____________________________________________________________
double Generator::PsdrapInv(double eta){
	return 2*atan(TMath::Exp(-eta));
}


