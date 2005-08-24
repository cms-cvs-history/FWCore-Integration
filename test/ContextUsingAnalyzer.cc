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
  if(!ew)
    {
      cout << "InnerAlg: no event found" << endl;
      return;
    }
  const edm::Event* e = *ew;

  seal::Handle<IntWrapper> iw = context_.component<IntWrapper>("iprod");
  if(!iw)
    {
      cout << "InnerAlg: no event found" << endl;
      return;
    }
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

  // IMPORTANT: note that we must check if the thing we looked for is found
  // or we will be operating on a null point!
  if(!ew)
    {
      cout << "OuterAlg: no event found" << endl;
      return;
    }
  const edm::Event* e = *ew;

  seal::Handle<IntWrapper> iw = context_.component<IntWrapper>("iprod");
  if(!iw)
    {
      cout << "OuterAlg: no iprod found" << endl;
      return;
    }
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
ContextUsingAnalyzer::analyze( const edm::Event& iEvent, const  edm::EventSetup& /*iSetup*/ )
{
   using namespace edm;

   edm::Handle<edmtest::IntProduct> ih;
   iEvent.getByLabel("iprod",ih);

   // JBK - important note
   // These wrapper object linger around until replaced.
   // Using this method of managing the context (a data member)
   // means that there are objects in the context with invalid
   // pointers after the event goes away at the end of the 
   // event loop.  An alternative is to create a Context on the
   // stack and add it to the data member parent (the parent
   // may hold job-duration objects).

   // the following is not easy to deal with.  The searches go from
   // child to parent and the Outer/Inner algos know about the parent
   // they would need to find this child Context first.
   //
   // seal::Context local_one(&context_);

   //create the wrapper that will hold our Event
   //  Note the 'magic' word "event"

   new EventWrapper(&iEvent, &context_,"event");
   new IntWrapper(ih.product(),&context_,"iprod");

   alg_.doWork();

   // we should clear the context here of any event related products
   // to prevent them from sticking around too long if the event
   // related products go into the data member context.
   context_.erase( seal::ContextKey::find("event") );
   context_.erase( seal::ContextKey::find("iprod") );

   // it seems to me that the Context facility is better suited
   // for long term state related object and is not very good
   // for limited lifetime objects.
}

DEFINE_FWK_MODULE(ContextUsingAnalyzer)
