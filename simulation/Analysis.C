#include <TSystem.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TH1.h>
#include <Riostream.h>
#include <TDirectory.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include "Const.h"
#include "Point.h"

void Analysis(const char* titlein=gTITLER,const char* titleout=gTITLEG){

  //Apertura Tree ------------------------------------------------------------------------------

  if(gSystem->AccessPathName(titlein)){
    cout << titlein << " file not found." << "\n";
    exit(1);
  }
  TFile f(titlein);
   
  // Check if TTree exists inside ROOT file
  if( !f.GetListOfKeys()->Contains("treerec") ){
    cout << "TTree treerec not found inside " << titlein << "\n";
    exit(1);
  }
  TTree *treerec = (TTree*)f.Get("treerec");

  int mult;
  double zrec, ztrue;
  TBranch *b1=treerec->GetBranch("VertMult");
  TBranch *b2=treerec->GetBranch("ZRec");
  TBranch *b3=treerec->GetBranch("ZTrue");

  b1->SetAddress(&mult);
  b2->SetAddress(&zrec);
  b3->SetAddress(&ztrue);

  TFile hfile(titleout,"RECREATE");
  TDirectory* subD0 = hfile.mkdir("Histoaux");
  TDirectory* subD1 = hfile.mkdir("Histo");
  subD0->cd();
  
  
  //dichiarazione istogrammi e grafici -----------------------------------------------------------
  TH1F* hrestot= new TH1F("zrestot", "Residuals z_{true}-z_{rec}",100,-1000,1000);
  hrestot->SetDirectory(0);
  hrestot->GetXaxis()->SetTitle("z_{rec}-z_{true} [#mum]");
  hrestot->GetYaxis()->SetTitle("counts");

  TH1F* halltot= new TH1F("halltot", "istogramma di supporto",100,-1000,1000);
  //halltot->SetDirectory(0);

  // bin di molteplicità
  const int nmultbins=20;
  const double multlims[nmultbins+1]={0.5,1.5,2.5,3.5,4.5,5.5,7.5,9.5,11.5,14.5,17.5,21.5,25.5,30.5,35.5,40.5,45.5,52.5,60.5,70.5,80.5};

  //bin di zeta
  const int nzbins=24;
  const double zlims[nzbins+1]={-310.,-280.,-250,-210.,-180.,-165.,-149.,-119.,-100.,-80.,-50.,-25.,0.,25.,50.,80.,100.,119.,149.,165.,180.,210.,250.,280.,310.};

  //setto a quanto voglio tagliare le z del vertice

  
  //vettore di histo per residui in funzione di mult e ausiliario
  TH1F* hresmult[nmultbins];
  TH1F* hallmult[nmultbins];
  //inizializzo i vari grafici per i residui fissata la mult
  for (int imult=0; imult<nmultbins; imult++){
    hresmult[imult]=new TH1F(Form("hzremult_multbin%d",imult),Form("Residuals for event with multiplicity between %d and %d",
								   (int) (multlims[imult]+0.5),
								   (int) (multlims[imult+1]-1+0.5)),100,-1000,1000);
    //hresmult[imult]->SetDirectory(0);
    hresmult[imult]->GetXaxis()->SetTitle("z_{rec}-z_{true} [#mum]");
    hresmult[imult]->GetYaxis()->SetTitle("counts");

    hallmult[imult]=new TH1F(Form("hallmult_multbin%d",imult),"istogramma di supporto",100,-1000,1000);
    //hallmult[imult]->SetDirectory(0);
  }

  //vettore di histo per i residui in funzione di z e ausiliario
  TH1F* hresz[nzbins];
  TH1F* hallz[nzbins];
  //inizializzo i vari grafici per i residui fissato z
  for (int iz=0; iz<nzbins; iz++){
    hresz[iz]=new TH1F(Form("hzrez_zbin%d",iz),Form("Residuals for event with z between %g and %g",zlims[iz],zlims[iz+1]),100,-1000,1000);
    //hresz[iz]->SetDirectory(0);
    hresz[iz]->GetXaxis()->SetTitle("z_{rec}-z_{true} [#mum]");
    hresz[iz]->GetYaxis()->SetTitle("counts");

    hallz[iz]=new TH1F(Form("hallz_zbin%d",iz),"istogramma di supporto",100,-1000,1000);
    //hallz[iz]->SetDirectory(0);
  }

  //errori per i vari grafici
  TGraphErrors* geffvsmult;
  TGraphErrors* gresvsmult;
  TGraphErrors* geffvsz;
  TGraphErrors* gresvsz;


  
  //loop su entries del tree--------------------------------------------------------------------------------
  for (int ev=0; ev<treerec->GetEntriesFast(); ev++){
    treerec->GetEvent(ev);
    int jMultBin=-1;
    int jZBin=-1;
    //trovo l'intervallo a cui appartiene la mult dell'evento
    for(int imult=0; imult<nmultbins; imult++){
      if(mult>=multlims[imult] && mult<multlims[imult+1]){
	jMultBin=imult;
	break;
      }
    }
    //trovo l'intervallo a cui appartiene la z dell'evento
    for(int iz=0; iz<nzbins; iz++){
      if(ztrue>=zlims[iz] && ztrue<zlims[iz+1]){
	jZBin=iz;
	break;
      }
    }
    
    double res=zrec-ztrue;
    if (zrec<=999998 || zrec>=1000000){         //mi valuta se l'evento è stato ricostruito-> entro nell'if
      hrestot->Fill(1000*res);
      if(jMultBin>=0 && jMultBin<nmultbins)    //controllo che il bin a cui appartiene sia uno di quelli che ho impostato
	if(TMath::Abs(ztrue)<gNSIGMA*gZRMS)                      //controllo che la z sia in n sigma
	  hresmult[jMultBin]->Fill(1000*res);
      if(jZBin>=0 && jZBin<nzbins)             //controllo che il bin a cui appartiene sia uno di quelli che ho impostato
	if(TMath::Abs(ztrue)<gNSIGMA*gZRMS)                      //controllo che la z sia in n sigma
	hresz[jZBin]->Fill(1000*res);
    }

    //salvo ora tutti gli eventi in histo ausiliari, anche quelli non ricostruiti per calcolare poi l'efficienza
    halltot->Fill(1000*res);
    if(jMultBin>=0 && jMultBin<nmultbins)
      if(TMath::Abs(ztrue)<gNSIGMA*gZRMS)
	hallmult[jMultBin]->Fill(1000*res);
    if(jZBin>=0 && jZBin<nzbins)
      if(TMath::Abs(ztrue)<gNSIGMA*gZRMS)
	hallz[jZBin]->Fill(1000*res);
    
  }

  
  //Grafici RES e EFF vs MULT--------------------------------------------------------------------------------------------------
  //instanzio i centri dei bin, la larghezza, la risoluzione e l'efficienza in funzione della MOLTEPLICITÀ
  double multbincentre[nmultbins];
  double multbinwidth[nmultbins];
  double eff[nmultbins];
  double seff[nmultbins];
  double res[nmultbins];
  double sres[nmultbins];

 
  for (int i=0; i<nmultbins; i++){
    multbincentre[i]=(multlims[i]+multlims[i+1])/2;
    multbinwidth[i]=(double) (multlims[i+1]-multlims[i])/2;
    double avg;
    
    if(hresmult[i]->GetEntries()!=0){
      res[i]=hresmult[i]->GetRMS(1);
      sres[i]=hresmult[i]->GetRMSError(1);
      eff[i]=hresmult[i]->GetEntries()/hallmult[i]->GetEntries();
      seff[i]=pow(eff[i]*(1-eff[i])/hallmult[i]->GetEntries(),0.5);
    }else{
      res[i]=-1;
      sres[i]=-1;
      eff[i]=-1;
      seff[i]=-1;
    }
    
  }

  //grafico con errore dell'efficienza vs molteplicità
  geffvsmult=new TGraphErrors(nmultbins,multbincentre,eff,multbinwidth,seff);
  int j=0;
  for(int i=0; i<nmultbins; i++)
    if(eff[i]<0){
      geffvsmult->RemovePoint(i-j);
      j++;
    }
  geffvsmult->SetTitle("efficiency vs multiplicity");
  geffvsmult->GetXaxis()->SetTitle("multiplicity");
  geffvsmult->GetYaxis()->SetTitle("efficiency");
  //grafico con errori di risoluzione vs molteplicità
  gresvsmult=new TGraphErrors(nmultbins,multbincentre,res,multbinwidth,sres);
  j=0;
  for(int i=0; i<nmultbins; i++)
    if(res[i]<0){
      gresvsmult->RemovePoint(i-j);
      j++;
    }
  gresvsmult->SetTitle("resolution vs multiplicity");
  gresvsmult->GetXaxis()->SetTitle("multiplicity");
  gresvsmult->GetYaxis()->SetTitle("resolution [#mum]");


  //instanzio i centri dei bin, la larghezza, la risoluzione e l'efficienza in funzione della zeta del vertice
  double *zbincentre=new double[nzbins];
  double *zbinwidth=new double[nzbins];
  double *effz=new double[nzbins];
  double *seffz=new double[nzbins];
  double *resz=new double[nzbins];
  double *sresz=new double[nzbins];
	
  for (int i=0; i<nzbins; i++){
    zbincentre[i]=(zlims[i]+zlims[i+1])/2;
    zbinwidth[i]=(double) (zlims[i+1]-zlims[i])/2;
    double avg;
    
    if(hresz[i]->GetEntries()!=0){
      resz[i]=hresz[i]->GetRMS();
      sresz[i]=hresz[i]->GetRMSError();
      effz[i]=hresz[i]->GetEntries()/hallz[i]->GetEntries();
      seffz[i]=pow(effz[i]*(1-effz[i])/hallz[i]->GetEntries(),0.5);
    }else{
      resz[i]=-1;
      sresz[i]=-1;
      effz[i]=-1;
      seffz[i]=-1;
    }
  }

  //grafico con errore dell'efficienza vs zeta vertice
  geffvsz=new TGraphErrors(nzbins,zbincentre,effz,zbinwidth,seffz);
  j=0;
  for(int i=0; i<nzbins; i++)
    if(effz[i]<0){
      geffvsz->RemovePoint(i-j);
      j++;
    }
  geffvsz->SetTitle("efficiency vs z");
  geffvsz->GetXaxis()->SetTitle("z_{true} [mm]");
  geffvsz->GetYaxis()->SetTitle("efficiency");
  //grafico con errori di risoluzione vs zeta vertice
  gresvsz=new TGraphErrors(nzbins,zbincentre,resz,zbinwidth,sresz);
  j=0;
  for(int i=0; i<nzbins; i++)
    if(resz[i]<0){
      gresvsz->RemovePoint(i-j);
      j++;
    }
  gresvsz->SetTitle("resolution vs z");
  gresvsz->GetXaxis()->SetTitle("z_{true} [mm]");
  gresvsz->GetYaxis()->SetTitle("resolution [#mum]");

  
  //disegno i grafici-------------------------------------------------------------------------------
  TCanvas* crestot=new TCanvas("crestot","Residulas distribtions",200,100,900,720);
  hrestot->Draw();
  
  TCanvas* ceffvsmult=new TCanvas("ceffvsmult","efficiency vs multiplicity",200,100,900,720);
  geffvsmult->Draw("AP");

  TCanvas* cresvsmult=new TCanvas("cresvsmult","resolution vs multiplicity",200,100,900,720);
  gresvsmult->Draw("AP");

  TCanvas* ceffvsz=new TCanvas("ceffvsz","efficiency vs z",200,100,900,720);
  geffvsz->Draw("AP");
  
  TCanvas* cresvsz=new TCanvas("cresvsz","resolution vs z",200,100,900,720);
  gresvsz->Draw("AP");

  /*
  TCanvas* c[nmultbins];
  for(Int_t i=0; i<nmultbins; i++){
    c[i]=new TCanvas(Form("cmult%d",i), "Distribuzione scarti posizione",200,10,900,720);
    hresmult[i]->Draw();
  }
  
  TCanvas* cz[nzbins];
  for(Int_t i=0; i<nzbins; i++){
    cz[i]=new TCanvas(Form("cz%d",i), "Distribuzione scarti posizione",200,10,900,720);
    hresz[i]->Draw();
  }
  */

  //chiudo i file e salvo gli histo su un file root

  hfile.Write();
  subD1->cd();
  hrestot->Write();
  geffvsmult->Write();
  gresvsmult->Write();
  geffvsz->Write();
  gresvsz->Write();
  
  hfile.Close();
  f.Close();
}	
