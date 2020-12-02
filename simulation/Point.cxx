#include <Riostream.h>
#include "Point.h"

ClassImp(Point) 

Point::Point():
  fX(0.),
  fY(0.),
  fZ(0.)
{
  //default constructor
  //cout << "DEFAULT CONSTRUCTOR POINT\n";
}

Point::Point(double x, double y,double z):
  fX(x),
  fY(y),
  fZ(z)
{
  //default constructor
  //cout << "STANDARD CONSTRUCTOR POINT\n";
}

Point::~Point(){
  //cout<<"DESTRUCTOR POINT\n";
}

void Point::PrintStatus() const{
  printf("Point coordinates: X= %f, Y= %f, Z= %f\n", fX, fY, fZ);
}




