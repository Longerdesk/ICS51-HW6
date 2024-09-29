#include "CSVReader.hpp"
#include "IGWriter.hpp"
#include "InterferenceGraph.hpp"
#include "catch_amalgamated.hpp"
#include <string>

namespace {


using namespace RA;

static const std::string &GRAPH_DIR = "tests/graphs/";
//static const std::string &GRAPH_DIR = std::string("");
/*
    TEST_CASE("SimpleAddEdge", "[NonRequiredIG]") {
        InterferenceGraph<std::string> ig;
        ig.addVertex("domino");
        ig.addVertex("banana");
        ig.addVertex("egg");
        ig.addVertex("chocolate");
        ig.addVertex("apple");
        ig.addEdge("apple", "banana");
        ig.addEdge("chocolate", "domino");
        ig.addEdge("banana", "chocolate");
        ig.addEdge("apple", "chocolate");
        ig.addEdge("apple", "egg");
        ig.addEdge("chocolate", "egg");
        ig.addEdge("egg", "banana");
    
        ig.removeVertex("banana");

        //ig.removeEdge("banana", "chocolate");
        REQUIRE(ig.numVertices() == 4);
        REQUIRE(ig.numEdges() == 4);
        //REQUIRE(ig.interferes("apple", "chocolate") == true);
        //REQUIRE(ig.degree("chocolate") == 3);
        //ig.neighbors("chocolate");
        
    }*/
    /*
    TEST_CASE("RuntimeTest", "[ig-complete_1000]") {
        const auto &GRAPH = GRAPH_DIR + "complete_1000.csv";
        InterferenceGraph<Variable> ig = CSVReader::load(GRAPH);
        REQUIRE(ig.numVertices() == 1000);
    }*/
/*
    TEST_CASE("SimpleAddEdgesAndVertices", "[RequiredIG]") {
        const auto &GRAPH = GRAPH_DIR + "simple.csv";
    ///autograder/git-repo/student-execution-files/tests/
        const InterferenceGraph<Variable> &ig = CSVReader::load(GRAPH);

        REQUIRE(ig.numEdges() == 3);
        REQUIRE(ig.numVertices() == 3);
    }
    TEST_CASE("Neighbors", "[RequiredIG]") {
        const auto &GRAPH = GRAPH_DIR + "simple.csv";

        const InterferenceGraph<Variable> &ig = CSVReader::load(GRAPH);
        const std::unordered_set<Variable> &expected_neighbors = {"y", "z"};

        REQUIRE(ig.neighbors("x") == expected_neighbors);
    }*/
}