#pragma once

#include "Solver_base.h"

namespace ODEs {

class Solver_euler : public Solver_base {
public:
  virtual ~Solver_euler() = default;

  virtual void evolve(real_t dh) {
    DataMap& vars    = model->get_vars();
    auto derivatives = model->compute_derivatives(vars);

    for (auto& [k, v]: vars)
      v += dh * derivatives[k];
  }
};

}