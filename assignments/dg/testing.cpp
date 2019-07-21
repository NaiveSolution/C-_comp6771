#include <iostream>
#include <vector>
#include <exception>
#include "graph.h"


int main() {

    std::vector<int> v1{1, 2, 3, 4};
    std::vector<int> v2{5, 6, 7};
    gdwg::Graph<int, double> a{v1.begin(),v1.end()};
    gdwg::Graph<int, double> b{v2.begin(),v2.end()};
    a.DeleteNode(3);
    
}