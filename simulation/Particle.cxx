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
  fPhi(0.)
 
{
  //default constructor
  //cout << "DEFAULT CONSTRUCTOR PARTICLE\n";
}

Particle::Particle(double x, double y, double z, double theta, double phi):
  TObject(),
  fPoint(x,y,z),
  fTheta(theta),
  fPhi(phi)
  
{
  //Standard constructor
  //cout << "STANDARD CONSTRUCTOR 1 PARTICLE\n";
}

Particle::Particle(Point p, double theta, double phi):
  TObject(),
  fPoint(p),
  fTheta(theta),
  fPhi(phi)
  
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

