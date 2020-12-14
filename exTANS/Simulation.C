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
#include "Reconstruction.h"
#include "Const.h"

TH1F* maniphist(double range);

double Simulation(const int seed=1, const char* title="simulation.root"){

  gRandom->SetSeed(seed);
  //inizializzo il Generator
  TH1F *etadist = maniphist(gETARANGE);
  if(gDISTR!=0){
    TH1F *distmult;
    if(gDISTR==1){
      TFile F("kinem.root");
      distmult = (TH1F*)F.Get("hmul");
      distmult->SetDirectory(0);
      F.Close();
    }else{
      TFile F("mult.root");
      distmult = (TH1F*)F.Get("hmulun");
      distmult->SetDirectory(0);
      F.Close();
    }
    Generator *gen = Generator::InstanceG(gXYRMS,gZRMS,distmult,etadist);  
  }

  Generator *gen = Generator::InstanceG(gXYRMS,gZRMS,15,etadist); //Inizializza il generator con molteplicità fissa al valore inserito
  //Generator *gen = Generator::InstanceG();		//Inizializza il generator con molteplicità fissa e eta estratto uniformemente
  gen->PrintStatus();
  //inizializzo il propagator
  Propagator *prop = Propagator::Instance();		//inizializza il Propagator standard
  prop->PrintStatus();


  //inizializzazione variabili per TTree
  int mult;
  Point genpoint;
  TClonesArray* ptrhits1 = new TClonesArray("Point",100);
  TClonesArray& hits1 =*ptrhits1;
  TClonesArray* ptrhits2 = new TClonesArray("Point",100);
  TClonesArray& hits2 =*ptrhits2;

  //Creo il TTree e relativo file
  TFile hfile(title,"RECREATE");
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
  
  for (int ev=0; ev<gNEV; ev++){   

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
      
      if(prop->Propagate(*part,hit0,gBEAMPIPE))
	if(gMSCAT)
	  prop->MultipleScatter(*part);     
      //a->PrintStatus();
      
      if(prop->Propagate(*part,hit1,gLAYER1)){
	if(gMSCAT)
	  prop->MultipleScatter(*part);
	new(hits1[m1]) Point(hit1);	
	m1++;	
      }
      //a->PrintStatus();
      
      if(prop->Propagate(*part,hit2,gLAYER2)){
	new(hits2[m2]) Point(hit2);
	m2++;
      }
      //a->PrintStatus();
      
      //cout << "\n";
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
  char titolo[50];
  sprintf(titolo,"#eta distribution, range: %f",range);
  TH1F* heta2 = new TH1F("hetadist",titolo,nobins,xlow,xhig);
  Int_t j=1;
  for(Int_t i=b1;i<=b2;i++)heta2->SetBinContent(j++,disteta->GetBinContent(i)); 
  return heta2;
}
