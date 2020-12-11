#include <Riostream.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include "Point.h"
#include <TMath.h>
#include <TClonesArray.h>

void ReadTree(){

  // Dichiarazione TClonesArray
  TClonesArray *hits = new TClonesArray("Point",100);
  //Apertura file di input
  TFile hfile("simulation.root");
  //Lettura TTree  e branch
  TTree *tree = (TTree*)hfile.Get("treep");
  //TBranch *b1=tree->GetBranch("VertMult");
  TBranch *b2=tree->GetBranch("HitPoint1");

  // Definizione degli indirizzi per la lettura dei dati su ttree
  //b1->SetAddress(&point.X);
  b2->SetAddress(&hits);

  // loop sugli ingressi nel TTree
  for(int ev=0;ev<tree->GetEntries();ev++){
    tree->GetEvent(ev);
    //cout<<"Evento "<<ev<<"; Molteplicita= "<<point.mult<<endl;
    //cout<<"X,Y,Z = "<<point.X<<"; "<<point.Y<<"; "<<point.Z<<endl;
    int num=hits->GetEntries();
    cout<<"Numero di elementi nel TClonesArray "<<num<<endl;
    for (int j=0; j<num; j++){
      Point *tst=(Point*)hits->At(j);
      //cout<<"Punto "<<j<<") x, y, z = "<<tst->fX<<"; "<<tst->fY<<"; "<<tst->fZ<<endl;
    }
  }
 
}
