#ifndef VERTEXER_H
#define VERTEXER_H

#include <TObject.h>
#include <Riostream.h>
#include "Particle.h"
#include "Point.h"
#include <TH1F.h>
#include <TClonesArray.h>

class Vertexer : public TObject {

	public:
	
	static Vertexer* Instance(const double phistep=0.005, const double zstep=5);
	static void Destroy();

	double FindVertexZ(TClonesArray* hits1, TClonesArray* hits2, TH1F* evzdist);
	TH1F* GetZDist();
	private:
	
	double fZStep;
	double fPhiStep;
	
	double FindTrackZ(Point* hit1, Point* hit2);
	Vertexer(const double phistep, const double zstep);
	Vertexer(const Vertexer& rec);
  Vertexer& operator=(const Vertexer source);
	virtual ~Vertexer();
	
  static Vertexer* fgInstance;
	
  ClassDef(Vertexer,2)
	};
	#endif
	
	
	
