#pragma once

#include <bits/stdc++.h>
#include "../external/inih/INIReader.h"

using real_t = double;

namespace ODEs {

class Params {
public:
  std::string solver;
  std::string file_out;
  real_t tmax;
  real_t dt;

  Params(std::string filename) {
    INIReader reader(filename);

    solver   = reader.Get("run", "solver_type", "euler");
    file_out = reader.Get("run", "output_filename", "ode.dat");
    tmax     = reader.GetFloat("run", "tmax", 10.0);
    dt       = reader.GetFloat("run", "dt", 0.1);
  }
};

}