#ifndef PROPAGATOR_H
#define PROPAGATOR_H

#include <TObject.h>
#include <Riostream.h>
#include "Particle.h"
#include "Point.h"
#include "Const.h"

class Propagator : public TObject {
  /////////////////////////////////////////////////////////////////
  // Classe pubblica utilizzata per propagare una particella sui //
  // layer del rivelatore i data member privati rappresentano la //
  // geometria del rivelatore sono espresse in mm                //
  /////////////////////////////////////////////////////////////////

 public:

  //funzione statica per rendere la classe singleton
  static Propagator* Instance(const double rbp=gRBP, const double r1=gRL1, const double r2=gRL2,
			      const double l1=gLENL1, const double l2=gLENL2,
			      const double dbp=gDEPBP, const double d1=gDEPL1);
  
  static void Destroy(); // funzione per eliminare l'ogetto Propagator
  void PrintStatus() const;// stampa lo stato del Propagator->geometria rivelatore

  // Funzione che propaga la particella al layer che si vuole,
  // modifica i datamember della particella e modifica il punto passato
  // per riferimento facendolo coincidere con l'hitpoint
  bool Propagate(Particle &particle,Point &point, const int layer);

  // funzione che implementa il multiplescatter
  // ->modifica i datamember della particella
  void MultipleScatter(Particle &particle);
  
  
 private:

  //costruttore, distruttore... privati per creare classe singleton
  Propagator(const double rbp, const double r1, const double r2,
	     const double l1, const double l2,
	     const double dbp, const double d1);
  Propagator(const Propagator& rec);
  Propagator& operator=(const Propagator &source);
  virtual ~Propagator();

  // private function
  // funzione che restituisce true se il layer è stato colpito data la z
  // della particella e la lunghezza del layer
  bool IsHit(const double zpart, const double lenght);
  
  // private datamember
  static Propagator* fgInstance;

  const double rmsScatt=0.001; //rms di teta nel multiple scatter
  double rBp;         //raggio beampipe
  double rLay1;       //raggio layer1
  double rLay2;       //raggio layer2
  double fLenght1;    //lunghezza layer1
  double fLenght2;    //lunghezza layer2
  double fDepthBp;    //spessore layer1
  double fDepth1;     //spessore layer2
  //altri datamember che possono essere implementati
  //double fDepth2;
  //double fMaterialIDBp;
  //double fMaterialID1;
  //double fMaterialID2;

  ClassDef(Propagator,0)
    };

#endif
