#pragma once

#include "../Params.h"

namespace ODEs {

class Model_base {
protected:
  std::string name;

  DataMap vars;

public:
  Model_base() = default;
  virtual ~Model_base() = default;

  virtual void init(const Params &p) = 0;
  virtual DataMap compute_derivatives(DataMap vars) = 0;

  real_t      get_var(std::string var_name) { return vars[var_name]; };
  DataMap&    get_vars()                    { return vars; };
  std::string get_name()                    { return name; };

  void set_name(std::string _name) { name = _name; };
};

}