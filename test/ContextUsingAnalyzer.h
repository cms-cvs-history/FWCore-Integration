#ifndef FWCORE_FWCOREINTEGRATION_CONTEXTUSINGANALYZER_H
#define FWCORE_FWCOREINTEGRATION_CONTEXTUSINGANALYZER_H

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SealKernel/Context.h"


// ------------------------------------------------------------ 

// We will create an analysis module (an EDAnalyzer) which contains an
// algorithm object of type OuterAlg; OuterAlg will contain an
// algorithm object of type InnerAlg.

// These algorithm objects will not be passed the data they need in
// order to do their work. Instead, those data will be hidden inside
// the Context.

class InnerAlg {
 public:
  InnerAlg(const edm::ParameterSet& ps, seal::Context* common);
  void doWork(); // note lack of arguments

 private:
  double        myParam_;
  seal::Context context_;
};

class OuterAlg {
 public:
  OuterAlg(const edm::ParameterSet& ps, seal::Context* common);
  void doWork(); // note lack of arguments

 private:
  int           threshold_;
  seal::Context context_;
  InnerAlg      inner_;
};


class ContextUsingAnalyzer : public edm::EDAnalyzer 
{
 public:
  explicit ContextUsingAnalyzer( const edm::ParameterSet& );
  ~ContextUsingAnalyzer();
  
  virtual void analyze( const edm::Event&, const  edm::EventSetup& );

 private:
  
  seal::Context context_;
  
};

#endif
