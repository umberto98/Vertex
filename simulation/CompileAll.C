void CompileAll(TString myopt="fast"){
  TString opt;
  if(myopt.Contains("force")){
    opt = "kfg";
  }
  else {
    opt = "kg";
  }
  gSystem->CompileMacro("Const.h",opt.Data());
  gSystem->CompileMacro("Point.cxx",opt.Data());
  gSystem->CompileMacro("Particle.cxx",opt.Data());
  gSystem->CompileMacro("Generator.cxx",opt.Data());
  gSystem->CompileMacro("Propagator.cxx",opt.Data());
  gSystem->CompileMacro("Reconstruction.cxx",opt.Data());
  gSystem->CompileMacro("Simulation.C",opt.Data());
  //gSystem->CompileMacro("TestSim.C",opt.Data());
  //gSystem->CompileMacro("ReadTree.C",opt.Data());	
}
