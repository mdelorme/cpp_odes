#pragma once

#include "Model_base.h"

namespace ODEs {

class Model_Lorenz : public Model_base {
private:
  real_t sigma, rho, beta;

  std::ofstream f_out;

public:
  Model_Lorenz() {};

  virtual void init(const Params &p) {
    sigma = p.reader.GetFloat("model", "sigma", 10.0);
    rho   = p.reader.GetFloat("model", "rho",   28.0);
    beta  = p.reader.GetFloat("model", "beta",  2.666667);

    vars["X"] = p.reader.GetFloat("model", "x0", 10.0);
    vars["Y"] = p.reader.GetFloat("model", "y0", 10.0);
    vars["Z"] = p.reader.GetFloat("model", "z0", 10.0);

    f_out.open(p.file_out);
  }

  virtual DataMap compute_derivatives(DataMap vars) {
    DataMap res;
    real_t x = vars["X"];
    real_t y = vars["Y"];
    real_t z = vars["Z"];

    res["X"] = sigma * (y-x);
    res["Y"] = x*(rho-z) - y;
    res["Z"] = x*y - beta*z;

    return res;
  }

  virtual void save_data(std::string prefix, int iteration, real_t time, bool first) {
    f_out << time << " " << vars["X"] << " " << vars["Y"] << " " << vars["Z"] << std::endl;
  }

  virtual void finalize() {
    f_out.close();
  }
};

}