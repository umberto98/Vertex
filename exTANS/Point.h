#ifndef POINT_H
#define POINT_H

#include "TObject.h"

class Point : public TObject{

  //////////////////////////////////////////////////////////
  // Classe pubblica utilizzata per rappresentare un punto//
  // nello spazio tridimensionale in coordinate cartesiane//
  //////////////////////////////////////////////////////////

 public:
  
  Point(double x=0., double y=0., double z=0.);
  Point(const Point& point); 
  virtual ~Point();

  // public data member
  double fX;  //Coordinata x
  double fY;  //Coordianta y
  double fZ;  //Coordinata z

  // public function
  void PrintStatus() const;  //Stampa i datamember -> x,y,z del punto

  // Restituisce il raggio in cordinate cilindriche a partire
  // dai data member in coordinate cartesiane del punto
  double GetR() const;       

  // Restituisce la coordinata Phi in cilindriche a partire
  // dai data member della classe espressi in cartesiane
  double GetPhi() const;

  // Modifica i datamember della classe effettuando una traslazione
  // del punto con direzione phi in coordinate cilindriche; il punto
  // viene portato ad una distanza r   
  void SetR(double r);

  // Modifica i datamember della classe effettuando una rotazione
  // del punto attorno all'asse z di un angolo phi
  void SetPhi(double phi);
  
  ClassDef(Point,2)
};

#endif
