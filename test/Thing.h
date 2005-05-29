#ifndef EDMREFTEST_THING_H
#define EDMREFTEST_THING_H

namespace edmreftest {

  struct Thing {
    virtual ~Thing() { }
    Thing():a() { }
    int a;
  };

}

#endif
