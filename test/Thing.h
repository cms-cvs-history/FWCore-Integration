#ifndef Integration_Thing_h
#define Integration_Thing_h
#include <vector>

namespace edmreftest {

  struct Thing {
    ~Thing() { }
    Thing():a() { }
    int a;
  };

}

#endif
