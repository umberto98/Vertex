#ifndef PROPAGATOR_H
#define PROPAGATOR_H

#include <TObject.h>
#include <Riostream.h>
#include "Particle.h"
#include "Point.h"


class Propagator : public TObject {

 public:

  static Propagator* Instance(const double rbp=30., const double r1=40., const double r2=70.,
			      const double l1=270.0, const double l2=270.0,
			      const double dbp=8., const double d1=2.);
  static void Destroy();

  bool Propagate(Particle &particle,Point &point, const int layer);
  void PrintStatus();
  void MultipleScatter(Particle &particle);
  void GaussianSmearing(Point &point, const double rphiRMS=0.1, const double zRMS=15., int layer=0);

 private:
  
  Propagator(const double rbp, const double r1, const double r2,
	     const double l1, const double l2,
	     const double dbp, const double d1);
  Propagator(const Propagator& rec);
  Propagator& operator=(const Propagator &source);
  virtual ~Propagator();

  bool IsHit(const double zpart, const double lenght);
  

  static Propagator* fgInstance;
  double rBp;
  double rLay1;
  double rLay2;
  double fLenght1;
  double fLenght2;
  double fDepthBp;
  double fDepth1;
  //double fDepth2;
  //double fMaterialIDBp;
  //double fMaterialID1;
  //double fMaterialID2;

  ClassDef(Propagator,0)
    };

#endif
  
