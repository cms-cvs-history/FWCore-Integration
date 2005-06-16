#ifndef EDMREFTEST_OTHERTHING_H
#define EDMREFTEST_OTHERTHING_H

#include "FWCore/EDProduct/interface/Ref.h"
#include "FWCore/EDProduct/interface/RefVector.h"

namespace edmreftest {

  class ThingCollection;

  struct OtherThing {
    virtual ~OtherThing() {}
    OtherThing():a(), ref(), refVec() { }
    int a;
    edm::Ref<ThingCollection> ref;
    edm::RefVector<ThingCollection> refVec;
  };
}

#endif
