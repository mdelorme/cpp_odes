#pragma once

#include "Solver_base.h"

namespace ODEs {

class Solver_euler : public Solver_base {
public:
  virtual ~Solver_euler() = default;

  virtual void evolve(real_t dh) {
    real_t dx = dh * (alpha * x - beta*x*y);
    real_t dy = dh * (delta * x * y - gamma*y); 
    x += dx;
    y += dy;
  }
};

}