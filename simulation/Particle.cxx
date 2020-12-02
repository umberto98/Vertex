#include <Riostream.h> // cercato nelle directory standard
#include "Particle.h" // cercato non nelle directory standard



ClassImp(Particle) // da mettere solo se eredita da qualcosa di root
///
//commentp
///


Particle::Particle():
TObject(),
  fPoint(0.,0.,0.),
  fTeta(0.),
  fPhi(0.),
  fPointTemp(0.,0.,0.),
  fTetaTemp(0.),
  fPhiTemp(0.),
  fT(0.)
{
  //default constructor
  //cout << "DEFAULT CONSTRUCTOR PARTICLE\n";
}

Particle::Particle(double x, double y, double z, double teta, double phi, double t):
  TObject(),
  fPoint(x,y,z),
  fTeta(teta),
  fPhi(phi),
  fPointTemp(x,y,z),
  fTetaTemp(teta),
  fPhiTemp(phi),
  fT(t)
{
  //Standard constructor
  //cout << "STANDARD CONSTRUCTOR 1 PARTICLE\n";
}

Particle::Particle(Point p, double teta, double phi, double t):
  TObject(),
  fPoint(p),
  fTeta(teta),
  fPhi(phi),
  fPointTemp(p),
  fTetaTemp(teta),
  fPhiTemp(phi),
  fT(t)
{
  //Standard constructor
  //cout << "STANDARD CONSTRUCTOR 2 PARTICLE\n";
}


Particle::~Particle(){
  //cout<<"DESTRUCTOR PARTICLE\n";
}


Point Particle::GetPoint() const{
  return fPoint;
}

double Particle::GetTeta() const{
  return fTeta;
}

double Particle::GetPhi() const{
  return fPhi;
}

Point Particle::GetPointTemp() const{
  return fPointTemp;
}

double Particle::GetTetaTemp() const{
  return fTetaTemp;
}

double Particle::GetPhiTemp() const{
  return fPhiTemp;
}

double Particle::GetTime() const{
  return fT;
}

void Particle::SetTime(double t){
  fT=t;
}

void Particle::SetPointTemp(double x, double y, double z, double teta ,double phi){
  fPointTemp.fX=x;
  fPointTemp.fY=y;
  fPointTemp.fZ=z;
  fTetaTemp=teta;
  fPhiTemp=phi;
}

void Particle::SetPointTemp(Point point, double teta, double phi){
  fPointTemp=point;
  fTetaTemp=teta;
  fPhiTemp=phi;
}
