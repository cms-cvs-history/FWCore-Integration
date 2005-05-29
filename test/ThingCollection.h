#ifndef EDMREFTEST_THINGCOLLECTION_H
#define EDMREFTEST_THINGCOLLECTION_H

#include "FWCore/EDProduct/interface/EDCollection.h"
#include "FWCore/FWCoreIntegration/test/Thing.h" 

namespace edmreftest {
  struct ThingCollection : public edm::EDCollection<Thing> {
    ThingCollection () : edm::EDCollection<Thing>() {}
    virtual ~ThingCollection() {}
  };
}

#endif

