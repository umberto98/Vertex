#include <Riostream.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include "Point.h"
#include <TMath.h>
#include <TClonesArray.h>
#include <TH1.h>
#include "Vertexer.h"
#include "Reconstruction.h"

void ReadTree(){

  // Lettura file input contenente TClones array di Point---------------------------------------------------------
  TClonesArray *ptrhits1 = new TClonesArray("Point",100);
	TClonesArray& hits1 =*ptrhits1;			
  TClonesArray *ptrhits2 = new TClonesArray("Point",100);
  TClonesArray& hits2 =*ptrhits2;
  Point* genpoint= new Point();
  
  Int_t mult=0;
  TFile hfile("simulation.root");
  TTree *tree = (TTree*)hfile.Get("treep");
  
  TBranch *b1=tree->GetBranch("GenPoint");
  TBranch *b2=tree->GetBranch("HitPoint1");
	TBranch *b3=tree->GetBranch("HitPoint2");
  TBranch *b4=tree->GetBranch("VertMult");
  
  b1->SetAddress(&genpoint);
  b2->SetAddress(&ptrhits1);
	b3->SetAddress(&ptrhits2);
	b4->SetAddress(&mult);
	
	//tree su cui salvare output---------------------------------------------------------
	double zrec, ztrue;
	TFile outfil("reconstruction.root","RECREATE");
	TTree* trec=new TTree("trec","TTree ricostruzione");
	trec->Branch("VertMult",&mult);
  trec->Branch("ZTrue",&ztrue);
  trec->Branch("ZRec",&zrec);
  
  //dichiarazioone reconstructor per gaussian smearing e un punto ausiliario------------
  Reconstruction *rec = Reconstruction::Instance();
  Point* hit=new Point();
  
	//dichiarazoine vertexer e istogramma usato per ricostruzione------------------------
	Vertexer *vert = Vertexer::Instance(gPHISTEP, gZSTEP);
	TH1F* evzdist=new TH1F("evzdist","istogramma dispersione z0 tracce ricostruite",100,-250,250);
  	//opzioni per la rappresentazione, per farlo bisogna lavorare su un' unica entry del tree
  	evzdist->GetXaxis()->SetTitle("z_{0} [mm]");
  	evzdist->GetYaxis()->SetTitle("counts");
  	
	
  // loop sugli ingressi nel TTree-----------------------------------------------------
	for (int ev=3; ev<4; ev++){
		tree->GetEvent(ev);
		int m1=ptrhits1->GetEntries();
		int m2=ptrhits2->GetEntries();
		//Gaussian Smearing
		for (int i1=0; i1<m1;i1++){
			hit=(Point*) ptrhits1->At(i1);
			rec->GaussianSmearing(*hit,1);
		}
		for (int i2=0; i2<m2;i2++){
			hit=(Point*) ptrhits2->At(i2);
			rec->GaussianSmearing(*hit,2);
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
		trec->Fill();
	}
  trec->Write();
  outfil.Close();
}	
	


