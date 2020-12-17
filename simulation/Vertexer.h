#ifndef VERTEXER_H
#define VERTEXER_H

#include <TObject.h>
#include <Riostream.h>
#include "Const.h"
#include "Point.h"
#include "Particle.h"


class Vertexer : public TObject {

  //////////////////////////////////////////////////////////
  // Classe pubblica ad istanza singola utilizzata per la //
  // ricostruzone del vertice                             //
  //////////////////////////////////////////////////////////


 public:
  
  static Vertexer* Instance(const double phistep=gPHISTEP, const double zstep=gZSTEP);
  static void Destroy(); // Permettere di distruggere l'oggetto ad istanza singola

  // Public function
  // Funzione che restituisce la zeta del vertice ricostruito
  // dati gli array dei punti di impatto sui layer e un histo su cui
  // la funzione trova il valore più probabile di zeta prima
  // di calcolare la media su un vector ristretto al range fZStep
  double FindVertexZ(TClonesArray* hits1, TClonesArray* hits2, TH1F* evzdist);

  // Mi stampa i datamember della classe
  void PrintStatus();
  
 private:
  //Costruttori, distruttori privati
  Vertexer(const double phistep, const double zstep);
  Vertexer(const Vertexer& rec);
  Vertexer& operator=(const Vertexer source);
  virtual ~Vertexer();

  //Privete function
  // Mi trova la z dati due punti
  double FindTrackZ(Point* hit1, Point* hit2);

  // private datamember 
  static Vertexer* fgInstance;
  double fZStep;          // Semiampiezza del range in cui il vertexer calcola
                          // la media dato un centro trovato dall'istogramma 
  double fPhiStep;        // Semiampiezza in phi in cui il vertexer considera
                          // due punti correlati
  
  ClassDef(Vertexer,2)
    };
#endif
	
	
	
