/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

*/

#include "assignments/dg/graph.h"
#include "catch.h"

// TODO(students): Fill this in.
SCENARIO("Graphs can be constructed") {
  GIVEN("A standard Vector") {
    std::vector<int> v{1,2,3};
    WHEN("The vector is used to construct a graph") {
      gdwg::Graph<int,int> g(v.begin(),v.end());
    }
  }
  GIVEN("A vector of tuples") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    WHEN("A Graph is constructed using the vector of tuples") {
      gdwg::Graph<std::string, double> b{e.begin(), e.end()};
    }
  }
}