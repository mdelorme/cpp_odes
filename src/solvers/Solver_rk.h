#pragma once

#include "Solver_base.h"

namespace ODEs {

class Solver_rk : public Solver_base {
private:
  int order;
public:
  virtual ~Solver_rk() = default;

  virtual void init(const Params &p) {
    order = p.reader.GetInteger("solver", "order", 2);
    std::set<int> valid_orders {2, 3, 4};
    if (valid_orders.count(order) == 0) {
      std::cerr << "ERROR : Runge-Kutta method not implemented/valid for order " << order << std::endl;
      std::cerr << "        Setting order=2" << std::endl;
      order = 2;
    }
  }

  void evolve_rk2(real_t dh) {
    DataMap &vars = model->get_vars();

    // 1st step
    auto derivatives = model->compute_derivatives(vars);
    DataMap tmp_vars = update(vars, derivatives, 0.5*dh);

    // 2nd step
    derivatives = model->compute_derivatives(tmp_vars);
    update_in_place(vars, derivatives, dh);
  } 

  void evolve_rk4(real_t dh) {
    DataMap &vars = model->get_vars();

    DataMap tmp_k;
    std::vector<DataMap> ks;
    std::vector<real_t> w {1.0/6.0, 1.0/3.0, 1.0/3.0, 1.0/6.0};

    tmp_k = model->compute_derivatives(vars);
    DataMap vk1 = update(vars, tmp_k, 0.5*dh);
    ks.push_back(tmp_k);

    tmp_k = model->compute_derivatives(vk1);
    DataMap vk2 = update(vars, tmp_k, 0.5*dh);
    ks.push_back(tmp_k);

    tmp_k = model->compute_derivatives(vk2);
    DataMap vk3 = update(vars, tmp_k, dh); 
    ks.push_back(tmp_k);

    tmp_k = model->compute_derivatives(vk3);
    ks.push_back(tmp_k);

    update_vector_in_place(vars, ks, w, dh);
  }

  virtual void evolve(real_t dh) {
    if (order == 2)
      evolve_rk2(dh);
    else if (order == 4)
      evolve_rk4(dh);
  }
};

}