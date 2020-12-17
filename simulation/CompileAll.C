void CompileAll(TString myopt="fast"){
  TString opt;
  if(myopt.Contains("force")){
    opt = "kfg";
  }
  else {
    opt = "kg";
  }
 
  gSystem->CompileMacro("Point.cxx",opt.Data());
  gSystem->CompileMacro("Particle.cxx",opt.Data());
  gSystem->CompileMacro("Generator.cxx",opt.Data());
  gSystem->CompileMacro("Propagator.cxx",opt.Data());
  gSystem->CompileMacro("Vertexer.cxx",opt.Data());
  gSystem->CompileMacro("LRec.cxx",opt.Data());
  gSystem->CompileMacro("Const.h",opt.Data());
  gSystem->CompileMacro("Simulation.C",opt.Data());
  gSystem->CompileMacro("Reconstruction.C",opt.Data());
  gSystem->CompileMacro("Analysis.C",opt.Data());
  gSystem->CompileMacro("CompleteSimulation.C",opt.Data());
}
