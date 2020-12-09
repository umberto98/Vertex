// Staff to do:
//Extract z with normal dist, RMS=53mm, x,y normal with RMS=0.1mm;
//Generate mult from assigned distribution
//Generate direction With phi uniform [0,2pi], theta from uniform or assigned pseudorapidity(inversion)


#include <Riostream.h>
#include <TMath.h>
#include "Generator.h"
#include <TClonesArray.h>
#include <TTree.h>
#include <TFile.h>
#include <TBranch.h>
#include <TString.h>
#include "Point.h"
#include "Propagator.h"

TH1F* maniphist();

void Generation(){ 

  TFile F("kinem.root");
  TH1F *disteta = maniphist();
  TH1F *distmult = (TH1F*)F.Get("hmul");
  Generator *gen = new Generator();
  
  Propagator *prop = Propagator::Instance();
  prop->PrintStatus();
  

  TClonesArray* ptrparts = new TClonesArray("Particle",100);
  TClonesArray& parts = *ptrparts;
  Point hit0,hit1,hit2;
  
  for (int j=0; j<2; j++){
    cout << "Event " << j << endl;
    //mult=Prova.RndmMult();
    ptrparts->Clear("C");
    gen->SimulateEvent(parts);
    gen->GetGenerationPoint().PrintStatus();
    for(int i=0; i<parts.GetEntries();i++){
      cout<<"Particle " << i << endl;
      Particle* a= (Particle*) ptrparts->At(i);
      a->PrintStatus();
      hit0=prop->Propagate(*a,0);
      a->PrintStatus();
      prop->MultipleScatter(*a);
      hit1=prop->Propagate(*a,1);
      a->PrintStatus();
      prop->MultipleScatter(*a);
      hit2=prop->Propagate(*a,2);
      a->PrintStatus();
      cout << "\n \n";
    }
    cout << "\n \\-------------------------------------\\ \n";

  }
  delete gen;
  prop->Destroy();
  cout << "ho finito";
}

TH1F* maniphist(){
  TFile F("kinem.root");
  TH1F *disteta = (TH1F*)F.Get("heta");
  disteta->SetDirectory(0);
  disteta->SetMinimum(0);
  F.Close();
  TAxis *xa=disteta->GetXaxis();
  Double_t step = xa->GetBinWidth(1);
  Int_t b1=xa->FindBin(-2.);
  Int_t b2=xa->FindBin(2.);
  Double_t xlow=xa->GetBinLowEdge(b1);
  Double_t xhig=xa->GetBinUpEdge(b2);
  Int_t nobins=b2-b1+1;
  Double_t step2 = (xhig-xlow)/nobins;
  cout << "Check: "<<step<<"; "<<step2<<endl;
  TH1F* heta2 = new TH1F("hetadist","#eta distribution 2",nobins,xlow,xhig);
  Int_t j=1;
  for(Int_t i=b1;i<=b2;i++)heta2->SetBinContent(j++,disteta->GetBinContent(i));
 
  return heta2;
}
