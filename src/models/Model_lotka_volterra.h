#pragma once

#include "Model_base.h"

namespace ODEs {

class Model_LotkaVolterra : public Model_base {
private:
  real_t alpha, beta, delta, gamma;

  std::ofstream f_out;

public:
  Model_LotkaVolterra() {};

  virtual void init(const Params &p) {
    alpha = p.reader.GetFloat("model", "alpha", 1.1);
    beta  = p.reader.GetFloat("model", "beta",  0.4);
    delta = p.reader.GetFloat("model", "delta", 0.1);
    gamma = p.reader.GetFloat("model", "gamma", 0.4);

    vars["X"] = p.reader.GetFloat("model", "x0", 10.0);
    vars["Y"] = p.reader.GetFloat("model", "y0", 10.0);

    f_out.open(p.file_out);
  }

  virtual DataMap compute_derivatives(DataMap vars) {
    DataMap res;
    real_t x = vars["X"];
    real_t y = vars["Y"];

    res["X"] = alpha*x - beta*x*y;
    res["Y"] = delta*x*y - beta*y;

    return res;
  }

  virtual void save_data(std::string prefix, int iteration, real_t time, bool first) {
    std::ofstream f_out;
    f_out << time << " " << vars["X"] << " " << vars["Y"] << std::endl;
  }

  virtual void finalize() {
    f_out.close();
  }
};

}