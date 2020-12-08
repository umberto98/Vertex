#ifndef POINT_H
#define POINT_H

#include "TObject.h"

class Point{

 public:

// coordinate cartesiane 
  double fX;
  double fY;
  double fZ;

//coordinate cilindriche
	double fR;
	double fPhi;

  Point();
  Point(bool cart, double x_r, double y_phi, double z);
  virtual ~Point();

  void PrintStatus() const;
  
  ClassDef(Point,2)
  
};

#endif
