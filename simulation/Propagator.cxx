#include "Propagator.h"
#include <TMath.h>
#include <TRandom3.h>


ClassImp(Propagator)


Propagator* Propagator::fgInstance = NULL;


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

Propagator::~Propagator(){
  // Destructor
}

Propagator* Propagator::Instance(const double rbp, const double r1, const double r2,
				 const double l1, const double l2,
				 const double dbp, const double d1){
  if(!fgInstance){
    fgInstance = new Propagator(rbp, r1, r2, l1, l2, dbp, d1);
  }
  return fgInstance;
}

void Propagator::Destroy(){
  if(fgInstance)delete fgInstance;
  fgInstance = NULL;
}

void Propagator::PrintStatus(){
  cout << "Raggio BeamPipe(cm): " << rBp
       << "\nRaggio primo layer(cm): " << rLay1
       << "\nRaggio secondo layer(cm): " << rLay2
       << "\nSpessore BeamPipe(mm): " << fDepthBp
       << "\nSpessore primo layer(mm): " << fDepth1
       << "\nLunghezza primo layer(cm): " << fLenght1
       << "\nLunghezza secondo layer(cm): " << fLenght2 << endl;
}

Point Propagator::Propagate(Particle &particle, int layer){
  if(layer==0){
    particle.PropagateToRadius(rBp);
    return particle.GetPoint();
  }
  else if(layer==1){
    particle.PropagateToRadius(rLay1);
    if(IsHit(particle.GetPoint().fZ, fLenght1))
      return particle.GetPoint();
    return Point(0,0,0);
  }
  else if(layer==2){
    particle.PropagateToRadius(rLay2);
    if(IsHit(particle.GetPoint().fZ, fLenght2))
      return particle.GetPoint();
    return Point(0,0,0);   
  }
  else
    return Point(0,0,0);
}

bool Propagator::IsHit(const double zpart, const double lenght){
  if(TMath::Abs(zpart)<lenght/2)
    return true;
  return false;
}

void Propagator::MultipleScatter(Particle &particle){
  //controllo rad2
  particle.Rotate(gRandom->Gaus(0,0.001),2*TMath::ACos(-1)*gRandom->Rndm());
}

void Propagator::GaussianSmearing(Point &point, const double rphiRMS, const double zRMS, int layer){
	double drphi=gRandom->Gaus(0,rphiRMS);
	double dz=gRandom->Gaus(0,zRMS);
	double r,dphi;
	if (layer==1) r=rLay1;
	else if (layer==2) r=rLay2;
	else {
	cout<<"invalid layer"<<endl;
	return;
	}
	dphi=drphi/r;
	point.fZ+=dz;
	point.SetPhi(point.GetPhi()+dphi);
}




















