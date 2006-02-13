#ifndef Integration_OtherThingAlgorithm_h
#define Integration_OtherThingAlgorithm_h

#include "DataFormats/TestObjects/interface/OtherThingCollectionfwd.h"

namespace edm {
  class Event;
}
  
namespace edmtest {

  class OtherThingAlgorithm {
  public:
    OtherThingAlgorithm() : theDebugLevel(0) {}
  
    /// Runs the algorithm and returns a list of OtherThings
    /// The user declares the vector and calls this method.
    void run(const edm::Event & e, OtherThingCollection& otherThingCollection);
  
  private:
    int    theDebugLevel;
  };

}
  
#endif
