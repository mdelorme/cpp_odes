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

    virtual void evolve(real_t dh) = 0;
    
    std::string get_name() { return name; };
    DataMap&    get_vars() { return model->get_vars(); };

    void        set_name(std::string  _name)  { name = _name; };
    void        set_model(Model_base* _model) { model = _model; };
};
}