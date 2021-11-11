#pragma once

#include <bits/stdc++.h>
#include "../external/inih/INIReader.h"

using real_t = double;
using DataMap = std::map<std::string, real_t>;

namespace ODEs {

class Params {
public:
  INIReader reader;

  std::string solver_name;
  std::string model_name;

  std::string file_out;
  real_t tmax;
  real_t dt;

  Params(std::string filename) : reader(filename) {
    solver_name = reader.Get("run", "solver", "euler");
    model_name  = reader.Get("model", "model", "lotka_volterra");
    file_out    = reader.Get("run", "output_filename", "ode.dat");
    tmax        = reader.GetFloat("run", "tmax", 10.0);
    dt          = reader.GetFloat("run", "dt", 0.1);
  }
};

}