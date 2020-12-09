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
#include <TCanvas.h>
#include <TH1D.h>

TH1F* maniphist();

void Simulation(){ 

  TFile F("kinem.root");
  TH1F *disteta = maniphist();
  TH1F *distmult = (TH1F*)F.Get("hmul");
  F.Close();

  int mult;
  Point genpoint;  
  vector<double>* hitx1 = NULL;
  vector<double>* hity1 = NULL;
  vector<double>* hitz1 = NULL;
  vector<double>* hitx2 = NULL;
  vector<double>* hity2 = NULL;
  vector<double>* hitz2 = NULL;
  TFile hfile("htree.root","RECREATE");
  // dichiarazione del TTree
  TTree *tree = new TTree("T","TTree simulazione");
  tree->Branch("VertMult",&mult);
  tree->Branch("GenPoint",&genpoint);
  tree->Branch("Hit1PointX",&hitx1);
  tree->Branch("Hit1PointY",&hity1);
  tree->Branch("Hit1PointZ",&hitz1);
  tree->Branch("Hit2PointX",&hitx2);
  tree->Branch("Hit2PointY",&hity2);
  tree->Branch("Hit2PointZ",&hitz2);
  
  Generator *gen = new Generator(100,0.01,5.3,2);
  
  Propagator *prop = Propagator::Instance();
  prop->PrintStatus();
  

  TClonesArray* ptrparts = new TClonesArray("Particle",100);
  TClonesArray& parts = *ptrparts;
  Point hit0,hit1,hit2,genp;

  
  for (int j=0; j<100; j++){
    //cout << "Event " << j << endl;
    ptrparts->Clear("C");
    gen->SimulateEvent(parts);
    //gen->GetGenerationPoint().PrintStatus();
    //mult=gen->GetMult(); Da Implementare
    mult=2;
    genpoint=gen->GetGenerationPoint();
    
    for(int i=0; i<parts.GetEntries();i++){
      //cout<<"Particle " << i << endl;
      Particle* a= (Particle*) ptrparts->At(i);  
      //a->PrintStatus();
      
      hit0=prop->Propagate(*a,0);
      prop->MultipleScatter(*a);
      //a->PrintStatus();
      
      hit1=prop->Propagate(*a,1);
      prop->MultipleScatter(*a);
      //a->PrintStatus();
      hitx1->push_back(hit1.fX);
      hity1->push_back(hit1.fY);
      hitz1->push_back(hit1.fZ);
      
      hit2=prop->Propagate(*a,2);
      //a->PrintStatus();
      hitx2->push_back(hit2.fX);
      hity2->push_back(hit2.fY);
      hitz2->push_back(hit2.fZ);
      
      //cout << "\n \n";
    }
    // cout << "\n \\-------------------------------------\\ \n";
    tree->Fill();    
  }
  
  delete gen;
  prop->Destroy();
  cout << "ho finito";
  hfile.Write();

  // Close the file. 
  hfile.Close();

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
