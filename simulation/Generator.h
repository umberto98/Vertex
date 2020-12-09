#ifndef GENERATOR_H  
#define GENERATOR_H

#include "TObject.h"
#include "Point.h"
#include "Particle.h"
#include <TString.h>
#include <TClonesArray.h>
#include <TH1.h>
class Generator : public TObject{
  /////////
  //----------------------This class simulate particle production in 1 collision event----------------//
  //////// 
 public:
  
   Generator(int mult=2, double xyrms=0.01, double zrms=5.3, double psdraprng=1); //Generates 1 event with assigned multiplicity and uniform pseudorapidity diatribution on assigned range//
    Generator(double xyRMS, double zRMS, TH1F* multdist, TH1F* etadist);  //Generates 1 event with assigned multiplicity and pseudorapidity distributions//
  //NB allo stato attuale si implementa solo la distribuzione in eta, DA MODIFICARE!!!!!!
  
   
   virtual ~Generator();
   
   
   void SetMult(double mult);
   void SetXYrms(double xyrms);
   void SetZrms(double zrms);
   void SetPsdrapRng(double psdraprng);
   Point GetGenerationPoint();
   
   //void SaveParticlesToFile(TString filename);
   void SimulateEvent(TClonesArray &genparts);
   int RndmMult();
   
 private:

   Point fGenP;
   int fMult;
   double fXYrms;
   double fZrms;
   double fPsdrapRng; 
   bool fDist;
   TH1F *fEtaDist;
   TH1 *fMultDist;
  
   double PsdrapInv (double eta);

   
  ClassDef(Generator,1) 
 
 };
#endif  
 

  
