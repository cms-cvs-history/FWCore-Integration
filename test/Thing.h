#ifndef EDMREFTEST_THING_H
#define EDMREFTEST_THING_H
#include <vector>

namespace edmreftest {

  struct Thing {
    ~Thing() { }
    Thing():a() { }
    int a;
  };

}

#endif
