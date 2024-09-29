#include "register_allocation.hpp"
#include "CSVReader.hpp"
#include "InterferenceGraph.hpp"
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <list>

using namespace RA;

// assignRegisters
//
// This is where you implement the register allocation algorithm
// as mentioned in the README. Remember, you must allocate at MOST
// d(G) + 1 registers where d(G) is the maximum degree of the graph G.
// If num_registers is not enough registers to accomodate the passed in
// graph you should return an empty map. You MUST use registers in the
// range [1, num_registers] inclusive.

RegisterAssignment RA::assignRegisters(const std::string &path_to_graph,
                                          int num_registers) noexcept {
  InterferenceGraph<Variable> ig = CSVReader::load(path_to_graph);
  std::unordered_map<std::string, int> registerAssignment;
  std::unordered_set<std::string> vertices = ig.vertices();
  int numVertices = ig.numVertices();
  std::list<std::string> verticesInDegree;
  std::vector<std::string> verticesSort;
  std::set<std::string> interferedSet;
  std::unordered_set<std::string> neighbors;
  auto itr = vertices.begin();

  //std::cout << "num: " << numVertices << std::endl;
  for(int i = 0; i < numVertices; i++){
    verticesSort.push_back(*itr);
    itr++;
  }
  int color = 1;

/*
  std::cout << "vector looks like " << std::endl;
  for(int i = 0; i < numVertices; i++){
    std::cout << verticesInDegree[i] << ", ";
  }
  std::cout << std::endl;*/
  std::list<std::string> nextVertices;

  
  quicksort(ig, verticesSort, 0, numVertices-1);
  
  if((int)ig.degree(verticesSort[verticesSort.size()-1])+1 > num_registers){
    return registerAssignment;
  }

  for(int i = 0; i < numVertices; i++){
    verticesInDegree.push_back(verticesSort[i]);
  }

  while(verticesInDegree.size() != 0 && numVertices > 0){
    while(verticesInDegree.size() != 0 && numVertices > 0){
      std::string name = verticesInDegree.back();//最後の(一番大きい)要素
      if(interferedSet.find(name) == interferedSet.end()){//使えるなら
        registerAssignment[verticesInDegree.back()] = color;//色を割り当てて
        neighbors = ig.neighbors(verticesInDegree.back());//隣り合うやつを調べて
        auto itr2 = neighbors.begin();
        for(; itr2 != neighbors.end(); itr2++){//隣り合うやつ1つ1つを
          interferedSet.insert(*itr2);//使えないリストに入れる
        }
        verticesInDegree.pop_back();//次に行く
        numVertices -= 1;
      }else{//使えないなら
        nextVertices.push_front(verticesInDegree.back());//次回使えるようにしとく
        verticesInDegree.pop_back();
      }
    }
    interferedSet.clear();//使えないリストをリセット
    verticesInDegree = std::move(nextVertices);//次に行く
        //std::cout << "after" << std::endl;

    color += 1;
  }

  std::cout << "------result-------" << std::endl;

  
  
  for (const auto& [key, value] : registerAssignment){
        std::cout << key << " => " << value << "\n";
  }
  return registerAssignment;
}


int partition(InterferenceGraph<std::string> ig, std::vector<std::string> &a, int start, int end)
{
    std::string pivot = a[end];
    int pIndex = start;

    for (int i = start; i < end; i++)
    {
        if (ig.degree(a[i]) <= ig.degree(pivot))
        {
            swapLists(a, i, pIndex);
            pIndex++;
        }
    }

    swapLists(a, pIndex, end);
    return pIndex;
}

void quicksort(InterferenceGraph<std::string> ig, std::vector<std::string> &a, int start, int end)
{
    if (start >= end) {
        return;
    }
    int pivot = partition(ig, a, start, end);
    quicksort(ig, a, start, pivot - 1);
    quicksort(ig, a, pivot + 1, end);
}

void swapLists(std::vector<std::string> &a, int index1, int index2){
  std::string temp;
  temp = a[index1];
  a[index1] = a[index2];
  a[index2] = temp;
}