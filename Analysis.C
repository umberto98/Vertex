#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TH1.h>
#include <Riostream.h>
#include <TFile.h>
#include <TTree.h>
#include "Point.h"

void Analysis(){

	//Apertura Tree ------------------------------------------
	int mult;
	double zrec, ztrue;

	TFile f("reconstruction.root");
	TTree *tree = (TTree*)f.Get("trec");

	TBranch *b1=tree->GetBranch("VertMult");
	TBranch *b2=tree->GetBranch("ZRec");
	TBranch *b3=tree->GetBranch("ZTrue");

	b1->SetAddress(&mult);
	b2->SetAddress(&zrec);
	b3->SetAddress(&ztrue);

	//dichiarazione istogrammi e grafici ----------------------
	TH1F* hrestot= new TH1F("zrestot", "Residuals z_{true}-z_{rec}",200,-1000,1000);
	hrestot->SetDirectory(0);
	hrestot->GetXaxis()->SetTitle("z_{rec}-z_{true} [#mum]");
	hrestot->GetYaxis()->SetTitle("counts");
	TH1F* halltot= new TH1F("halltot", "istogramma di supporto",200,-1000,1000);
	halltot->SetDirectory(0);
	
	const int nmultbins=12;
	const int multlims[nmultbins+1]={2,3,4,5,7,9,13,17,20,25,30,40,55};
	const int nzbins=12;
	const double zlims[nzbins+1]={-175,-150,-100,-75,-50,-25,0,25,50,75,100,150,175};
	TH1F* hresmult[nmultbins];
	TH1F* hallmult[nmultbins];
	for (int imult=0; imult<nmultbins; imult++){
		hresmult[imult]=new TH1F(Form("hzremult_multbin%d",imult),Form(" Residuals for event with multiplicity between %d and %d",multlims[imult],multlims[imult+1]-1),200,-1000,1000);
		hresmult[imult]->SetDirectory(0);
		hresmult[imult]->GetXaxis()->SetTitle("z_{rec}-z_{true} [#mum]");
	  hresmult[imult]->GetYaxis()->SetTitle("counts");
		hallmult[imult]=new TH1F(Form("hallmult_multbin%d",imult),"istogramma di supporto",200,-1000,1000);
		hallmult[imult]->SetDirectory(0);
	}
	TH1F* hresz[nmultbins];
	TH1F* hallz[nmultbins];
   for (int iz=0; iz<nzbins; iz++){
		hresz[iz]=new TH1F(Form("hzrez_zbin%d",iz),Form(" Residuals for event with z between %g and %g",zlims[iz],zlims[iz+1]),200,-1000,1000);
		hresz[iz]->SetDirectory(0);
		hresz[iz]->GetXaxis()->SetTitle("z_{rec}-z_{true} [#mum]");
	  hresz[iz]->GetYaxis()->SetTitle("counts");
		hallz[iz]=new TH1F(Form("hallz_zbin%d",iz),"istogramma di supporto",200,-1000,1000);
		hallz[iz]->SetDirectory(0);
	}
	TGraphErrors* geffvsmult;
	TGraphErrors* gresvsmult;
	TGraphErrors* geffvsz;
	TGraphErrors* gresvsz;
	
	//loop su entries del tree---------------------------------
	for (int ev=0; ev<tree->GetEntriesFast(); ev++){
		tree->GetEvent(ev);
		int jMultBin=-1;
		int jZBin=-1;
    for(int imult=0; imult<nmultbins; imult++){
      if(mult>=multlims[imult] && mult<multlims[imult+1]){
				jMultBin=imult;
				break;
      }
    }
    for(int iz=0; iz<nzbins; iz++){
      if(ztrue>=zlims[iz] && ztrue<zlims[iz+1]){
				jZBin=iz;
				break;
      }
    }
    double res=zrec-ztrue;
    if (zrec<=999998 || zrec>=1000000){ 
    	hrestot->Fill(1000*res);
			if(jMultBin>=0 && jMultBin<nmultbins)
	      hresmult[jMultBin]->Fill(1000*res);
		  if(jZBin>=0 && jZBin<nzbins)
			    hresz[jZBin]->Fill(1000*res);
    }
    halltot->Fill(1000*res);
  	if(jMultBin>=0 && jMultBin<nmultbins)
      hallmult[jMultBin]->Fill(1000*res);
    if(jZBin>=0 && jZBin<nzbins)
      hallz[jZBin]->Fill(1000*res);  
	  
	}
	//Grafici RES e EFF vs MULT-------------------------------------------------------------
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
		res[i]=hresmult[i]->GetRMS(1);
		sres[i]=hresmult[i]->GetRMSError(1);
		if (hresmult[i]->GetEntries()!=0)
		eff[i]=hresmult[i]->GetEntries()/hallmult[i]->GetEntries();
		seff[i]=pow(eff[i]*(1-eff[i])/hallmult[i]->GetEntries(),0.5);
		
  }
  geffvsmult=new TGraphErrors(nmultbins,multbincentre,eff,multbinwidth,seff);
  geffvsmult->SetTitle("efficiency vs multiplicity");
  geffvsmult->GetXaxis()->SetTitle("multiplicity");
  geffvsmult->GetYaxis()->SetTitle("efficiency");
  gresvsmult=new TGraphErrors(nmultbins,multbincentre,res,multbinwidth,sres);
  gresvsmult->SetTitle("resolution vs multiplicity");
  gresvsmult->GetXaxis()->SetTitle("multiplicity");
  gresvsmult->GetYaxis()->SetTitle("resolution [#mum]");

  TCanvas* crestot=new TCanvas("crestot","Residulas distibtions",200,100,900,720);
	hrestot->Draw();

  TCanvas* c[nmultbins];
  for(Int_t i=0; i<nmultbins; i++){
    c[i]=new TCanvas(Form("cmult%d",i), "Distribuzione scarti posizione",200,10,900,720);
    hresmult[i]->Draw();
  }
  
  TCanvas* ceffvsmult=new TCanvas("ceffvsmult","efficiency vs multiplicity",200,100,900,720);
	geffvsmult->Draw("AP");
	
  TCanvas* cresvsmult=new TCanvas("cresvsmult","resolution vs multiplicity",200,100,900,720);
	gresvsmult->Draw("AP");


  double zbincentre[nzbins];
	double zbinwidth[nzbins];
	double effz[nzbins];
	double seffz[nzbins];
	double resz[nzbins];
	double sresz[nzbins];
	
  for (int i=0; i<nzbins; i++){
  	zbincentre[i]=(zlims[i]+zlims[i+1])/2;
  	zbinwidth[i]=(double) (zlims[i+1]-zlims[i])/2;
		double avg;
		resz[i]=hresz[i]->GetRMS();
		sresz[i]=hresz[i]->GetRMSError();
		effz[i]=hresz[i]->GetEntries()/hallz[i]->GetEntries();
		seffz[i]=pow(effz[i]*(1-effz[i])/hallz[i]->GetEntries(),0.5);
		
  }
  geffvsz=new TGraphErrors(nzbins,zbincentre,effz,zbinwidth,seffz);
  geffvsz->SetTitle("efficiency vs z");
  geffvsz->GetXaxis()->SetTitle("z_{true} [mm]");
  geffvsz->GetYaxis()->SetTitle("efficiency");
  gresvsz=new TGraphErrors(nzbins,zbincentre,resz,zbinwidth,sresz);
  gresvsz->SetTitle("resolution vs z");
  gresvsz->GetXaxis()->SetTitle("z_{true} [mm]");
  gresvsz->GetYaxis()->SetTitle("resolution [#mum]");
 
  TCanvas* cz[nzbins];
  for(Int_t i=0; i<nzbins; i++){
    cz[i]=new TCanvas(Form("cz%d",i), "Distribuzione scarti posizione",200,10,900,720);
    hresz[i]->Draw();
  }
  
  TCanvas* ceffvsz=new TCanvas("ceffvsz","efficiency vs z",200,100,900,720);
	geffvsz->Draw("AP");
	
  TCanvas* cresvsz=new TCanvas("cresvsz","resolution vs z",200,100,900,720);
	gresvsz->Draw("AP");
}	
