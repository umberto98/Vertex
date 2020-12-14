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

void TestGen(){ 

  //TH1D *teta = new TH1D("teta","prova",1000,1/100*TMath::ACos(-1),1/100*TMath::ACos(-1));
  TFile F("kinem.root");
  TH1F *disteta = maniphist();
  TH1F *distmult = (TH1F*)F.Get("hmul");
  Generator *gen = new Generator(10,0.1,53,2);
  
  Propagator *prop = Propagator::Instance();
  prop->PrintStatus();
  

  TClonesArray* ptrparts = new TClonesArray("Particle",100);
  TClonesArray& parts = *ptrparts;
  Point hit0,hit1,hit2,genp;

  
  for (int j=0; j<10; j++){
    //cout << "Event " << j << endl;
    //mult=Prova.RndmMult();
    ptrparts->Clear("C");
    gen->SimulateEvent(parts);
    //gen->GetGenerationPoint().PrintStatus();
    genp=gen->GetGenerationPoint();
    for(int i=0; i<parts.GetEntries();i++){
      cout<<"Particle " << i << endl;
      Particle* a= (Particle*) ptrparts->At(i);
      
      a->PrintStatus();
      double ang = a->GetPhi();
      hit0=prop->Propagate(*a,0);
      
      a->PrintStatus();

      //prop->MultipleScatter(*a);
      hit1=prop->Propagate(*a,1);
      a->PrintStatus();	
      //prop->MultipleScatter(*a);
      hit2=prop->Propagate(*a,2);
      a->PrintStatus();
      

      double ang1 = a->GetPhi();
      //teta->Fill(ang1-ang);
      if(ang1-ang < -1.){
	hit0.PrintStatus();
	hit1.PrintStatus();
	hit2.PrintStatus();
      }
	
        double ab[3], bc[3], cd[3];
      ab[0]=genp.fX-hit0.fX;
      ab[1]=genp.fY-hit0.fY;
      ab[2]=genp.fZ-hit0.fZ;
      bc[0]=hit0.fX-hit1.fX;
      bc[1]=hit0.fY-hit1.fY;
      bc[2]=hit0.fZ-hit1.fZ;
      cd[0]=hit1.fX-hit2.fX;
      cd[1]=hit1.fY-hit2.fY;
      cd[2]=hit1.fZ-hit2.fZ;
      
      
      //cout << a->GetTheta()<< endl;
      for(int i=0;i<3;i++){
	cout << ab[i]/bc[i] <<"  " <<  bc[i]/cd[i] <<endl;
      }
      
      
      cout << "\n \n";
    }
    cout << "\n \\-------------------------------------\\ \n";

  }
  delete gen;
  prop->Destroy();
  cout << "ho finito";
  //TCanvas *c1 = new TCanvas("c1","c1",800,1000);
  //teta->SetMinimum(0);
  //teta->Draw("histo");
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

/*
  UInt_t mult = 0;
  t->SetBranchAddress("Nparticles", &Nparticles);
  vector<Double_t>* particlePositionX = NULL;
  t->SetBranchAddress("particlePositionX", &particlePositionX);
  vector<Double_t>* particlePositionY = NULL;
  t->SetBranchAddress("particlePositionY", &particlePositionY);
  vector<Double_t>* particlePositionZ = NULL;
  t->SetBranchAddress("particlePositionZ", &particlePositionZ);
*/
