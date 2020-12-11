#include <Riostream.h> // cercato nelle directory standard
#include "Particle.h" // cercato non nelle directory standard
#include <TMath.h>

using namespace TMath;

ClassImp(Particle)

  ////////////////////////////////////////////////////////////////
  // Implementazione della classe particella                    //
////////////////////////////////////////////////////////////////

//____________________________________________________________
Particle::Particle(double x, double y, double z, double theta, double phi):TObject(),
  fPoint(x,y,z),
  fTheta(theta),
  fPhi(phi){
  // Standard constructor
  }

//___________________________________________________________
Particle::Particle(Point p, double theta, double phi):
  TObject(),
  fPoint(p),
  fTheta(theta),
  fPhi(phi){
  // Standard constructor 2
  }

//_________________________________________________________
Particle::~Particle(){
  // default destructor
}

//__________________________________________________________
void Particle::PrintStatus() const{
  cout << "Particle status: ";
  fPoint.PrintStatus();
  printf("Theta e Phi: Theta= %f, Phi= %f \n", fTheta, fPhi);
}

//_________________________________________________________
Point Particle::GetPoint() const{
  return fPoint;
}

//_________________________________________________________
double Particle::GetTheta() const{
  return fTheta;
}

//_________________________________________________________
double Particle::GetPhi() const{
  return fPhi;
}

//_________________________________________________________
void Particle::PropagateToRadius(double r){
  double t,a,b,x,y,z;
  
  x=fPoint.fX;
  y=fPoint.fY;
  z=fPoint.fZ;
  a = x*Sin(fTheta)*Cos(fPhi)+y*Sin(fTheta)*Sin(fPhi);
  b = (Sin(fTheta)*Cos(fPhi))*(Sin(fTheta)*Cos(fPhi))+(Sin(fTheta)*Sin(fPhi))*(Sin(fTheta)*Sin(fPhi));
  t = (-a+pow((a*a-b*(x*x+y*y-r*r)),0.5))/b;
  //trovo le nuove coordinate propagando la particella ad una distanza r da z
  x+=Sin(fTheta)*Cos(fPhi)*t;
  y+=Sin(fTheta)*Sin(fPhi)*t;
  z+=Cos(fPhi)*t;
  //aggiorno il datamember punto di particle
  fPoint.fX=x;
  fPoint.fY=y;
  fPoint.fZ=z;
}

//_________________________________________________________
void Particle::Rotate(const double thp,const double php){
  double th, ph;  // angoli prima della deviazione
  double v[3];    // vettore colonna con angoli della deviazione
  double mr[3][3];// matrice con angoli prima della deviazione
  double cd[3];   // vettore che rappresenta la direzione di propagazione
                  // in coordinate cartesiane 
  th=fTheta;
  ph=fPhi;
  
  v[0]=Sin(thp)*Cos(php);
  v[1]=Sin(thp)*Sin(php);
  v[2]=Cos(thp);

  mr[0][0]=-Sin(ph);
  mr[1][0]=Cos(ph);
  mr[2][0]=0.;
  mr[0][1]=-Cos(ph)*Cos(th);
  mr[1][1]=-Cos(th)*Sin(ph);
  mr[2][1]=Sin(th);
  mr[0][2]=Sin(th)*Cos(ph);
  mr[1][2]=Sin(th)*Sin(ph);
  mr[2][2]=Cos(th);

  // Prodotto matriciale
  for(int i=0;i<3;i++){
    cd[i]=0.;
    for(int j=0;j<3;j++){
      cd[i]+=mr[i][j]*v[j];
    }
  }

  CartesianToPolar(cd); //dati i vettori della direzione di propagazione
                        //modifico i datamember della particella
}

//______________________________________________________________
void Particle::CartesianToPolar(double *cd){
  double p2=0;           //trovo la norma per normalizzare
  for (int i=0;i<3;i++)
    p2+=cd[i]*cd[i];

  fTheta=ACos(cd[2]/Sqrt(p2));
  
  if(cd[1]<0)
    fPhi=ATan2(cd[1],cd[0])+2*ACos(-1);
  else
    fPhi=ATan2(cd[1],cd[0]);
}

