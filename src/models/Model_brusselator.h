#pragma once

#include "Model_base.h"

namespace ODEs {

class Model_Brusselator : public Model_base {
private:
  real_t A, B;

public:
  Model_Brusselator() {};

  virtual void init(const Params &p) {
    A = p.reader.GetFloat("model", "A", 1.1);
    B = p.reader.GetFloat("model", "B",  0.4);

    vars["X"] = 1.0;
    vars["Y"] = 1.0;
  }

  virtual DataMap compute_derivatives(DataMap vars) {
    DataMap res;
    real_t x = vars["X"];
    real_t y = vars["Y"];

    res["X"] = A + x*x*y - B*x - x;
    res["Y"] = B*x - x*x*y;

    return res;
  }
};

}