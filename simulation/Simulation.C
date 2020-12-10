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
  TClonesArray* ptrhits1 = new TClonesArray("Point",100);
  TClonesArray& hits1 =*ptrhits1;
  TClonesArray* ptrhits2 = new TClonesArray("Point",100);
  TClonesArray& hits2 =*ptrhits2;
  
  TFile hfile("htree.root","RECREATE");
  // dichiarazione del TTree
  TTree *tree = new TTree("T","TTree simulazione");
  tree->Branch("VertMult",&mult);
  tree->Branch("GenPoint",&genpoint);
  tree->Branch("HitPoint1",&ptrhits1);
  tree->Branch("HitPoint2",&ptrhits2);

  
  Generator *gen = new Generator(4,0.1,53,1);
  
  Propagator *prop = Propagator::Instance();
  prop->PrintStatus();
  

  TClonesArray* ptrparts = new TClonesArray("Particle",100);
  TClonesArray& parts = *ptrparts;

  
  for (int j=0; j<100000; j++){
    Point genp;
    //cout << "Event " << j << endl;
    ptrparts->Clear("C");
    gen->SimulateEvent(parts);
    //gen->GetGenerationPoint().PrintStatus();
    //mult=gen->GetMult(); Da Implementare
    mult=2;
    genpoint=gen->GetGenerationPoint();
    int m1=0, m2=0;
    ptrhits1->Clear("C");
    ptrhits2->Clear("C");

    for(int i=0; i<parts.GetEntries();i++){
      Point hit0,hit1,hit2;
      
      //cout<<"Particle " << i << endl;
      
      Particle* a= (Particle*) ptrparts->At(i);  
      //a->PrintStatus();
      if(prop->Propagate(*a,hit0,0)){
	prop->MultipleScatter(*a);
	//a->PrintStatus();
      }
      
      if(prop->Propagate(*a,hit1,1)){
	prop->GaussianSmearing(hit1,0.03,0.12,1);
	new(hits1[m1]) Point(hit1.fX,hit1.fY,hit1.fZ);

	//new(hits1[m1]) Point(hit1);
	m1++;
	prop->MultipleScatter(*a);
	//a->PrintStatus();
      }
      
      if(prop->Propagate(*a,hit2,2)){
	prop->GaussianSmearing(hit2,0.03,0.12,2);
	new(hits2[m2]) Point(hit2.fX,hit2.fY,hit2.fZ);
	m2++;
	//a->PrintStatus();
      }   
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
