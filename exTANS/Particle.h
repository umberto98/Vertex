#ifndef PARTICLE_H
#define PARTICLE_H

#include "TObject.h"
#include "Point.h"

class Particle : public TObject{

  ////////////////////////////////////////////////////////////////
  // Classe pubblica utilizzata per rappresentare una particella//
  // con tre data member privati che rappresentano il suo stato //
  // ->Posizione in cordinate cartesiane e direzione in         //
  //   coordinate sferiche                                      //
  // ->Varie funzioni che modificano lo stato della particella  //
  ////////////////////////////////////////////////////////////////

  
 public:
  
  Particle(double x=0., double y=0., double z=0., double theta=0., double phi=0.);
  Particle(Point p, double theta, double phi);
  virtual ~Particle();

  // public methods

  void PrintStatus() const;// stampa i data member della classe -> x,y,z,theta,phi
  Point GetPoint() const;  // restituisce il datamember point -> posizione x,y,z
  double GetTheta() const; // restituisce il datamember theta -> theta
  double GetPhi() const;   // restituisce il datamember phi -> phi

  // Funzione che modifica il data member point della particella
  // la propaga fino ad una distanza r dall'asse z 
  void PropagateToRadius(double r);

  // Funzione che modifica la direzione di propagazione della particella,
  // se subisce una deviazione in thp e php rispetto alla sua direzione
  // di propagazione
  void Rotate(double thp, double php);
 

 private:

  // private methods

  // Data la terna cd che rappresenta la direzione di propagazione
  // in coordinate cartesiane, modifica i datamember della particella
  // theta e phi 
  void CartesianToPolar(double *cd);

  // private data member
  
  Point fPoint;  // Punto in cui si trova la particella in coordinate cartesiane
  double fTheta; // Angolo polare [0,pi] -> direzione di propagazione
  double fPhi;   // Angolo azimutale [0,2pi] -> direzione di propagazione

  
  ClassDef(Particle,2)
    };
 
#endif
