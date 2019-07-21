#include <iostream>
#include <vector>
#include <exception>
#include "graph.h"


int main() {

    gdwg::Graph<std::string, int> a;
    std::vector<std::string> v{"Hello", "how", "are", "you"};
    gdwg::Graph<std::string, double> b{v.begin(),v.end()};
    std::vector<std::string> nodes = b.GetNodes();
    for (auto& element : nodes){
        std::cout << element << '\n';
    }

    gdwg::Graph<std::string, double> c{b};
    std::vector<std::string> nodes2 = c.GetNodes();
    for (auto& element : nodes2){
        std::cout << element << '\n';
    }
}