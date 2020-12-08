#include <Riostream.h>
#include <TMath.h>
#include "Generator.h"
#include <TClonesArray.h>
#include <TTree.h>
#include <TFile.h>
#include <TBranch.h>
#include <TString.h>
#include "Point.h"
#include "Particle.h"

void Prova(){
	Generator G(0,2,0.1,53.,2);
	Point p;
	TClonesArray parts("Particle",2);
	G.SimulateEvent(p,parts);
	Particle* par=(Particle*)parts[1];
	par->PropagateToRadius(100);
	cout<<"controllo conversioni cartesiane e polari"<<endl;
	cout<<"X="<<p.fX<<endl;
	cout<<"Y="<<p.fY<<endl;
	cout<<"Z="<<p.fZ<<endl;
	cout<<"R="<<p.fR<<endl;
	cout<<"Phi="<<p.fPhi<<endl;
	cout<<"controllo propagazione a R=100mm"<<endl;
	cout<<"X1="<<par->GetPoint().fX<<endl;
	cout<<"Y1="<<par->GetPoint().fY<<endl;
	cout<<"Z1="<<par->GetPoint().fZ<<endl;
	cout<<"Theta1="<<par->GetTheta()<<endl;
	cout<<"Phi1="<<par->GetPhi()<<endl;
}			
