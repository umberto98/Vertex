#ifndef GENERATOR_H  
#define GENERATOR_H

#include "TObject.h"
#include "Point.h"
#include "Particle.h"
#include <TString.h>
class Generator : public TObject{
  /////////
  //----------------------This class simulate particle production in 1 collision event----------------//
  //////// 
 public:
  
   Generator();
   Generator(double seed, int mult, double xyrms, double zrms, double psdraprng); //Generates 1 event with assigned multiplicity and symmetrical pseudorapidity range//
   
   //---------------------Altri Costruttori che per il momento non implemento----------------------------//
   
   /*
   Generator(int mult, double xyRMS, double zRMS, double (*psdrapdist) (double, double*)); //Generates 1 event with assigned multiplicity and assigned pseudorapidity distribution//
   Generator(int (*multdist) (double, double*), double xyRMS, double zRMS, double psdraprng);//Generates 1 event with assigned multiplicity distribution and assigned pseudorapidity range//
   Generator(int (*multdist) (double, double*), double xyRMS, double zRMS, double (*psdrapdist) (double, double*));  //Generates 1 event with assigned multiplicity and pseudorapidity distributions//
   */
   virtual ~Generator();
   
   
   Point fProdPoint;
   Particle *fProdParticles;
   
   void SetSeed(double seed);
   void SetMult(double mult);
   void SetXYrms(double xyrms);
   void SetZrms(double zrms);
   void SetPsdrapRng(double psdraprng);
   
   void SaveParticlesToFile(TString filename);
 
 private:
 
   int fMult;
   double fXYrms;
   double fZrms;
   double fPsdrapRng; 
   double fSeed;
   
   double PsdrapInv (double eta);
   
  ClassDef(Generator,1) 
 
 };
#endif  
 

  
