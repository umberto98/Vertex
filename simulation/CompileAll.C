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
  gSystem->CompileMacro("Generation.C",opt.Data());
}
