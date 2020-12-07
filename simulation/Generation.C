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

TH1F* maniphist();

void Generation(){
  TFile F("kinem.root");
  TH1F *disteta = maniphist();
  TH1F *distmult = (TH1F*)F.Get("hmul");
  Generator Prova(15.3,0.1,53.,distmult,disteta);

  TClonesArray* ptrparts = new TClonesArray("Particle",100);
  TClonesArray& parts = *ptrparts;

  int mult;
  for (int j=0; j<20; j++){    
    Point p;
    mult=Prova.RndmMult();
    //TClonesArray parts("Particle",mult);
    ptrparts->Clear("C");
    Prova.SimulateEvent(p,parts);
    p.PrintStatus();
    for(int i=0; i<parts.GetEntries();i++){
      Particle* a=(Particle*) ptrparts->At(i);
      cout<<"theta della particella"<<i<<": "<<a->GetTheta()<<endl;
    }
  }
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
