#ifndef RECONSTRUCTION_H
#define RECONSTRUCTION_H

#include <TObject.h>
#include <Riostream.h>
#include "Point.h"
#include "Const.h"

class Reconstruction : public TObject {
  /////////////////////////////////////////////////////////////////
  // Classe pubblica utilizzata per la ricostruzione degli hit   //
  // sui layer del rivelatore, i data member privati sono dati   //
  // dalla geometria del rivelatore, sono espressi in mm         //
  /////////////////////////////////////////////////////////////////

 public:

  //funzione statica per rendere la classe singleton
  static Reconstruction* Instance(const double rphirms=gRPHISM, const double zrms=gZSM,
				 const double r1=gRL1, const double r2=gRL2,
				 const double l1=gLENL1, const double l2=gLENL2);

  static void Destroy(); // funzione per eliminare l'ogetto Recostruction
  
  // Dati l'RMS rphi, e l' RMSz, e il layer applica
  // lo smearing gaussiano al punto passato per riferimento
  void GaussianSmearing(Point &point, const int layer);

  // Dato un punto e il layer, posiziona il punto in modo casuale sul layer
  void NoisePoint(Point &point, const int layer);

  void PrintStatus();

 private:

  Reconstruction(const double rphirms, const double zrms,
		const double r1, const double r2,
		const double l1, const double l2);
  Reconstruction(const Reconstruction& rec);
  Reconstruction& operator=(const Reconstruction &source);
  virtual ~Reconstruction();

  // private datamember
  static Reconstruction* fgInstance;
  
  double fRphi;       //Rms rphi per lo smearing 
  double fZ;          //Rms z per lo smearing 
  double rLay1;       //raggio layer1
  double rLay2;       //raggio layer2
  double fLenght1;    //lunghezza layer1
  double fLenght2;    //lunghezza layer2

  ClassDef(Reconstruction,0)
    };

#endif