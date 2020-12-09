#include <Riostream.h> // cercato nelle directory standard
#include "Particle.h" // cercato non nelle directory standard
#include <TMath.h>


ClassImp(Particle) // da mettere solo se eredita da qualcosa di root
///
//commentp
///


Particle::Particle():
TObject(),
  fPoint(0.,0.,0.),
  fTheta(0.),
  fPhi(0.)
 
{
  //default constructor
  //cout << "DEFAULT CONSTRUCTOR PARTICLE\n";
}

Particle::Particle(double x, double y, double z, double theta, double phi):
  TObject(),
  fPoint(x,y,z),
  fTheta(theta),
  fPhi(phi)
  
{
  //Standard constructor
  //cout << "STANDARD CONSTRUCTOR 1 PARTICLE\n";
}

Particle::Particle(Point p, double theta, double phi):
  TObject(),
  fPoint(p),
  fTheta(theta),
  fPhi(phi)
  
{
  //Standard constructor
  //cout << "STANDARD CONSTRUCTOR 2 PARTICLE\n";
}


Particle::~Particle(){
  //cout<<"DESTRUCTOR PARTICLE\n";
}


Point Particle::GetPoint() const{
  return fPoint;
}

double Particle::GetTheta() const{
  return fTheta;
}

double Particle::GetPhi() const{
  return fPhi;
}

void Particle::PropagateToRadius(double r){
	double t,a,b,x,y,z;
	
	x=fPoint.fX;
	y=fPoint.fY;
	z=fPoint.fZ;
	a = x*sin(fTheta)*cos(fPhi)+y*sin(fTheta)*sin(fPhi);
	b = (sin(fTheta)*cos(fPhi))*(sin(fTheta)*cos(fPhi))+(sin(fTheta)*sin(fPhi))*(sin(fTheta)*sin(fPhi));
	t = (-a+pow((a*a-b*(x*x+y*y-r*r)),0.5))/b;
	
	x+=sin(fTheta)*cos(fPhi)*t;
	y+=sin(fTheta)*sin(fPhi)*t;
	z+=cos(fPhi)*t;
	
	fPoint.fX=x;
	fPoint.fY=y;
	fPoint.fZ=z;
}

void Particle::Rotate(const double thp,const double php){
  double th, ph;
  double v[3];
  double mr[3][3];
  double cd[3];

  th=fTheta;
  ph=fPhi;
  v[0]=TMath::Sin(thp)*TMath::Cos(php);
  v[1]=TMath::Sin(thp)*TMath::Sin(php);
  v[2]=TMath::Cos(thp);

  mr[0][0]=-TMath::Sin(ph);
  mr[1][0]=TMath::Cos(ph);
  mr[2][0]=0;
  mr[0][1]=-TMath::Cos(ph)*TMath::Cos(th);
  mr[1][1]=-TMath::Cos(th)*TMath::Sin(ph);
  mr[2][1]=TMath::Sin(th);
  mr[0][2]=TMath::Sin(th)*TMath::Cos(ph);
  mr[1][2]=TMath::Sin(th)*TMath::Sin(ph);
  mr[2][2]=TMath::Cos(th);

  for(int i=0;i<3;i++){
    cd[i]=0.;
    for(int j=0;j<3;j++){
      cd[i]+=mr[i][j]*v[j];
    }
  }

  CartesianToPolar(cd);
}

void Particle::CartesianToPolar(double *cd){
  double p2=0;
  for (int i=0;i<3;i++)
    p2+=cd[i]*cd[i];

  fTheta=TMath::ACos(cd[2]/TMath::Sqrt(p2));
  
  if(cd[1]>0) fPhi=TMath::ATan2(cd[1],cd[0])+2*TMath::ACos(-1);
  else fPhi=TMath::ATan2(cd[1],cd[0]);
  
}

void Particle::PrintStatus(){
  cout << "Particle status: ";
  fPoint.PrintStatus();
  printf("Tetha e Phi particella: Tetha= %f, Phi= %f \n", fTheta, fPhi);
}
