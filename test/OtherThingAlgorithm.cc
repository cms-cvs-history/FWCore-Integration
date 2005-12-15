#include "FWCore/Integration/test/OtherThingAlgorithm.h"
#include "FWCore/Integration/test/OtherThing.h"
#include "FWCore/Integration/test/OtherThingCollection.h"
#include "FWCore/Integration/test/ThingCollection.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Handle.h"

namespace edmreftest {
  void OtherThingAlgorithm::run(const edm::Event &e, OtherThingCollection & otherThingCollection) {
    edm::Handle<ThingCollection> things;
    e.getByLabel("Thing", things);
    for (int i = 0; i < 20; ++i) {
      OtherThing tc;
      tc.a = i;
      tc.refProd = edm::RefProd<ThingCollection>(things);
      tc.ref = edm::Ref<ThingCollection>(things, i);
      tc.refVec.push_back(tc.ref);
      tc.refVec.push_back(edm::Ref<ThingCollection>(things, 19-i));
      otherThingCollection.push_back(tc);
    }
  }
}
