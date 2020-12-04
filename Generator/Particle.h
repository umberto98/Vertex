#ifndef PARTICLE_H  //serve a non ricompilare ogni volta che viene chiamata la classe, il compilatore deve includere l'header una volta sola
#define PARTICLE_H
//è un eder file, vengono inclusi in implementazioni dell'header, oltre a funzioni stand-alone, come le macro

#include "TObject.h"
#include "Point.h"

class Particle : public TObject{
  /////////
  //commento al codice
  ////////
 public:
  
  Particle();//inizializza tutti i datamember a 0
  Particle(double x, double y, double z, double teta, double phi, double t);//costruttore std, assegna valori a data member
  Particle(Point p, double teta, double phi, double t);
  virtual ~Particle(); //da mettere solo se alloca memoria la classe
  // le member function sono virtuali se possono essere implementato da classi figlie, posso chiamarle nella classe madre attraverso puntatori che puntano a classi figlie dove sono implementati


//forse poi verranno tolti, per il momento restano lì...
  Point fPointTemp; 
  double fThetaTemp;
  double fPhiTemp;
  double fT;

  Point GetPoint() const;
  double GetTheta() const;
  double GetPhi() const;
  Point GetPointTemp() const;
  double GetThetaTemp() const;
  double GetPhiTemp() const;
  double GetTime() const;
  void SetTime(double t);
  void SetPointTemp(double x, double y, double z, double theta, double phi);
  void SetPointTemp(Point point, double teta, double phi);

 private:  // inizializzati quando generi la particella

  Point fPoint; 
  double fTheta;
  double fPhi;

  //coding convention, usare anche commenti a destra doppio il doppio slash a destra del data member, es //! non mi salva il file nello streamer che costruisce root
  ClassDef(Particle,2) // dice a root che questa è la versione 1, se cambio la classe, esempio aggiungendo un datamember metto un 2 nella ClassDef(); quando leggo un oggetto da file guarda la versione e mi legge l'header della versione corrispondente. Se metto 0 root non si cura di creare uno streamer, l'oggetto non ha persistenza
    
    };
//solitamente non c'è il punto e virgola, nell'header sì 
#endif
