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

    std::vector<std::shared_ptr<std::tuple<int,int,int>>> vec;
    vec.push_back(make_shared<tuple<int, int, int>>(tup2));
    vec.push_back(make_shared<tuple<int, int, int>>(tup4));
    vec.push_back(make_shared<tuple<int, int, int>>(tup3));

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
    // std::tuple<std::string, std::string, double> tup1 {"d","a",5.4};
    // std::tuple<std::string, std::string, double> tup2 {"a","b",-3.4};
    // std::tuple<std::string, std::string, double> tup3 {"a","b",1.8};
    // std::tuple<std::string, std::string, double> tup4 {"a","c",3.7};
    // std::tuple<std::string, std::string, double> tup5 {"a","c",1.1};
    // std::tuple<std::string, std::string, double> tup6 {"c","a",8.6};
    // auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3, tup4, tup5, tup6};
    // gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    // std::cout << g;
    // auto it = g.find("a","b",1.8);
    // g.erase(it);
    // it = g.find("a","b", -2);
    // it = g.erase(it);
    // if (it == g.end()){
    //     std::cout <<"poo1" << '\n';
    // }
    // it = g.find("d","a", 5.4);
    // it = g.erase(it);
    // if (it == g.end()){
    //     std::cout <<"poo2" << '\n';
    // }
    // std::cout << g;
    

    /* tuple<int, int, int> n1{1,5,-1};
    tuple<int, int, int> n2{2,1,1};
    tuple<int, int, int> n3{2,4,2};
    tuple<int, int, int> n4{3,6,-8};
    tuple<int, int, int> n5{3,2,2};
    tuple<int, int, int> n6{4,1,-4};
    tuple<int, int, int> n7{4,5,3};
    tuple<int, int, int> n8{5,2,7};
    tuple<int, int, int> n9{6,2,5};
    tuple<int, int, int> n10{6,3,10};
    auto f = std::vector<std::tuple<int, int, int>>{n1, n2, n3, n4, n5, n6, n7, n8, n9, n10};
    gdwg::Graph<int, int> g2{f.begin(), f.end()};
    g2.DeleteNode(2); 
    cout<< g2; */

    // gdwg::Graph<int, int> g3;
    // g3.InsertNode(1);
    // g3.InsertNode(2);
    // g3.InsertNode(3);
    // g3.DeleteNode(1);
    // auto vec = g3.GetNodes();
    // g3.DeleteNode(2);
    // g3.DeleteNode(3);
    // cout << g3;



    // Internal representation
//    gdwg::Graph<std::string, int> g4;
//    {
//        std::string s1{"Hello"};
//        g4.InsertNode(s1);
//    }

    // Even though s1 has gone out of scope, g has its own
    //  copied resource that it has stored, so the node
    //  will still be in here.
//    std::cout << g4.IsNode("Hello") << "\n"; // prints 'true';

   tuple<int, int, int> m1{1,1,-1};
   tuple<int, int, int> m2{1,1,1};
   tuple<int, int, int> m3{1,1,2};
   tuple<int, int, int> m4{1,1,-8};
   auto h = std::vector<std::tuple<int, int, int>>{m2, m1, m3, m4};
   gdwg::Graph<int, int> g5{h.begin(), h.end()};
   cout << g5;

//    for (const auto& it : g) {
//        std::cout << '<' << std::get<0>(it) << ", ";
//        std::cout << std::get<1>(it) << ", ";
//        std::cout << std::get<2>(it) << '>' << '\n';
//    }
//    auto it1 = g.find("a","c",1.1);
//    std:: cout << "Removing: <" << std::get<0>(*it1) << "," <<
//        std::get<1>(*it1) << "," << std::get<2>(*it1) << ">" << '\n';
//    auto it2 = g.erase(it1);
//    while (it2 != g.begin()) {
//      --it2;
//    }
//    while (it2 != g.end()) {
//      std::cout << '<' << std::get<0>(*it2) << ", ";
//      std::cout << std::get<1>(*it2) << ", ";
//      std::cout << std::get<2>(*it2) << '>' << '\n';
//      ++it2;
//    }
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