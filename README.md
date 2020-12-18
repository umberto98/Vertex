# Vertex
Progetto per il corso di Tecniche di Analisi Numerica e Simulazione
Il programma simula il prodotto di una collisione ad alta energia con alcune approssimazioni e la successiva ricostruzione del vertice.

Per compilare digitare da linea di comando di root:
root [0] .x CompileAll.C
Il file .C si occupa di compilare tutte le macro e le classi necessarie.

Dopo aver compilato si può procedere con l'avvio della simulazione completa:
root [1] CompleteSimulation();
Questa funzione lancia la simulazione, poi procede in automatico con la ricostruzione e termina con l'analisi.

È anche possibile eseguire i singoli passaggi:
root [1] Simulation();
root [2] Reconstruction();
root [3] Analysis();
Essi lavorano indipendentemente e comunicano attraverso 2 file che contengono un TTRee.

Simulation(seed,"nomefiledioutput") -> genera un file .root con all'interno un TTree contenente informazioni sull'evento simulato: molteplicità, punto di generazione, punti di hitpoint sui layer
Reconstruction("nomefilediinput","nomefiledioutput") -> deve prendere in input il file generato da Simulation() e produce un altro file con un TTree contenente informazioni: molteplicità, coordinata z del vertice reale e del vertice ricostruito 
Analysis("nomefilediinput","nomefiledioutput") -> deve prendere in input il file generato da Reconstruction() e produce un file contenente gli istogrammi ottenuti dall'analisi


I nomi sono settati a valori di default, così come tutte le altre variabili della simulazione. Possono essere tutti cambiati dal file Const.h
Dopo aver cambiato qualche parametro nel file Const.h è necessario ricompilare il codice.


Il programma include 5 macro .C :
-CompileAll.C
-CompleteSimulation.C
-Simulation.C
-Reconstruction.C
-Analysis.C

Le macro utilizzano le seguenti classi implementate nei rispettivi file .cxx :
-Point.h
-Particle.h
-Generator.h
-Propagator.h
-LRec.h
-Vertexer.h

Tutte le variabili della simulazione sono inizializzate nel file:
-Const.h

Vengono anche inclusi nel codice due file .root in cui sono salvate le distribuzioni in eta e molteplicità:
-kinem.root
-mult.root (molteplicità uniforme)

##
Luca Aglietta, Umberto Follo