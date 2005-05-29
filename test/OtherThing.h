#ifndef EDMREFTEST_OTHERTHING_H
#define EDMREFTEST_OTHERTHING_H

#include "FWCore/EDProduct/interface/Ref.h"

namespace edmreftest {

  class ThingCollection;

  struct OtherThing {
    virtual ~OtherThing() {}
    OtherThing():a(), ref() { }
    int a;
    edm::Ref<ThingCollection> ref;
  };
}

#endif
