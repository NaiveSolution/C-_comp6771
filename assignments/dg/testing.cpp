#include <iostream>
#include <vector>
#include <exception>
#include <memory>
#include <tuple>
#include <algorithm>

//#include "graph.h"

using namespace std;

bool CompareSort(const std::shared_ptr<std::tuple<int, int, int>>& a, const std::shared_ptr<std::tuple<int, int, int>>& b ){
    auto new_a = a.get();
    auto new_b = b.get();
    if (get<0>(*new_a) < get<0>(*new_b))
        return true;
    if ((get<0>(*new_a) == get<0>(*new_b))){
        if (get<1>(*new_a) < get<1>(*new_b))
            return true;
        if (get<1>(*new_a) == get<1>(*new_b) && (get<2>(*new_a) < get<2>(*new_b)))
            return true;
    }
    return false;
}
int main() {

    std::tuple<int, int, int> tup4 {3,2,-8};
    std::tuple<int, int, int> tup2 {2,1,1};
    std::tuple<int, int, int> tup3 {2,4,2};
    
    std::tuple<int, int, int> tup5 {3,2,2};
    
    std::vector<std::shared_ptr<std::tuple<int,int,int>>> vec;
    vec.push_back(make_shared<tuple<int, int, int>>(tup2));
    vec.push_back(make_shared<tuple<int, int, int>>(tup4));
    vec.push_back(make_shared<tuple<int, int, int>>(tup3));
    vec.push_back(make_shared<tuple<int, int, int>>(tup5));

    std::cout << "vector of pointers before sorting: " << endl;
    for (const auto& i : vec){
        std::cout << std::get<0>(*i) << std::get<1>(*i) << std::get<2>(*i) << std::endl;
    }
    std::cout << "vector of pointers after sorting: " << endl;
    std::sort(vec.begin(), vec.end(), CompareSort);
    for (const auto& i : vec){
        std::cout << std::get<0>(*i) << std::get<1>(*i) << std::get<2>(*i) << std::endl;
    }
}