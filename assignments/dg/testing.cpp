#include <iostream>
#include <vector>
#include <exception>
#include "graph.h"


int main() {

    std::vector<std::string> v{"Hello", "How", "Are", "You"};
    std::sort(v.begin(), v.end());
    for (auto a : v){
        std::cout << a << '\n';
    }
}