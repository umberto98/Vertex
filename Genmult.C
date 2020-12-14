#include <TH1F.h>
#include <Riostream.h>
#include <TFile.h>
void Genmult(){
  
  TFile hfile("mult.root","RECREATE");

  TH1F *hmulun = new TH1F("hmulun","Molteplicità uniforme",82,-0.5,81.5);

  for(int i=1;i<81;i++){
    hmulun->Fill(i,1);
  }
  hfile.Write();
  hfile.Close();
}
