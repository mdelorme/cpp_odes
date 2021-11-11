#pragma once

#include "Solver_base.h"

namespace ODEs {

class Solver_euler : public Solver_base {
public:
  virtual ~Solver_euler() = default;

  virtual void init(const Params &p) {};

  virtual void evolve(real_t dh) {
    DataMap& vars    = model->get_vars();
    auto derivatives = model->compute_derivatives(vars);
    update_in_place(vars, derivatives, dh);
  }
};

}