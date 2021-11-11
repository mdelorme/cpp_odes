#pragma once

#include "../Params.h"
#include "../models/Model_base.h"

namespace ODEs {

class Solver_base {
  protected:
  Model_base* model;

  std::string name;

  public:
    Solver_base()  = default;
    virtual ~Solver_base() = default;

    virtual void init(const Params &p) = 0;
    virtual void evolve(real_t dh)     = 0;
    
    inline 
    void update_in_place(DataMap &vars, DataMap &derivatives, real_t dh) {
      for (auto& [k, v] : vars)
        v += dh * derivatives[k];
    }

    inline
    DataMap update(DataMap &vars, DataMap &derivatives, real_t dh) {
      DataMap res;
      for (auto [k, v] : vars)
        res[k] = v + dh * derivatives[k];
      return res;
    }

    inline
    void update_vector_in_place(DataMap  &vars, 
                                DataVec   derivatives, 
                                ScalarVec weights,
                                real_t    dh) {
      size_t nsteps = derivatives.size();

      for (int i=0; i < nsteps; ++i) {
        for (auto& [k, v] : vars)
          v += dh * weights[i] * derivatives[i][k];
      }
    }

    std::string get_name() { return name; };
    DataMap&    get_vars() { return model->get_vars(); };

    void        set_name(std::string  _name)  { name = _name; };
    void        set_model(Model_base* _model) { model = _model; };
};
}