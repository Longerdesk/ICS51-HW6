#ifndef __INTERFERENCE_GRAPH__HPP
#define __INTERFERENCE_GRAPH__HPP

#include <exception>
#include <string>
#include <unordered_set>
#include <stdexcept>
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

class UnknownVertexException : public std::runtime_error {
public:
  UnknownVertexException(const std::string &v)
      : std::runtime_error("Unknown vertex " + v) {}
};

class UnknownEdgeException : public std::runtime_error {
public:
  UnknownEdgeException(const std::string &v, const std::string &w)
      : std::runtime_error("Unknown edge " + v + " - " + w) {}
};

// InterferenceGraph
//
// This is a class representing an interference graph
// as described in "Part 1: Interference Graph" of the README.md
// file. Though this class is templated, because of the usage of exceptions
// UnknownVertexException and UnknownEdgeException it will
// ONLY be tested with strings.
template <typename T> class InterferenceGraph {
public:
  // Custom type used to represent edges. This is mainly
  // used in the utility function for reading and writing
  // the graph structure to/from files. You don't need to use it.
  using EdgeTy = std::pair<T, T>;

  InterferenceGraph();

  ~InterferenceGraph();

  void addEdge(const T &v, const T &w);

  void addVertex(const T &vertex);

  void removeEdge(const T &v, const T &w);

  void removeVertex(const T &vertex);

  std::unordered_set<T> vertices() const noexcept;

  std::unordered_set<T> neighbors(const T &vertex) const;

  unsigned numVertices() const noexcept;

  unsigned numEdges() const noexcept;

  bool interferes(const T &v, const T &w) const;

  unsigned degree(const T &v) const;
/*
  int partition(int, int);
  
  void quicksort(int, int);

  void swapLists(int, int);*/

  //int findList(const T &v) const;

private:
  std::unordered_set<std::string> verticesSet;
  std::unordered_map<T, std::unordered_set<T>> adjacencyLists;
  int edgeNum;
};

template <typename T> InterferenceGraph<T>::InterferenceGraph() {
  edgeNum = 0;
}

template <typename T> InterferenceGraph<T>::~InterferenceGraph() {

}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::neighbors(const T &vertex) const {
  auto itr = verticesSet.begin();
  for(; itr != verticesSet.end(); itr++){
    if(*itr == vertex){
      break;
    }
  }
  if(itr == verticesSet.end()){
    throw UnknownVertexException(vertex);
  }

  return adjacencyLists.at(vertex);
}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::vertices() const noexcept {
  return verticesSet;
}

template <typename T>
unsigned InterferenceGraph<T>::numVertices() const noexcept {
  return verticesSet.size();
}

template <typename T> unsigned InterferenceGraph<T>::numEdges() const noexcept {
  return edgeNum;
}

template <typename T>
void InterferenceGraph<T>::addEdge(const T &v, const T &w) {
  //std::cout << "try to add edge: " << v << ", " << w << std::endl;
  std::unordered_set<T>* vList = &adjacencyLists.at(v);
  auto itr = vList->find(w);
  if(itr != vList->end()){
    return;
  }
  vList->insert(w);
  std::unordered_set<T>* wList = &adjacencyLists.at(w);
  wList->insert(v);
  edgeNum += 1;

  //int listSize = this->numVertices();
  
  //std::cout << "quicksort with (0, " << listSize << ")" << std::endl;
  //this->quicksort(0, listSize-1);
  
  //std::cout << "success to add edge: " << v << ", " << w << std::endl;
  /*
  std::cout << "graph has now" << std::endl;
  for (const auto& [key, value] : adjacencyLists){
    std::cout << key << ": ";
    auto itr = value.begin();
    for(; itr != value.end(); itr++){
      std::cout << *itr << ", ";
    }
    std::cout << std::endl;
  }*/
}

template <typename T>
void InterferenceGraph<T>::removeEdge(const T &v, const T &w) {
//std::cout << "try to remove " << v << ", " << w << std::endl;
  std::unordered_set<T>* wList = &adjacencyLists.at(w);
  auto itr2 = wList->find(v);
  if(itr2 == wList->end()){
    throw UnknownEdgeException(w, v);
  }else{
    wList->erase(itr2);
  }
  std::unordered_set<T>* vList = &adjacencyLists.at(v);
  auto itr1 = vList->find(w);
  if(itr1 == vList->end()){
    throw UnknownEdgeException(v, w);
  }else{
    vList->erase(itr1);
  }

  edgeNum -= 1;
  /*
  std::cout << "graph has now" << std::endl;
  for (const auto& [key, value] : adjacencyLists){
    std::cout << key << ": ";
    auto itr = value.begin();
    for(; itr != value.end(); itr++){
      std::cout << *itr << ", ";
    }
    std::cout << std::endl;
  }*/
}

