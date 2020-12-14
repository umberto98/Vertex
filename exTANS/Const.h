#ifndef CONST_H  
#define CONST_H



//Struttura simulation->Variabili globali necessarie nel Simulation.C

const int gNEV {1000000};		//Inizializza il numero di eventi della simulazione
const int gDISTR {1};			//Inizializza la distribuzione in molteplicità:"0" fissa, "1" distribuzione assegnata, "2" distribuzione uniforme
const bool gMSCAT {true};		//"true" scattering multiplo acceso,"false" scattering multiple spento
const double gETARANGE{2.};		//Range in cui viene estretto eta(es se "2." allora -2.<eta<2.)
const int gBEAMPIPE {0};		//Da non modificare, per comodità si associa alla beam pipe valore 0
const int gLAYER1 {1};			//Da non modificare, per comodità si associa al primo layer valore 1
const int gLAYER2 {2};			//Da non modificare, per comodità si associa al secondo layer valore 2


//Struttura Generator->Variabili globali con cui si instanzia la classe Generator.h

const double gXYRMS {0.1};		//RMS di x e y del punto di generazione dell'evento (in mm)
const double gZRMS {53.};		//RMS di z del punto di generazione dell'evento (in mm)
const int gMULT {15};			//Nel caso gDISTR=0 (molteplicità fissa), è la molteplicità dell'evento


//Struttura Propagator->Variabili globali con cui si instanzia la classe Propagator.h

const double gRBP {30.};		//Raggio della beam pipe (in mm)
const double gRL1 {40.};		//Raggio del primo layer (in mm)
const double gRL2 {70.};		//Raggio del secondo layer (in mm)
const double gLENL1 {270.};		//Lunghezza totale del primo layer (in mm)
const double gLENL2 {270.};		//Lunghezza totale del secondo layer (in mm)
const double gDEPBP {0.8};		//Spessore della beam pipe (in mm)->non implementato
const double gDEPL1 {0.2};		//Spessore primo layer (in mm)->non implementato

//____________________________________________________________________________________________


//Struttura ...->Variabili globali che servono per la classe di ricostruzione...

const bool gSMEAR {true};		//"true" smearing acceso, "false" smearing spento
const bool gNOISE {true};		//"true" aggiunta di punti spuri, "false" non vengono aggiunti punti spuri
const int gNS {10};			//Quantità di punti spuri aggiunti


//Struttura smearing->Variabili globali che servono per la classe Smearing.h

const double gRPHISM {0.03};		//RMS [mm] in direzione rphi dello smearing (gaussiano)
const double gZSM {0.12};		//RMS [mm] in direzione z dello smearing (gaussiano)


//Struttura Vertexer->Variabili globali che servono per la classe Vertexer.h

const double gPHISTEP {0.003};		//Intervallo entro il quale ,preso un hit sul primo layer, il vertexer va a ricercare un hit sul secondo per ricostruire una traccia [rad]
const double gZSTEP {5};		      //Binning dell'istogramma usato per la ricostruzione della z del vertice di interazione 


#endif  
