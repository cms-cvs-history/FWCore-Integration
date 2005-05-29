#ifndef EDMREFTEST_OTHERHTINGCOLLECTION_H
#define EDMREFTEST_OTHERHTINGCOLLECTION_H

#include "FWCore/EDProduct/interface/EDCollection.h"
#include "FWCore/FWCoreIntegration/test/OtherThing.h" 


namespace edmreftest {
  struct OtherThingCollection : public edm::EDCollection<OtherThing> {
    OtherThingCollection () : edm::EDCollection<OtherThing>() {}
    virtual ~OtherThingCollection() {}
  };
}

#endif

