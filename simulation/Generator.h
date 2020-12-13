#ifndef GENERATOR_H  
#define GENERATOR_H

#include "TObject.h"
#include "Point.h"
#include "Particle.h"
#include "Const.h"
#include <TClonesArray.h>
#include <TH1F.h>

class Generator : public TObject{
  ////////////////////////////////////////////////////////////////////////////
  // This singleton class simulate particle production in 1 collision event
  // Le grandezze sono espresse in mm e rappresentano la geometria del rivelatore
  ////////////////////////////////////////////////////////////////////////////

 public:

  static Generator* InstanceG(const double xyrms=gXYRMS, const double zrms=gZRMS,
			      const int mult=gMULT, const double etarange=gETARANGE);
  static Generator* InstanceG(const double xyrms, const double zrms,
			      const int mult, const TH1F* etadist);
  static Generator* InstanceG(const double xyrms, const double zrms,
			      const TH1F* multdist, const TH1F* etadist);
  
  static void Destroy(); // Permettere di distruggere l'oggetto ad istanza singola

  // Public function
  //void SetMult(double mult);
  //void SetPsdrapRng(double psdraprng);

  // Restituisce il punto di generazione delle particelle
  // -> posizione in cui avviene l'urto
  Point GetGenerationPoint() const;  
  int GetMult() const;  // Restituisce la molteplicità dell'evento

  // Simula una array di particelle prodotte dopo l'urto,
  // tutte con stesso punto di origine ma con diversi theta e phi
  void SimulateEvent(TClonesArray &genparts);
  void PrintStatus() const;

  
 private:

  //Costruttori, distruttori privati
  Generator(const double xyrms, const double zrms, const int mult,const double etarange);
  Generator(const double xyrms, const double zrms, const int mult,const TH1F* etadist); //Generates 1 event with assigned multiplicity and uniform pseudorapidity diatribution on assigned range//
  Generator(const double xyRMS, const double zRMS,const TH1F* multdist, const TH1F* etadist);  //Generates 1 event with assigned multiplicity and pseudorapidity distributions//

  Generator(const Generator& rec);
  Generator& operator=(const Generator &source);
  virtual ~Generator();

  //Privete function
  //Returns theta given pseudorapidity eta
  double PsdrapInv (double eta);

   // private datamember  
  static Generator* fgInstance;
  Point fGenP;        //punto di generazione->urto
  double fXYrms;      //rms di x e y del punto di generazione
  double fZrms;       //rms di z del punto di generazione
  double fPsdrapRng;  //Range in pseudorapidità
  int fMult;          //molteplicità evento
  const TH1F *fEtaDist;     //distribuzione in pseudorapidità
  const TH1F *fMultDist;     //distribuzione in molteplicità

  
  ClassDef(Generator,1) 
 
 };
#endif  
 

  
