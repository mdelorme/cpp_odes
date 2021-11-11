#pragma once

#include "../Params.h"

namespace ODEs {

class Solver_base {
  protected:
  // Lotka volterra model
  real_t x, y, alpha, beta, delta, gamma;

  std::string name;

  public:
    Solver_base()  = default;
    virtual ~Solver_base() = default;

    void init() {
      x = 10.0;
      y = 10.0;
      alpha = 1.1;
      beta  = 0.4;
      delta = 0.1;
      gamma = 0.4;
    }

    virtual void evolve(real_t dh) = 0;
    std::string get_name() { return name; };
    void set_name(std::string new_name) { name = new_name; };

    std::pair<real_t, real_t> get_model() { return std::pair<real_t, real_t>(x, y); };
};
}