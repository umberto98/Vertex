#ifndef GENERATOR_H  
#define GENERATOR_H

#include "TObject.h"
#include "Point.h"
#include "Particle.h"

class Generator : public TObject{
  /////////
  //----------------------This class simulate particle production in 1 collision event----------------//
  //////// 
 public:
  
   Generator();
   Generator(int mult, double xyRMS, double zRMS, double psdraprng); //Generates 1 event with assigned multiplicity and symmetrical pseudorapidity range//
   
   //---------------------Altri Costruttori che per il momento non implemento----------------------------//
   
   /*
   Generator(int mult, double xyRMS, double zRMS, double (*psdrapdist) (double, double*)); //Generates 1 event with assigned multiplicity and assigned pseudorapidity distribution//
   Generator(int (*multdist) (double, double*), double xyRMS, double zRMS, double psdraprng);//Generates 1 event with assigned multiplicity distribution and assigned pseudorapidity range//
   Generator(int (*multdist) (double, double*), double xyRMS, double zRMS, double (*psdrapdist) (double, double*));  //Generates 1 event with assigned multiplicity and pseudorapidity distributions//
   */
   virtual ~Generator();
   
   //void SaveToFile();
   Point fprodP;
   Particle fprodPart;
 
 private:
 
   int fmult;
   double fxyRMS;
   double fzRMS;
   double fpsdraprng; 
   
   double PsdrapInv (double eta);
   
  ClassDef(Generator,1) 
 
 
 };
#endif  
 

  
