#include <iostream>
#include <vector>
#include <exception>
#include "graph.h"


int main() {

    int s1 = 1;
    int s2 = 2;
    int s3 = 3;
    int s4 = 4;
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e3 = std::make_tuple(s3, s4, 8.3);
    auto e = std::vector<std::tuple<int, int, double>>{e1, e2, e3};
    gdwg::Graph<int, double> g{e.begin(), e.end()};
    
}