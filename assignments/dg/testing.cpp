#include <iostream>
#include <vector>
#include <exception>
#include <memory>
#include <tuple>
#include <algorithm>

#include "graph.h"

using namespace std;
/*/
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
*/
int main() {
/*
    std::tuple<int, int, int> tup4 {3,2,-8};
    std::tuple<int, int, int> tup2 {2,1,1};
    std::tuple<int, int, int> tup3 {2,4,2};
<<<<<<< HEAD
    
    std::tuple<int, int, int> tup5 {3,2,2};
    
=======

    std::tuple<int, int, int> tup5 {3,2,2};

>>>>>>> 1427953cdff0347c8fe053d94c42a630b24fcd9f
    std::vector<std::shared_ptr<std::tuple<int,int,int>>> vec;
    vec.push_back(make_shared<tuple<int, int, int>>(tup2));
    vec.push_back(make_shared<tuple<int, int, int>>(tup4));
    vec.push_back(make_shared<tuple<int, int, int>>(tup3));
    vec.push_back(make_shared<tuple<int, int, int>>(tup5));
<<<<<<< HEAD

=======
>>>>>>> 1427953cdff0347c8fe053d94c42a630b24fcd9f
    std::cout << "vector of pointers before sorting: " << endl;
    for (const auto& i : vec){
        std::cout << std::get<0>(*i) << std::get<1>(*i) << std::get<2>(*i) << std::endl;
    }
    std::cout << "vector of pointers after sorting: " << endl;
    std::sort(vec.begin(), vec.end(), CompareSort);
    for (const auto& i : vec){
        std::cout << std::get<0>(*i) << std::get<1>(*i) << std::get<2>(*i) << std::endl;
    }
    */
    std::tuple<std::string, std::string, double> tup1 {"d","a",5.4};

    std::tuple<std::string, std::string, double> tup2 {"a","b",-3.4};
    std::tuple<std::string, std::string, double> tup3 {"a","b",1.8};

    std::tuple<std::string, std::string, double> tup4 {"a","c",3.7};
    std::tuple<std::string, std::string, double> tup5 {"a","c",1.1};

    std::tuple<std::string, std::string, double> tup6 {"c","a",8.6};

    auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3, tup4, tup5, tup6};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};
  g.PrintEdges();
    g.find("a","b",-3.4);
    //std::cout << "Found: (" << (*it2)->src_.lock()->value_ << ", " << (*it2)->dest_.lock()->value_ << ", " << it2->weight_ << ")" << '\n';

//    for (const auto it: g) {
//        std::cout << '<' << std::get<0>(it) << ", ";
//        std::cout << std::get<1>(it) << ", ";
//        std::cout << std::get<2>(it) << '>' << '\n';
//    }


//    for (auto it = g.crbegin(); it != g.crend(); ++it) {
//        std::cout << '<' << std::get<0>(*it) << ", ";
//        std::cout << std::get<1>(*it) << ", ";
//        std::cout << std::get<2>(*it) << '>' << '\n';
//    }
}