#include <Riostream.h> 
#include <TMath.h>
#include <TRandom3.h>
#include "Particle.h"
#include "Generator.h"


ClassImp(Generator)


Generator::Generator():
   TObject(),
   fmult(0),
   fxyRMS(0.),
   fzRMS(0.),
   fpsdraprng(0.),
   fprodP(0.,0.,0.),
   fprodPart(fprodP,0.,0.,0.)
 {
 //default constructor
 }
 
 
Generator::Generator(int mult, double xyRMS, double zRMS, double psdraprng):
   TObject(),
   fmult(mult),
   fxyRMS(xyRMS),
   fzRMS(zRMS),
   fpsdraprng(psdraprng)
 {
 double x,y,z, theta,eta, phi;
 
 x=gRandom->Gaus(0,fxyRMS);
 y=gRandom->Gaus(0,fxyRMS);
 z=gRandom->Gaus(0,fzRMS);
 
 eta=(gRandom->Rndm()*2-1)*fpsdraprng;
 theta=PsdrapInv(eta);
 
 phi=2*acos(-1)*gRandom->Rndm();
 
 fprodP=Point( x, y, z);
 fprodPart=Particle( fprodP, theta, phi, 0.);
 
 cout<<"standard constructor"<<endl;
 }
 
 
 Generator::~Generator(){
 //default destructor
 cout<<"default destructor"<<endl;
 }
 
 double Generator::PsdrapInv(double eta)
 {
   return 2*atan(TMath::Exp(-eta));
 }
 
