#include <stdexcept>

using std::runtime_error;

#include "Jug.h"

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA)
    : capacityA_(Ca),
      capacityB_(Cb),
      n_(N),
      cfA_(cfA),
      cfB_(cfB),
      ceA_(ceA),
      ceB_(ceB),
      cpAB_(cpAB),
      cpBA_(cpBA)
{
}

int Jug::solve(string &solution) const
{
    bool validCosts = (cfA_ > 0) && 
                      (cfB_ > 0) && 
                      (ceA_ > 0) && 
                      (ceB_ > 0) && 
                      (cpAB_ > 0) && 
                      (cpBA_ > 0);
    bool validCapacities = (0 < capacityA_ && capacityA_ <= capacityB_) && 
                           (n_ <= capacityB_ && capacityB_ <= 1000);

    if (!validCosts && !validCapacities) return -1;

    throw runtime_error("finish solve");
}