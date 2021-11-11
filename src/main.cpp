#include "solvers/Solver_factory.h"
#include "models/Model_factory.h"
#include "Params.h"

using namespace ODEs;

void write_vars(std::ofstream &f_out, real_t time, DataMap &vars) {
  f_out << time << " ";
  for (auto [k, v] : vars)
    f_out << v << " ";
  f_out << std::endl;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "ERROR : No param file given." << std::endl;
    std::cerr << "USAGE : " << argv[0] << " FILENAME" << std::endl;
    return 1;
  }

  Params params(argv[1]);

  Model_base* model = Model_factory::instantiate(params.model_name);
  std::cout << "Solving model " << model->get_name() << std::endl;
  model->init(params);

  Solver_base* solver = Solver_factory::instantiate(params.solver_name);
  solver->set_model(model);
  std::cout << "Solving model with solver : " << solver->get_name() << std::endl;

  real_t t=0.0;

  std::ofstream f_out;
  std::cout << "Saving outputs in " << params.file_out << std::endl;
  f_out.open(params.file_out);

  auto vars = solver->get_vars();
  write_vars(f_out, t, vars);

  std::cout << "Temporal loop : " << std::endl;
  while (t < params.tmax) {
    int pct = t / params.tmax * 100.0;
    std::cout << "\r" << pct << "% done";
    solver->evolve(params.dt);
    vars = solver->get_vars();
    t += params.dt;
    write_vars(f_out, t, vars);
  }
  std::cout << "\r100 % done" << std::endl;
  f_out.close();

  std::cout << "ALL good !" << std::endl;

  return 0;
}