#ifndef POINT_H
#define POINT_H

#include "TObject.h"

class Point{

 public:

  double fX;
  double fY;
  double fZ;

  Point();
  Point(double x, double y, double z);
  virtual ~Point();

  void PrintStatus() const;
  
  ClassDef(Point,2)
  
};

#endif
