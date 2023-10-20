#include "find_similar_files.hpp"
#include "dist.hpp"

#include <iostream>

#include <argparse/argparse.hpp>

int main(int argc, char *argv[]) {
  argparse::ArgumentParser program("binary comp");

  program.add_argument("firstDir")
    .help("first input directory");

  program.add_argument("secondDir")
    .help("second input directory");

  program.add_argument("border")
    .help("second input directory")
    .default_value(70)
    .scan<'i', int>();

  try {
    program.parse_args(argc, argv);
  }
  catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  std::string firstDir = program.get<std::string>("firstDir");
  std::string secondDir = program.get<std::string>("secondDir");
  int border = program.get<int>("border");

  FindSimilarFiles(firstDir, secondDir, border);
  
}