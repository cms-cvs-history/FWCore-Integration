#ifndef Integration_OtherThing_h
#define Integration_OtherThing_h

#include "FWCore/EDProduct/interface/Ref.h"
#include "FWCore/EDProduct/interface/RefVector.h"
#include <vector>

namespace edmreftest {

  class Thing;
  typedef std::vector<Thing> ThingCollection;

  struct OtherThing {
    ~OtherThing() {}
    OtherThing():a(), ref(), refVec() { }
    int a;
    edm::Ref<ThingCollection> ref;
    edm::RefVector<ThingCollection> refVec;
  };
}

#endif
