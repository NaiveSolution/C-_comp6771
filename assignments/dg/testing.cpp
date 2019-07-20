#include <iostream>
#include <vector>
#include <exception>
#include "graph.h"
#include "graph.tpp"

int main() {
std::cout << "Enter -1 to quit\n";
std::vector<int> items{97, 84, 72, 65};
gdwg::Graph<std::string, int> a;

std::cout << "Enter an index: ";
for (int print_index; std::cin >> print_index; ) {
if (print_index == -1) break;
try {
std::cout << items.at(print_index) << '\n';
items.resize(items.size() + 10);
} catch (const std::out_of_range& e) {
std::cout << "Index out of bounds\n";
} catch (const std::exception& e) {
std::cout << "Something else happened";
}
std::cout << "Enter an index: ";
}
}