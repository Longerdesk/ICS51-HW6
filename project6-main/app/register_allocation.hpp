#ifndef __PROJ_6__HPP
#define __PROJ_6__HPP

#include <string>
#include <unordered_map>
#include "InterferenceGraph.hpp"

/*
class Vertex{
	public:
    std::string name;
    int degree;
	
	Vertex(){
        degree = 0;
	}

	Vertex(std::string name1, int degree1){
		name = name1;
        degree = degree1;
	}
	
};

inline bool operator < (const Vertex& vertex1, const Vertex& vertex2){
	if((vertex1.degree) < (vertex2.degree)){
		return true;
	}else{
		return false;
	}
}*/

namespace RA {

using Variable = std::string;
using Register = int;
using RegisterAssignment = std::unordered_map<Variable, Register>;


RegisterAssignment assignRegisters(const std::string &path_to_graph,
                                   int num_registers) noexcept;

}; // namespace proj6


	int partition(InterferenceGraph<std::string> ig, std::vector<std::string> &a, int start, int end);
  
  	void quicksort(InterferenceGraph<std::string> ig, std::vector<std::string> &a, int, int);

 	void swapLists(std::vector<std::string> &a, int, int);

#endif