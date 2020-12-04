#include <Riostream.h> // cercato nelle directory standard
#include "Particle.h" // cercato non nelle directory standard



ClassImp(Particle) // da mettere solo se eredita da qualcosa di root
///
//commentp
///


Particle::Particle():
TObject(),
  fPoint(0.,0.,0.),
  fTheta(0.),
  fPhi(0.),
  fPointTemp(0.,0.,0.),
  fThetaTemp(0.),
  fPhiTemp(0.),
  fT(0.)
{
  //default constructor
  //cout << "DEFAULT CONSTRUCTOR PARTICLE\n";
}

Particle::Particle(double x, double y, double z, double theta, double phi, double t):
  TObject(),
  fPoint(x,y,z),
  fTheta(theta),
  fPhi(phi),
  fPointTemp(x,y,z),
  fThetaTemp(theta),
  fPhiTemp(phi),
  fT(t)
{
  //Standard constructor
  //cout << "STANDARD CONSTRUCTOR 1 PARTICLE\n";
}

Particle::Particle(Point p, double theta, double phi, double t):
  TObject(),
  fPoint(p),
  fTheta(theta),
  fPhi(phi),
  fPointTemp(p),
  fThetaTemp(theta),
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

double Particle::GetTheta() const{
  return fTheta;
}

double Particle::GetPhi() const{
  return fPhi;
}

Point Particle::GetPointTemp() const{
  return fPointTemp;
}

double Particle::GetThetaTemp() const{
  return fThetaTemp;
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

void Particle::SetPointTemp(double x, double y, double z, double theta ,double phi){
  fPointTemp.fX=x;
  fPointTemp.fY=y;
  fPointTemp.fZ=z;
  fThetaTemp=theta;
  fPhiTemp=phi;
}

void Particle::SetPointTemp(Point point, double theta, double phi){
  fPointTemp=point;
  fThetaTemp=theta;
  fPhiTemp=phi;
}
