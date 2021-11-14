#pragma once

#include "Model_base.h"

namespace ODEs {

class Model_VanDerPol : public Model_base {
private:
  real_t mu;

public:
  Model_VanDerPol() {};

  virtual void init(const Params &p) {
    mu = p.reader.GetFloat("model", "mu", 0.0);

    vars["X"] = p.reader.GetFloat("model", "x0", 1.0);
    vars["Y"] = p.reader.GetFloat("model", "y0", 1.0);
  }

  virtual DataMap compute_derivatives(DataMap vars) {
    DataMap res;
    real_t x = vars["X"];
    real_t y = vars["Y"];

    res["X"] = y;
    res["Y"] = mu*(1.0 - x*x)*y - x;

    return res;
  }
};

}