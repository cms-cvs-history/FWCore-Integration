#ifndef Integration_OtherThing_h
#define Integration_OtherThing_h

#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefVector.h"
#include "DataFormats/Common/interface/RefProd.h"
#include "FWCore/Integration/test/ThingCollectionfwd.h"

namespace edmreftest {

  struct OtherThing {
    ~OtherThing() {}
    OtherThing():a(), ref(), refVec() { }
    int a;
    edm::RefProd<ThingCollection> refProd;
    edm::Ref<ThingCollection> ref;
    edm::RefVector<ThingCollection> refVec;
  };
}

#endif
