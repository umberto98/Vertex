#include <TMath.h>
#include <TH1F.h>
#include <TClonesArray.h>
#include <vector>
#include "Vertexer.h"

using namespace std;

ClassImp(Vertexer)

Vertexer* Vertexer::fgInstance=NULL;

//---------------------------------------------------------------------
Vertexer::Vertexer(const double phistep, const double zstep):TObject(),
fPhiStep(phistep),
fZStep(zstep)
{
//standard constructor
}

//---------------------------------------------------------------------
Vertexer:: ~Vertexer(){
//Default Destructor
}

//---------------------------------------------------------------------
Vertexer* Vertexer::Instance(const double phistep, const double zstep){
  if(!fgInstance){
    fgInstance = new Vertexer(phistep, zstep);
  }
  return fgInstance;
}

//---------------------------------------------------------------------
void Vertexer::Destroy(){
  if(fgInstance)delete fgInstance;
  fgInstance = NULL;
}

//---------------------------------------------------------------------
double Vertexer::FindTrackZ(Point* hit1, Point* hit2){
	double r1, z1, r2, z2;
	r1=hit1->GetR();
	z1=hit1->fZ;
	r2=hit2->GetR();
	z2=hit2->fZ;
	return (z2*r1-z1*r2)/(r1-r2);
}

//---------------------------------------------------------------------
double Vertexer::FindVertexZ(TClonesArray* hits1, TClonesArray* hits2, TH1F* evzdist){
  vector <double> tracksz;
  for (int i=0; i<hits1->GetEntries(); i++){
    Point *hit1=(Point*)hits1->At(i);
    double phi1=hit1->GetPhi();
    for (int j=0; j<hits2->GetEntries(); j++){
      Point *hit2=(Point*)hits2->At(j);
      double phi2=hit2->GetPhi();
      if (TMath::Abs(phi2-phi1)<fPhiStep){
	double z=FindTrackZ(hit1, hit2);
	evzdist->Fill(z);
	tracksz.push_back(z);
      }
    }
  }
  if (tracksz.size()==0) {
    evzdist->Reset();
    return 999999;
  }
  //solo se si vuole rappresentare istogramma, sconsigliato in un loop
  //evzdist->DrawCopy();
  int max=evzdist->GetMaximum();
  int binmax = evzdist->GetMaximumBin(); 
  double bincentre=evzdist->GetXaxis()->GetBinCenter(binmax);
  int c1=evzdist->GetBinContent(binmax-1);
  int c2=evzdist->GetBinContent(binmax+1);

  evzdist->SetBinContent(binmax,0);
  evzdist->SetBinContent(binmax-1,0);
  evzdist->SetBinContent(binmax+1,0);

  int max2=evzdist->GetMaximum();
  int binmax2=evzdist->GetMaximumBin();
  if (max2==max) {
    evzdist->Reset();
    return 999999;
  }

  int l=0;
  double vertz=0;

  for(unsigned int k=0; k<tracksz.size();k++)
    if (TMath::Abs(tracksz[k]-bincentre)<fZStep){
      vertz+=tracksz[k];
      l++;
    }
  vertz=vertz/l;
  
  evzdist->Reset();
  return vertz;
}

//---------------------------------------------------------------
void Vertexer::PrintStatus(){
  cout << "Semiampiezza in phi in cui il Vertexer considera due hit correlate: " << fPhiStep << endl
       << "La media in z viene calcolata in un range +- [mm]: " << fZStep
       << endl;
}
