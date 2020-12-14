#include "Propagator.h"
#include <TMath.h>
#include <TRandom3.h>

ClassImp(Propagator)

Propagator* Propagator::fgInstance = NULL;

//____________________________________________________________-
Propagator::Propagator(const double rbp, const double r1, const double r2,
		       const double l1, const double l2,
		       const double dbp, const double d1):TObject(),
							  rBp(rbp),
							  rLay1(r1),
							  rLay2(r2),
							  fLenght1(l1),
							  fLenght2(l2),
							  fDepthBp(dbp),
							  fDepth1(d1){
  //Default constructor
							  }

//_________________________________________________________________
Propagator::~Propagator(){
  // default Destructor
}

//__________________________________________________________________
Propagator* Propagator::Instance(const double rbp, const double r1, const double r2,
				 const double l1, const double l2,
				 const double dbp, const double d1){
  if(!fgInstance){
    fgInstance = new Propagator(rbp, r1, r2, l1, l2, dbp, d1);
  }
  return fgInstance;
}

//_____________________________________________________________________
void Propagator::Destroy(){
  if(fgInstance)delete fgInstance;
  fgInstance = NULL;
}

//______________________________________________________________________
void Propagator::PrintStatus() const{
  cout << "Raggio BeamPipe(mm): " << rBp
       << "\nRaggio primo layer(mm): " << rLay1
       << "\nRaggio secondo layer(mm): " << rLay2
       << "\nSpessore BeamPipe(mm): " << fDepthBp
       << "\nSpessore primo layer(mm): " << fDepth1
       << "\nLunghezza primo layer(mm): " << fLenght1
       << "\nLunghezza secondo layer(mm): " << fLenght2 << "\n\n\n";
}

//_______________________________________________________________________
bool Propagator::Propagate(Particle &particle, Point &point, int layer){
  if(layer==0){
    particle.PropagateToRadius(rBp);
    point=particle.GetPoint();
    return true;
  }
  else if(layer==1){
    particle.PropagateToRadius(rLay1);
    if(IsHit(particle.GetPoint().fZ, fLenght1)){
      point=particle.GetPoint();
      return true;
    }
    return false;
  }
  else if(layer==2){
    particle.PropagateToRadius(rLay2);
    if(IsHit(particle.GetPoint().fZ, fLenght2)){
      point=particle.GetPoint();
      return true;
    }
    return false;   
  }
  else
    return false;
}

//______________________________________________________________
bool Propagator::IsHit(const double zpart, const double lenght){
  if(TMath::Abs(zpart)<lenght/2)
    return true;
  return false;
}

//_____________________________________________________________
void Propagator::MultipleScatter(Particle &particle){
  particle.Rotate(gRandom->Gaus(0,rmsScatt),2*TMath::ACos(-1)*gRandom->Rndm());
}
