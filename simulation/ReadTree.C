#include <Riostream.h>
#include <TMath.h>
#include <TClonesArray.h>
#include <TTree.h>
#include <TFile.h>
#include <TBranch.h>
#include <TString.h>
#include "Point.h"
#include <TCanvas.h>
#include <TH1D.h>

void ReadTree(){
  if(gSystem->AccessPathName("htree.root")){
    cout << "titleRoot1" << " file not found." << "\n";
    exit(1);
  }
  TFile* f1 = new TFile("htree.root");

   
  // Check if TTree exists inside ROOT file
  if( !f1->GetListOfKeys()->Contains("T") ){
    cout << "TTree " << "T" << " not found inside " << "htree.root" << "\n";
    exit(1);
  }
  TTree* t1 = (TTree*)f1->Get("T");
  cout<<1;

  int ev = t1->GetEntries();
  int mult = 0;
  t1->SetBranchAddress("VertMult", &mult);
  Point *genpoint;
  t1->SetBranchAddress("GenPoint", &genpoint);
  TClonesArray* hits1 = new TClonesArray("Point",100);
  TClonesArray* hits2 = new TClonesArray("Point",100);
  
  t1->SetBranchAddress("HitPoint1", &hits1);
  
  t1->SetBranchAddress("HitPoint2", &hits2);

  TH1D* rdistr1 = new TH1D("rdistr1","Distribuzione r layer 1",100,1000.,2000.);  
  TH1D* rdistr2 = new TH1D("rdistr1","Distribuzione r layer 1",100,4000.,5000.);
      int fivepercent = ceil(float(ev-1)/20);

  for(int n=0; n<ev; n++){
  if(n != 0 && n % fivepercent == 0) cout << endl << 100 * float(n)/ev << " %" ; 
    t1->GetEntry(n);
    //cout<<"Evento "<< n <<"; Molteplicita= "<<mult<<endl;
    int num1=hits1->GetEntries();
    //cout<<"Numero di hits1 "<<num1<<endl;
    for(int i=0;i<num1;i++){     
      Point *tst=(Point*)hits1->At(i);
      //tst->PrintStatus();
      double r = tst->fX*tst->fX+tst->fY*tst->fY;
      rdistr1->Fill(r);
    }
    int num2=hits2->GetEntries();
    //cout<<"Numero di hits2 "<<num2<<endl;
    for(int i=0;i<num2;i++){     
      Point *tst=(Point*)hits2->At(i);
      //tst->PrintStatus();
      double r = tst->fX*tst->fX+tst->fY*tst->fY;
      rdistr2->Fill(r);
    }
    
  }
  
  
  TCanvas* c1 = new TCanvas("c1","c1",800,600);
  rdistr1->Draw("hist");
  

  TCanvas* c2 = new TCanvas("c2","c2",800,600);
  rdistr2->Draw("hist");
  
  f1->Close();
}
