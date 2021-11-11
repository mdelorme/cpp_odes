#pragma once

#include "../Params.h"
#include "Model_base.h"
#include "Model_lotka_volterra.h"
#include "Model_brusselator.h"

namespace ODEs {

#define REGISTER_MODEL(classname, class) if(name == #classname) {Model_base* res = new class; res->set_name(#classname); return res;}

class Model_factory {
public: 
  static Model_base* instantiate(std::string name) {
    REGISTER_MODEL(lotka_volterra, Model_LotkaVolterra)
    REGISTER_MODEL(brusselator,    Model_Brusselator)

    std::cerr << "ERROR : No model named " << name << std::endl;
    std::cerr << "        Using lotka-volterra instead" << std::endl;
    return new Model_LotkaVolterra;
  }
};

}