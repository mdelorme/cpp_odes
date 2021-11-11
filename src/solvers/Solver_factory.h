#pragma once

#include "../Params.h"
#include "Solver_base.h"
#include "Solver_euler.h"

namespace ODEs {

#define REGISTER_SOLVER(classname, class) if(name == #classname) {Solver_base* res = new class; res->set_name(#classname); return res;}

class Solver_factory {
public: 
  static Solver_base* instantiate(std::string name) {
    REGISTER_SOLVER(euler, Solver_euler)

    std::cerr << "ERROR : No solver named " << name << std::endl;
    std::cerr << "        Using euler instead" << std::endl;
    return new Solver_euler;
  }
};

}