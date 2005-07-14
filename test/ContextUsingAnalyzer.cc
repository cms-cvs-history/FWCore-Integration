#include "FWCore/Integration/test/ContextUsingAnalyzer.h"

#include "SealKernel/ComponentWrapper.h"

typedef seal::ComponentWrapper<const edm::Event> EventWrapper;

InnerAlg::InnerAlg(const edm::ParameterSet& ps, seal::Context* common) :
  myParam_(ps.getParameter<double>("myParam")),
  context_(common)
{ }

void
InnerAlg::doWork()
{
  // get the hidden products here, and do work with them.
}


// Note that when we contsruct the inner algorithm, we have to pass
// along its parameter set, and a pointer to *our* context... I think.
OuterAlg::OuterAlg(const edm::ParameterSet& ps, seal::Context* common) :
  threshold_(ps.getParameter<int>("threshold")),
  context_(common),
  inner_(ps.getParameter<edm::ParameterSet>("inner"), &context_)
{ }

void
OuterAlg::doWork()
{
  // get the hidden products here, and do work with them.
}
	    


ContextUsingAnalyzer::ContextUsingAnalyzer( const  edm::ParameterSet& iConfig ) : 
  context_()
{ }


ContextUsingAnalyzer::~ContextUsingAnalyzer()
{ }


void
ContextUsingAnalyzer::analyze( const edm::Event& iEvent, const  edm::EventSetup& iSetup )
{
   using namespace edm;

   //create the wrapper that will hold our Event
   //  Note the 'magic' word "event"
   new EventWrapper(&iEvent, &context_,"event");
}

DEFINE_FWK_MODULE(ContextUsingAnalyzer)
