#include <Riostream.h> // cercato nelle directory standard
#include "Particle.h" // cercato non nelle directory standard
#include <TMath.h>


ClassImp(Particle) // da mettere solo se eredita da qualcosa di root
///
//commentp
///


Particle::Particle():
TObject(),
  fPoint(false,0.,0.,0.),
  fTheta(0.),
  fPhi(0.)
 
{
  //default constructor
  //cout << "DEFAULT CONSTRUCTOR PARTICLE\n";
}

Particle::Particle(double x, double y, double z, double theta, double phi):
  TObject(),
  fPoint(false,x,y,z),
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

void Particle::PropagateToRadius(double r){
	double t,a,b,x,y,z;
	
	x=fPoint.fX;
	y=fPoint.fY;
	z=fPoint.fZ;
	a = x*sin(fTheta)*cos(fPhi)+y*sin(fTheta)*sin(fPhi);
	b = (sin(fTheta)*cos(fPhi))*(sin(fTheta)*cos(fPhi))+(sin(fTheta)*sin(fPhi))*(sin(fTheta)*sin(fPhi));
	t = (-a+pow((a*a-b*(x*x+y*y-r*r)),0.5))/b;
	
	x+=sin(fTheta)*cos(fPhi)*t;
	y+=sin(fTheta)*sin(fPhi)*t;
	z+=cos(fPhi)*y;
	
	fPoint.fX=x;
	fPoint.fY=y;
	fPoint.fZ=z;
}

