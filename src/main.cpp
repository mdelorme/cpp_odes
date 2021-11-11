#include "solvers/Solver_factory.h"
#include "Params.h"

using namespace ODEs;

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "ERROR : No param file given." << std::endl;
    std::cerr << "USAGE : " << argv[0] << " FILENAME" << std::endl;
    return 1;
  }

  Params params(argv[1]);

  Solver_base* solver = Solver_factory::instantiate(params.solver);
  std::cout << "Solving model with solver : " << solver->get_name() << std::endl;

  real_t t=0.0;
  
  solver->init();

  std::ofstream f_out;
  std::cout << "Saving outputs in " << params.file_out << std::endl;
  f_out.open(params.file_out);

  auto res = solver->get_model();
  f_out << t << " " << res.first << " " << res.second << std::endl;

  while (t < params.tmax) {
    int pct = t / params.tmax * 100.0;
    std::cout << "\r" << pct << "% done";
    solver->evolve(params.dt);
    res = solver->get_model();
    f_out << t << " " << res.first << " " << res.second << std::endl;
    t += params.dt;
  }
  std::cout << "\r100 % done" << std::endl;
  f_out.close();

  std::cout << "ALL good !" << std::endl;

  return 0;
}