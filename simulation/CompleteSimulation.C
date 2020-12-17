#include <TROOT.h>

void CompleteSimulation(){
  gROOT->ProcessLine("Simulation()");
  gROOT->ProcessLine("Reconstruction()");
  gROOT->ProcessLine("Analysis()");
}
