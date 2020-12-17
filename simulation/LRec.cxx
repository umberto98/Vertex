#include "LRec.h"
#include <TMath.h>
#include <TRandom3.h>

ClassImp(LRec)

LRec* LRec::fgInstance = NULL;

//____________________________________________________________-
LRec::LRec(const double rphirms, const double zrms,
				 const double r1, const double r2,
				 const double l1, const double l2):TObject(),
								   fRphi(rphirms),
								   fZ(zrms),
								   rLay1(r1),
								   rLay2(r2),
								   fLenght1(l1),
								   fLenght2(l2){
  //Default constructor
								   }

//_________________________________________________________________
LRec::~LRec(){
  // default Destructor
}

//__________________________________________________________________
LRec* LRec::Instance(const double rphirms, const double zrms,
					 const double r1, const double r2,
					 const double l1, const double l2){
  if(!fgInstance){
    fgInstance = new LRec(rphirms, zrms, r1, r2, l1, l2);
  }
  return fgInstance;
}

//_____________________________________________________________________
void LRec::Destroy(){
  if(fgInstance)delete fgInstance;
  fgInstance = NULL;
}

//_______________________________________________________________
void LRec::GaussianSmearing(Point &point,const int layer){
	double drphi=gRandom->Gaus(0,fRphi);
	double dz=gRandom->Gaus(0,fZ);
	double r,lenght,dphi;
	if (layer==1){
	  r=rLay1;
	  lenght=fLenght1;
	}
	else if (layer==2){
	  r=rLay2;
	  lenght=fLenght2;
	}
	else {
	  cout<<"invalid layer"<<endl;
	  return;
	}
	dphi=drphi/r;
	if(TMath::Abs(point.fZ+dz)<lenght/2)
	  point.fZ+=dz;
	else{
	  point.fZ-=dz/2;
	  //cout << "Punto fuori dal rivelatore dopo aver applicato lo smearing\n";
	}
	point.SetPhi(point.GetPhi()+dphi);
}

//____________________________________________________________________
void LRec::NoisePoint(Point &point,const int layer){
  double r,lenght;
  if (layer==1){
    r=rLay1;
    lenght=fLenght1;
  }
  else if (layer==2){
    r=rLay2;
    lenght=fLenght2;
  }
  else {
    cout<<"invalid layer"<<endl;
    return;
  }
  point.fX=0;
  point.fY=0;
  point.fZ=(gRandom->Rndm())*lenght-lenght/2;
  point.SetR(r);
  point.SetPhi(2*TMath::ACos(-1)*gRandom->Rndm());
}

void LRec::PrintStatus(){
  cout << "Smearing gaussiano con RMS in rphi: " << fRphi << endl
       << "Smearing gaussiano su z con rms di [mm]: " << fZ
       << endl;
}
