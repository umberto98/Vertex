#include <Riostream.h>
#include "Point.h"
#include <TMath.h>
ClassImp(Point) 

Point::Point():
  fX(0.),
  fY(0.),
  fZ(0.),
  fR(0.),
  fPhi(0.)
{
  //default constructor
  //cout << "DEFAULT CONSTRUCTOR POINT\n";
}

Point::Point(bool cart, double x_r, double y_phi,double z):
  fZ(z)
{
  if (cart){
  	fX=x_r;
  	fY=y_phi;
  	fR=pow(fX*fX+fY*fY,0.5);
  /*	if ((fX==0. && fY==0.) || (fY==0. && fX>0.)) fPhi=0;
  	else if (fX==0 && fY>0) fPhi=acos(-1)/2;
  	else if (fX==0 && fY<o) fPhi=-acos(-1)/2;
  */
  	if ((fX>0 && fY<0) || (fX<0 && fY>0))   fPhi=atan(fY/fX)+2*acos(-1);
  	else if (fX<0 && fY<0)   fPhi=atan(fY/fX)+acos(-1);
    else fPhi=atan(fY/fX);	
  }
  else {
  	fR=x_r;
  	fPhi=y_phi;
  	fX=fR*cos(fPhi);
  	fY=fR*sin(fPhi);
  }
  
}

Point::~Point(){
  //cout<<"DESTRUCTOR POINT\n";
}

void Point::PrintStatus() const{
  printf("Point coordinates: X= %f, Y= %f, Z= %f\n", fX, fY, fZ);
}




