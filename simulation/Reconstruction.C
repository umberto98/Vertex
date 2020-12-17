#include <TSystem.h>
#include <Riostream.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TClonesArray.h>
#include <TH1F.h>
#include "Const.h"
#include "Point.h"
#include "LRec.h"
#include "Vertexer.h"


void Reconstruction(const char* titlein=gTITLES,const char* titleout=gTITLER){

  // Lettura file input contenente TClones array di Point---------------------------------------------------------
  int entry=0, mult=0;
  Point* genpoint= new Point();
  TClonesArray *ptrhits1 = new TClonesArray("Point",200);
  TClonesArray& hits1 =*ptrhits1;			
  TClonesArray *ptrhits2 = new TClonesArray("Point",200);
  TClonesArray& hits2 =*ptrhits2;

  if(gSystem->AccessPathName(titlein)){
    cout << titlein << " file not found." << "\n";
    exit(1);
  }
  TFile hfile(titlein);
   
  // Check if TTree exists inside ROOT file
  if( !hfile.GetListOfKeys()->Contains("treep") ){
    cout << "TTree treep not found inside " << titlein << "\n";
    exit(1);
  }
  TTree *treep = (TTree*)hfile.Get("treep");

  entry=treep->GetEntries();
  TBranch *b1=treep->GetBranch("VertMult");
  TBranch *b2=treep->GetBranch("GenPoint");
  TBranch *b3=treep->GetBranch("HitPoint1");
  TBranch *b4=treep->GetBranch("HitPoint2");


  b1->SetAddress(&mult);
  b2->SetAddress(&genpoint);
  b3->SetAddress(&ptrhits1);
  b4->SetAddress(&ptrhits2);

	
  //tree su cui salvare output---------------------------------------------------------
  double zrec, ztrue;
  TFile outfil(titleout,"RECREATE");
  TTree* treerec=new TTree("treerec","TTree ricostruzione");
  treerec->Branch("VertMult",&mult);
  treerec->Branch("ZTrue",&ztrue);
  treerec->Branch("ZRec",&zrec);
  
  //dichiarazioone reconstructor per gaussian smearing e un punto ausiliario------------
  LRec *rec = LRec::Instance();
  if(gSMEAR){
    cout << "\nSmear attivo\n";
    rec->PrintStatus();
  }  
  if(gNOISE)
     cout << "\nNoise attivo, punti di noise aggiunti per ogni evento: " << gNS << "\n\n";
  Point* hit=new Point();
  
  //dichiarazoine vertexer e istogramma usato per ricostruzione------------------------
  Vertexer *vert = Vertexer::Instance();
  vert->PrintStatus();

  TH1F* evzdist=new TH1F("evzdist","istogramma dispersione z0 tracce ricostruite",gHBINREC,-gHRANGEREC,gHRANGEREC);
  //opzioni per la rappresentazione, per farlo bisogna lavorare su un' unica entry del tree
  evzdist->GetXaxis()->SetTitle("z_{0} [mm]");
  evzdist->GetYaxis()->SetTitle("counts");
  	
	
  // loop sugli ingressi nel TTree-----------------------------------------------------
  for (int ev=0; ev<entry; ev++){
    treep->GetEvent(ev);
    int m1=ptrhits1->GetEntries();
    int m2=ptrhits2->GetEntries();
    //Gaussian Smearing
    if(gSMEAR){
      for (int i1=0; i1<m1;i1++){
	hit=(Point*) ptrhits1->At(i1);
	rec->GaussianSmearing(*hit,gLAYER1);
      }
      for (int i2=0; i2<m2;i2++){
	hit=(Point*) ptrhits2->At(i2);
	rec->GaussianSmearing(*hit,gLAYER2);
      }
    }
    if(gNOISE){
      Point p1(0,0,0);
      for(int n=m1;n<m1+gNS;n++){
	rec->NoisePoint(p1,gLAYER1);
	new(hits1[n]) Point(p1);
      }
      for(int n=m2;n<m2+gNS;n++){
	rec->NoisePoint(p1,gLAYER2);
	new(hits2[n]) Point(p1);
      }
    }
    zrec=vert->FindVertexZ(ptrhits1,ptrhits2,evzdist);
    ztrue=genpoint->fZ;
    treerec->Fill();
  }
  treerec->Write();

  rec->Destroy();
  vert->Destroy();
  
  outfil.Close();
  hfile.Close();
}	
	


