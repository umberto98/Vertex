#include <Riostream.h>
#include <TClonesArray.h>
#include <TTree.h>
#include <TFile.h>
#include <TBranch.h>
#include <TH1F.h>
#include "Point.h"
#include "Particle.h"
#include "Generator.h"
#include "Propagator.h"
#include <TRandom3.h>
#include <TMath.h>
//da togliere alla fine
#include <TCanvas.h>

const int nEV = 1000000;
const bool DISTR = false;
const bool mSCAT = true;
const bool SMEAR = true;
const double XYSMEAR = 0.03;
const double ZSMEAR = 0.12;
const double etaRANGE = 2.;
const int BEAMPIPE = 0;
const int LAYER1 = 1;
const int LAYER2 = 2;

TH1F* maniphist(double range);

double TestSim(){
  
  //TH1F *thetahisto = new TH1F("thetahisto","Variazione direzione multiple scatter",1000,-0.01,0.01);
  //TH1F *phiris = new TH1F("phiris","resolution in phi",1000,-0.01,0.01);
  TH1F *multout1 = new TH1F("multout1","perdita di particelle layer1", 41,-0.5,40.5);
  TH1F *multout2 = new TH1F("multout2","perdita di particelle layer2", 41,-0.5,40.5);

  
  gRandom->SetSeed(1);
  //inizializzo il Generator
  if(DISTR){
    TH1F *disteta = maniphist(etaRANGE);
    TFile F("kinem.root");
    TH1F *distmult = (TH1F*)F.Get("hmul");
    distmult->SetDirectory(0);
    F.Close();
    Generator *gen = Generator::InstanceG(0.1,53.,distmult,disteta); 
  }

  Generator *gen = Generator::InstanceG(0.1,53.,2.,15);
  gen->PrintStatus();
  //inizializzo il propagator
  Propagator *prop = Propagator::Instance();
  prop->PrintStatus();
 

  //Creo un vettore di particelle
  TClonesArray* ptrparts = new TClonesArray("Particle",100);
  TClonesArray& parts = *ptrparts;

  Point genpoint;
  int mult;
  int l=0;
  /////simulazione////////
  int fivepercent =(nEV-1)/20;
  cout << "inizio la simulazione ";
  for (int ev=0; ev<nEV; ev++){   
    if(ev != 0 && ev % fivepercent == 0) cout  << " - "<< 100 * ev/nEV << "%" ; 
    parts.Clear("C");
    gen->SimulateEvent(parts);
    mult=gen->GetMult();
    genpoint=gen->GetGenerationPoint();
    
    //cout << "Event " << ev << endl;
    //gen->GetGenerationPoint().PrintStatus();

    int m1=0, m2=0;
    for(int p=0; p<parts.GetEntries();p++){
      //double theta0=0,theta1=0,theta2=0;
      double phi1=0,phi2=0;
      int temp=false;
      Point hit0,hit1,hit2;
      Particle* part = (Particle*) ptrparts->At(p);  
      //theta0=part->GetPhi();
      //cout<<"Particle " << p << endl;
      //part->PrintStatus();
      
      if(prop->Propagate(*part,hit0,BEAMPIPE))
	if(mSCAT)
	  prop->MultipleScatter(*part);     
      //part->PrintStatus();
      //theta1=part->GetTheta();
      
      if(prop->Propagate(*part,hit1,LAYER1)){
	if(mSCAT)
	  prop->MultipleScatter(*part);
	if(SMEAR)
	  prop->GaussianSmearing(hit1,XYSMEAR,ZSMEAR,LAYER1);	
	m1++;
	//phi1=hit1.GetPhi();
	//temp=true;
	//theta2=part->GetPhi();
      }
      //part->PrintStatus();

      /*
      if(theta1!=0)
	thetahisto->Fill(theta1-theta0);
      if(theta1!=0 && theta2!=0)
	thetahisto->Fill(theta2-theta1);
      */
      if(prop->Propagate(*part,hit2,LAYER2)){
	if(SMEAR)
	  prop->GaussianSmearing(hit2,XYSMEAR,ZSMEAR,LAYER2);
	m2++;

	/*
	phi2=hit2.GetPhi();
	if(temp){
	  double dphi=phi2-phi1;
	  if(dphi>6)
	    dphi-=2*TMath::ACos(-1);
	  if(dphi<-6)
	    dphi+=2*TMath::ACos(-1);
	  phiris->Fill(dphi);
	  }
	*/
	//Test per vedere se i punti sono allineati
	/*
	double ab[3], bc[3], cd[3];
	ab[0]=genpoint.fX-hit0.fX;
	ab[1]=genpoint.fY-hit0.fY;
	ab[2]=genpoint.fZ-hit0.fZ;
	bc[0]=hit0.fX-hit1.fX;
	bc[1]=hit0.fY-hit1.fY;
	bc[2]=hit0.fZ-hit1.fZ;
	cd[0]=hit1.fX-hit2.fX;
	cd[1]=hit1.fY-hit2.fY;
	cd[2]=hit1.fZ-hit2.fZ;
	
	for(int i=0;i<3;i++){
	  cout << ab[i]/bc[i] <<"  " <<  bc[i]/cd[i] <<endl;
	}
	*/
      }
      
      
      //part->PrintStatus();
     
      // cout << "\n --- \n";
    }
    multout1->Fill(mult-m1);
    multout2->Fill(mult-m2);
    //cout << "\n \\-------------------------------------\\ \n";   
  }
  /*
  TCanvas *c1 = new TCanvas("c1","c1",800,1000);
  phiris->SetMinimum(0);
  phiris->Draw("histo");
  */
  TCanvas *c2 = new TCanvas("c2","c2",800,1000);
  multout1->SetMinimum(0);
  multout2->SetLineColor(kRed);
  multout1->Draw("histo");
  multout2->Draw("histosame");

  
  //distruggo generator e propagator
  gen->Destroy();
  prop->Destroy();

  // Close and write file.
  
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
