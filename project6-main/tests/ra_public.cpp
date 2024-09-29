#include "CSVReader.hpp"
#include "IGWriter.hpp"
#include "InterferenceGraph.hpp"
#include "catch_amalgamated.hpp"
#include "register_allocation.hpp"
#include "verifier.hpp"

namespace {

using namespace RA;

static const std::string &GRAPH_DIR = "tests/graphs/";

TEST_CASE("SimpleMiddleSuccess", "[NonRequiredRA]") {
  // Load the graph pointed to by simple.csv
  const auto &GRAPH = GRAPH_DIR + "simplemiddle.csv";
  const auto NUM_REGS = 8;

  // Provide 3 registers to the register allocation algorithm.
  // Note, the highest degree in this graph is two, so all three
  // will be needed.
  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);

  IGWriter::write(CSVReader::load(GRAPH), GRAPH_DIR + "simplemiddle.dot",
                  allocation);
  REQUIRE((verifyAllocation(GRAPH, NUM_REGS, allocation)));
}
/*
TEST_CASE("SimpleSuccess", "[RequiredRA]") {
  // Load the graph pointed to by simple.csv
  const auto &GRAPH = GRAPH_DIR + "simple.csv";
  const auto NUM_REGS = 3;

  // Provide 3 registers to the register allocation algorithm.
  // Note, the highest degree in this graph is two, so all three
  // will be needed.
  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  IGWriter::write(CSVReader::load(GRAPH), GRAPH_DIR + "simple_success.dot",
                  allocation);

  REQUIRE((verifyAllocation(GRAPH, NUM_REGS, allocation)));
}

TEST_CASE("SimpleFail", "[RequiredRA]") {
  // Load the graph pointed to by simple.csv
  const auto &GRAPH = GRAPH_DIR + "simple.csv";
  const auto NUM_REGS = 2;

  // Provide 2 registers to the register allocation algorithm.
  // Note, the highest degree in this graph is two, so the allocation
  // cannot be completed.
  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  REQUIRE((allocation.empty()));
}
*/
} // namespace