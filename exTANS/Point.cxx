#include <Riostream.h>
#include "Point.h"
#include <TMath.h>

ClassImp(Point) 

  /////////////////////////////////////////////////////////////////////
  // Implementazione della classe punto, utilizzata per rappresentare//
  //un punto nello spazio tridimensionale in coordinate cartesiane   //
  /////////////////////////////////////////////////////////////////////

//____________________________________________________________
Point::Point( double x, double y,double z):TObject(),
  fX(x),
  fY(y),
  fZ(z){
  // standar constructor 
  }

//____________________________________________________________
Point::Point(const Point& point):TObject(),
				 fX(point.fX),
				 fY(point.fY),
				 fZ(point.fZ){
  //copy constructor
}
//____________________________________________________________
Point::~Point(){
  // default destructor
}

//____________________________________________________________
void Point::PrintStatus() const{
  printf("Point coordinates: X= %f, Y= %f, Z= %f\n", fX, fY, fZ);
}

//____________________________________________________________
double Point::GetR() const{
  double r=TMath::Sqrt(fX*fX+fY*fY);
  return r;
}

//____________________________________________________________
double Point::GetPhi() const{
  double phi;
  if (fY<0)
    phi=TMath::ATan2(fY,fX)+2*TMath::ACos(-1);
  else
    phi=TMath::ATan2(fY,fX);

  return phi;
}

//____________________________________________________________
void Point::SetR(double r)  {
  double phi;
  if (fY<0)
    phi=TMath::ATan2(fY,fX)+2*TMath::ACos(-1);
  else
    phi=TMath::ATan2(fY,fX);

  fX=r*cos(phi);
  fY=r*sin(phi);
}

//____________________________________________________________
void Point::SetPhi(double phi)  {
  double r=TMath::Sqrt(fX*fX+fY*fY);
  fX=r*cos(phi);
  fY=r*sin(phi);
}
