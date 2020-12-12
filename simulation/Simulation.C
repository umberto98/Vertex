#include <Riostream.h>
#include <TClonesArray.h>
#include <TTree.h>
#include <TFile.h>
#include <TBranch.h>
#include <TH1F.h>
#include <TRandom3.h>
#include "Point.h"
#include "Particle.h"
#include "Generator.h"
#include "Propagator.h"

const int nEV = 1000000;
const bool DISTR = true;
const bool mSCAT = true;
const bool SMEAR = true;
const bool NOISE = true;
const double XYSMEAR = 0.03;
const double ZSMEAR = 0.12;
const double etaRANGE = 2.;
const int BEAMPIPE = 0;
const int LAYER1 = 1;
const int LAYER2 = 2;
const double NS=100;

TH1F* maniphist(double range);

double Simulation(int seed=1){

  gRandom->SetSeed(seed);
  //inizializzo il Generator
  TH1F *etadist = maniphist(etaRANGE);
  if(DISTR){
    TFile F("kinem.root");
    TH1F *distmult = (TH1F*)F.Get("hmul");
    distmult->SetDirectory(0);
    F.Close();
    Generator *gen = Generator::InstanceG(0.1,53.,distmult,etadist); 
    //Generator *gen = Generator::InstanceG(0.1,53.,distmult,disteta); 
  }

  Generator *gen = Generator::InstanceG(0.1,53.,15,etadist);
  gen->PrintStatus();
  //inizializzo il propagator
  Propagator *prop = Propagator::Instance();
  prop->PrintStatus();
  
  //inizializzazione variabili per TTree
  int mult;
  Point genpoint;
  TClonesArray* ptrhits1 = new TClonesArray("Point",300);
  TClonesArray& hits1 =*ptrhits1;
  TClonesArray* ptrhits2 = new TClonesArray("Point",300);
  TClonesArray& hits2 =*ptrhits2;

  //Creo il TTree e relativo file
  TFile hfile("simulation.root","RECREATE");
  // dichiarazione delle branch TTree
  TTree *treep = new TTree("treep","TTree simulazione");
  treep->Branch("VertMult",&mult);
  treep->Branch("GenPoint",&genpoint);
  treep->Branch("HitPoint1",&ptrhits1);
  treep->Branch("HitPoint2",&ptrhits2);

  //Creo un vettore di particelle
  TClonesArray* ptrparts = new TClonesArray("Particle",100);
  TClonesArray& parts = *ptrparts;



  /////simulazione////////
  int fivepercent = ceil(float(nEV-1)/20);
  
  for (int ev=0; ev<nEV; ev++){   
    if(ev != 0 && ev % fivepercent == 0) cout  << " - "<< 100 * float(ev)/nEV << "%" ; 

    ptrparts->Clear("C");
    ptrhits1->Clear("C");
    ptrhits2->Clear("C");

    gen->SimulateEvent(parts);
    mult=gen->GetMult();
    genpoint=gen->GetGenerationPoint();

    //cout << "Event " << ev << endl;
    //gen->GetGenerationPoint().PrintStatus();

    int m1=0, m2=0;
    for(int p=0; p<parts.GetEntries();p++){
      Point hit0,hit1,hit2;
      Particle* part = (Particle*) ptrparts->At(p);  

      //cout<<"Particle " << p << endl;
      //part->PrintStatus();
      
      if(prop->Propagate(*part,hit0,BEAMPIPE))
	if(mSCAT)
	  prop->MultipleScatter(*part);     
      //a->PrintStatus();
      
      if(prop->Propagate(*part,hit1,LAYER1)){
	if(mSCAT)
	  prop->MultipleScatter(*part);
	if(SMEAR)
	  prop->GaussianSmearing(hit1,XYSMEAR,ZSMEAR,LAYER1);
	new(hits1[m1]) Point(hit1);	
	m1++;	
      }
      //a->PrintStatus();
      
      if(prop->Propagate(*part,hit2,LAYER2)){
	if(SMEAR)
	  prop->GaussianSmearing(hit2,XYSMEAR,ZSMEAR,LAYER2);
	new(hits2[m2]) Point(hit2);
	m2++;
      }
      //a->PrintStatus();
      
      //cout << "\n";
    }
    if(NOISE){
      int pn1=gRandom->Gaus(NS,10);
      Point p1(0,0,0);
      int pn2=gRandom->Gaus(NS,10);
      for(int n=m1;n<m1+pn1;n++){
	prop->NoisePoint(p1,LAYER1);
	new(hits1[m1]) Point(p1);
      }
      for(int n=m2;n<m2+pn2;n++){
	prop->NoisePoint(p1,LAYER2);
	new(hits2[m2]) Point(p1);
      }
    }
    // cout << "\n \\-------------------------------------\\ \n";
    treep->Fill();    
  }

  //distruggo generator e propagator
  gen->Destroy();
  prop->Destroy();
  
  // Close and write file.
  hfile.Write();
  hfile.Close();

  cout << "\n";
  return 0;
  
}





//_______________________________________________________
//funzione per creare un TH1F nel range voluto
TH1F* maniphist(double range){
  TFile F("kinem.root");
  TH1F *disteta = (TH1F*)F.Get("heta");
  disteta->SetDirectory(0);
  disteta->SetMinimum(0);
  F.Close();
  TAxis *xa=disteta->GetXaxis();
  Double_t step = xa->GetBinWidth(1);
  Int_t b1=xa->FindBin(-range);
  Int_t b2=xa->FindBin(range);
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
