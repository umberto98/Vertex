#ifndef POINT_H
#define POINT_H

#include "TObject.h"

class Point : public TObject{

 public:

  Point();
  Point(double x, double y, double z);
  virtual ~Point();

  void PrintStatus() const;
  
// coordinate cartesiane 
  double fX;
  double fY;
  double fZ;

  double GetR() const;
  double GetPhi() const;
  void SetR(double r);
  void SetPhi(double phi);
  
	ClassDef(Point,2)
};

#endif
