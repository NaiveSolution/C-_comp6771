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
      // May need to change way of testing
      THEN("Using the getNodes function will return nodes {1, 2, 3}") {
        std::vector<int> expected{1,2,3};
        REQUIRE(g.GetNodes() == expected);
      }
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
      gdwg::Graph<std::string, double> g{e.begin(), e.end()};
      /* Need to find a way to test that the graph exists
       * At the moment i'll use the getNodes method but
       * this is bad testing.
       */
      THEN("Using the getNodes function will return nodes {Hello, how, are}") {
        std::vector<std::string> expected{"Hello", "how", "are"};
        REQUIRE(g.GetNodes() == expected);
      }
    }
  }
  GIVEN("An initialiser list") {
    WHEN("A Graph<char,string> is created using the initialiser list") {
      gdwg::Graph<char, std::string> g{'a', 'b', 'x', 'y'};
      /* Need to find a way to test that the graph exists
         * At the moment i'll use the getNodes method but
         * this is bad testing.
         */
      THEN("Using the getNodes function will return nodes {a,b,x,y}") {
        std::vector<char> expected{'a', 'b', 'x', 'y'};
        REQUIRE(g.GetNodes() == expected);
      }
    }
    WHEN("A Graph<int,int> is created using the initialiser list") {
      gdwg::Graph<int,int> g{1,2,3};
      /* Need to find a way to test that the graph exists
      * At the moment i'll use the getNodes method but
      * this is bad testing.
      */
      THEN("Using the getNodes function will return nodes {1,2,3}") {
        std::vector<int> expected{1,2,3};
        REQUIRE(g.GetNodes() == expected);
      }
    }
  }
  GIVEN("A Graph<int,int>") {
    gdwg::Graph<int,int> g1{1,2,3};
    WHEN("A new graph is constructed using the move constructor") {
      gdwg::Graph<int,int> g2(std::move(g1));
      THEN("Graph g2 will have nodes {1,2,3}") {
        std::vector<int> expected{1,2,3};
        REQUIRE(g2.GetNodes() == expected);
      }
      AND_THEN("Graph g1 will not have any nodes") {
        REQUIRE(g1.GetNodes().empty());
      }
    }
  }
  GIVEN("An existing graph 'a' can be be copied"){
    std::vector<std::string> v{"Hello", "how", "are", "you"};
    gdwg::Graph<std::string, double> a{v.begin(),v.end()};
    WHEN("A new graph 'aCopy' is constructed using the copy constructor"){
      gdwg::Graph<std::string, double> aCopy{a};
      THEN("Graph aCopy will have the nodes {Hello,how,are,you}"){
        std::vector<std::string> expected{"Hello", "how", "are", "you"};
        REQUIRE(aCopy.GetNodes() == expected);
      }
    }
  }
}

SCENARIO("Graphs use copy and move equal operators") {
  GIVEN("Two Graphs <int,int>") {
    gdwg::Graph<int,int> g1{1,2,3};
    gdwg::Graph<int,int> g2{4,5,6};
    WHEN("The move assignment operator is called g2 = std::move(g1)") {
      g2 = std::move(g1);
      THEN("g2 will have nodes {1,2,3}") {
        std::vector<int> expected{1,2,3};
        REQUIRE(g2.GetNodes() == expected);
      }
      AND_THEN("Graph g1 will not have any nodes") {
        REQUIRE(g1.GetNodes().empty());
      }
    }
  }
}

SCENARIO("Given a graph 'a' and 'b' with strings for nodes, try and insert nodes"){
  GIVEN("A graph with some string nodes"){
    std::vector<std::string> v1{"a", "b", "z", "f"};
    std::vector<std::string> v2{"f", "o", "d"};
    gdwg::Graph<std::string, double> a{v1.begin(),v1.end()};
    gdwg::Graph<std::string, double> b{v2.begin(),v2.end()};
    WHEN("Trying to insert a node that doesnt exist in 'a'"){
      std::string str{"c"};
      a.InsertNode(str);
      THEN("Graph 'a' will have the nodes {a, b, z, f, c}"){
        std::vector<std::string> expected{"a", "b", "z", "f", "c"};
        REQUIRE(a.GetNodes() == expected);
      }
    }
    WHEN("Trying to insert a node that does exist in 'b'"){
      std::string str{"o"};
      b.InsertNode(str);
      THEN("Graph 'b' will have the nodes {f, o, d}"){
        std::vector<std::string> expected{"f", "o", "d"};
        REQUIRE(b.GetNodes() == expected);
      }
    }
  }
}