template <typename T>
void InterferenceGraph<T>::addVertex(const T &vertex) {
  int listSize = adjacencyLists.size();
  //std::cout << "try to add vertex: " << vertex << std::endl;
  if(verticesSet.find(vertex) != verticesSet.end()){
    return;
  }else{
    verticesSet.insert(vertex);
    std::unordered_set<T> adList = {};
    adjacencyLists[vertex] = adList;
  }
  //std::cout << "success to add vertex: " << vertex << std::endl;
  //this->quicksort(0, listSize);

  listSize += 1;
  /*
  std::cout << "graph has now " << std::endl;
  for(int i = 0; i < listSize; i++){
    std::cout << adjacencyLists[i].front() << ", ";
  }
  std::cout << std::endl;
  */
}

template <typename T>
void InterferenceGraph<T>::removeVertex(const T &vertex) {
  //std::cout << "try to remove vertex " << vertex << std::endl;
  std::unordered_set<T>* vList = &adjacencyLists.at(vertex);

  auto itr = vList->begin();
  while(itr != vList->end()){
  //  std::cout << "try remove edge: " << vertex << ", " << *itr << std::endl;
    this->removeEdge(vertex, *itr);
    itr = vList->begin();
  }
  //std::cout << "remove done: " << vertex << std::endl;
  //vList自体は消せてない
  verticesSet.erase(vertex);
  adjacencyLists.erase(vertex);
  /*
  std::cout << "graph has now" << std::endl;
  for (const auto& [key, value] : adjacencyLists){
    std::cout << key << ": ";
    auto itr = value.begin();
    for(; itr != value.end(); itr++){
      std::cout << *itr << ", ";
    }
    std::cout << std::endl;
  }*/
}

template <typename T>
bool InterferenceGraph<T>::interferes(const T &v, const T &w) const {

  std::unordered_set<T> vList = adjacencyLists.at(v);
  std::unordered_set<T> wList = adjacencyLists.at(w);

  if(vList.size() > wList.size()){
    auto itr = vList.find(w);
    if(itr != vList.end()){
      return true;
    }
  }else{
    auto itr = wList.find(v);
    if(itr != wList.end()){
      return true;
    }
  }

  return false;
}

template <typename T> unsigned InterferenceGraph<T>::degree(const T &v) const {
  std::unordered_set<T> vList = adjacencyLists.at(v);
  return vList.size();
}

/*
template <typename T>
int InterferenceGraph<T>::partition(int start, int end)
{
    T pivot = adjacencyLists[end].front();
    int pIndex = start;

    for (int i = start; i < end; i++)
    {
        if (adjacencyLists[i].front() <= pivot)
        {
            this->swapLists(i, pIndex);
            pIndex++;
        }
    }

    this->swapLists(pIndex, end);
    return pIndex;
}

template <typename T>
void InterferenceGraph<T>::quicksort(int start, int end)
{
    if (start >= end) {
        return;
    }
    int pivot = partition(start, end);
    quicksort(start, pivot - 1);
    quicksort(pivot + 1, end);
}

template <typename T>
void InterferenceGraph<T>::swapLists(int index1, int index2){
  std::list<T> temp;
  temp = adjacencyLists[index1];
  adjacencyLists[index1] = adjacencyLists[index2];
  adjacencyLists[index2] = temp;
}*/

/*
template <typename T>
int InterferenceGraph<T>::findList(const T &v) const{
  int listSize = adjacencyLists.size();
  //std::cout << "find " << v << ", listSize = " << listSize << std::endl;
  for(int i = 0; i < listSize; i++){
    if(adjacencyLists[i].front() == v){
      return i;
    }
  }
  throw UnknownVertexException(v);
}*/

/*
template <typename T>
int InterferenceGraph<T>::findList(const T &v) const{
  int listSize = adjacencyLists.size();
  //std::cout << "find " << v << ", listSize = " << listSize << std::endl;
  int left = 0;
  int right = listSize-1;
  int pivot;

  while(right-left > 0){
    pivot = (left+right)/2;
    //std::cout << adjacencyLists[pivot].front() << ", " << v << std::endl;
    if(adjacencyLists[pivot].front() == v){
    //  std::cout << "return: " << pivot << std::endl;
      return pivot;
    }else if(adjacencyLists[pivot].front() > v){
      right = pivot-1;
    }else{
      left = pivot+1;
    }
  }

  if(right == left && adjacencyLists[right].front() == v){
    //std::cout << "return: " << right << std::endl; 
    return right;
  }else{
    throw UnknownVertexException(v);
  }
}*/

#endif
