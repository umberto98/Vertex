#include <Riostream.h>
#include "Point.h"
#include <TMath.h>
ClassImp(Point) 

Point::Point():
  fX(0.),
  fY(0.),
  fZ(0.)
{
  //default constructor
  //cout << "DEFAULT CONSTRUCTOR POINT\n";
}

Point::Point( double x, double y,double z):
	fX(x),
	fY(y),
  fZ(z)
{
// default constructor 
}

Point::~Point(){
  //cout<<"DESTRUCTOR POINT\n";
}

void Point::PrintStatus() const{
  printf("Point coordinates: X= %f, Y= %f, Z= %f\n", fX, fY, fZ);
}


double Point::GetR() const{
  double r=TMath::Sqrt(fX*fX+fY*fY);
  return r;
}

double Point::GetPhi() const{
	double phi;
	if (fY<0) phi=TMath::ATan2(fY,fX)+2*TMath::ACos(-1);
	else phi=TMath::ATan2(fY,fX);
  return phi;
}

void Point::SetR(double r)  {
	double phi;
	if (fY<0) phi=TMath::ATan2(fY,fX)+2*TMath::ACos(-1);
	else phi=TMath::ATan2(fY,fX);
	fX=r*cos(phi);
	fY=r*sin(phi);
}

void Point::SetPhi(double phi)  {
  double r=TMath::Sqrt(fX*fX+fY*fY);
	fX=r*cos(phi);
	fY=r*sin(phi);
}



