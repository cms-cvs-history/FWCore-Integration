#include "FWCore/Integration/test/ContextUsingAnalyzer.h"
#include "FWCore/Framework/src/ToyProducts.h"

#include "SealKernel/ComponentWrapper.h"

#include <iostream>
using namespace std;

// ---------- use standard seal wrapper class ----------------

// the constness of the event and product are preserved with the
// current wrapper.

typedef seal::ComponentWrapper<const edm::Event> EventWrapper;

typedef edmtest::IntProduct IntType;
typedef seal::ComponentWrapper<const IntType> IntWrapper;


// -------------------------------------------------

InnerAlg::InnerAlg(const edm::ParameterSet& ps, seal::Context* common) :
  myParam_(ps.getParameter<double>("myParam")),
  context_(common)
{ }

void
InnerAlg::doWork()
{
  // get the hidden products here, and do work with them.
  seal::Handle<EventWrapper> ew = context_.component<EventWrapper>("event");
  const edm::Event* e = *ew;
  seal::Handle<IntWrapper> iw = context_.component<IntWrapper>("iprod");
  const IntType* ip = *iw;

  cout << "InnerAlg: Event ID = " << e->id() << endl;
  cout << "InnerAlg: Int value = " << ip->value << endl;
}

// ---------------------------------------------------

// Note that when we contsruct the inner algorithm, we have to pass
// along its parameter set, and a pointer to *our* context... I think.
OuterAlg::OuterAlg(const edm::ParameterSet& ps, seal::Context* common) :
  threshold_(ps.getParameter<int>("threshold")),
  context_(common),
  inner_(ps.getParameter<edm::ParameterSet>("inner"), &context_)
{ }

template <class T>
inline T* doit(const T* t) { return t; }

void
OuterAlg::doWork()
{
  // get the hidden products here, and do work with them.
  seal::Handle<EventWrapper> ew = context_.component<EventWrapper>("event");
  const edm::Event* e = *ew;
  seal::Handle<IntWrapper> iw = context_.component<IntWrapper>("iprod");
  const IntType* ip = *iw;

  cout << "OuterAlg: Event ID = " << e->id() << endl;
  cout << "OuterAlg: Int value = " << ip->value << endl;

  inner_.doWork();
}
	    
// ---------------------------------------------------

ContextUsingAnalyzer::ContextUsingAnalyzer( const  edm::ParameterSet& iConfig ) : 
  context_(),
  alg_(iConfig.getParameter<edm::ParameterSet>("outer"),&context_)
{ }


ContextUsingAnalyzer::~ContextUsingAnalyzer()
{ }


void
ContextUsingAnalyzer::analyze( const edm::Event& iEvent, const  edm::EventSetup& iSetup )
{
   using namespace edm;

   edm::Handle<edmtest::IntProduct> ih;
   iEvent.getByLabel("iprod",ih);

   //create the wrapper that will hold our Event
   //  Note the 'magic' word "event"
   new EventWrapper(&iEvent, &context_,"event");
   new IntWrapper(ih.product(),&context_,"iprod");

   alg_.doWork();
}

DEFINE_FWK_MODULE(ContextUsingAnalyzer)
