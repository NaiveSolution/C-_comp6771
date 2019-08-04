/*

  Since we are testing class functionality only, testing all functions and methods
  separately is the best approach as the class design is highly modular. Overloaded operators and Iterators
  require significantly more testing than the other methods as there is more flexibility 
  (and hence possibilities of exceptions) with the choices of operands and valid memory addresses.

  Testing of all components was done with the outlying cases in mind; inputs of 0, of no inputs,
  of negative inputs and out of bounds inputs. It is assumed that basic and valid inputs will not,
  or should not, throw errors/exceptions in terms of constructors or methods.

  Testing of iterators generally involves testing a valid but unusual graph.
  Examples could be an empty graph, a graph of nodes with no edges, a graph with 1 node that has many
  self edges, and highly interconnected graphs.

  Where an exception can be thrown by a method, it has a test case written for it.

*/

#include <string>
#include <utility>

#include "assignments/dg/graph.h"
#include "catch.h"

// Constructors
SCENARIO("Graphs can be constructed") {
  GIVEN("A standard Vector") {
    std::vector<int> v{1, 2, 3};
    WHEN("The vector is used to construct a graph") {
      gdwg::Graph<int, int> g(v.begin(), v.end());
      // May need to change way of testing
      THEN("Using the getNodes function will return nodes {1, 2, 3}") {
        std::vector<int> expected{1, 2, 3};
        REQUIRE(g.GetNodes() == expected);
      }
    }
    GIVEN("An empty Vector") {
      std::vector<int> v{};
      WHEN("The vector is used to construct a graph") {
        gdwg::Graph<int, int> g(v.begin(), v.end());
        THEN("Using the getNodes function will return an empty nodes vector") {
          std::vector<int> expected{};
          REQUIRE(g.GetNodes() == expected);
        }
      }
    }
    GIVEN("No inputs to a graph") {
      WHEN("calling the default constructor") {
        gdwg::Graph<int, int> g;
        THEN("The getNodes function will return an unitialised nodes vector") {
          std::vector<int> expected;
          REQUIRE(g.GetNodes() == expected);
        }
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
      THEN("Using the getNodes function will return nodes {Hello, are, how}") {
        std::vector<std::string> expected{"Hello", "are", "how"};
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
      gdwg::Graph<int, int> g{1, 2, 3};
      /* Need to find a way to test that the graph exists
       * At the moment i'll use the getNodes method but
       * this is bad testing.
       */
      THEN("Using the getNodes function will return nodes {1,2,3}") {
        std::vector<int> expected{1, 2, 3};
        REQUIRE(g.GetNodes() == expected);
      }
    }
  }
  GIVEN("A Graph<int,int>") {
    gdwg::Graph<int, int> g1{1, 2, 3};
    WHEN("A new graph is constructed using the move constructor") {
      gdwg::Graph<int, int> g2(std::move(g1));
      THEN("Graph g2 will have nodes {1,2,3}") {
        std::vector<int> expected{1, 2, 3};
        REQUIRE(g2.GetNodes() == expected);
      }
      AND_THEN("Graph g1 will not have any nodes") { REQUIRE(g1.GetNodes().empty()); }
    }
  }
  GIVEN("An existing graph 'a' can be be copied") {
    std::vector<std::string> v{"are", "how", "you"};
    gdwg::Graph<std::string, double> a{v.begin(), v.end()};
    WHEN("A new graph 'aCopy' is constructed using the copy constructor") {
      gdwg::Graph<std::string, double> aCopy{a};
      THEN("Graph aCopy will have the nodes {are, how ,you}") {
        std::vector<std::string> expected{"are", "how", "you"};
        REQUIRE(aCopy.GetNodes() == expected);
      }
      AND_THEN("Graph 'a' will have the nodes {are, how, you}") {
        std::vector<std::string> expected{"are", "how", "you"};
        REQUIRE(a.GetNodes() == expected);
      }
    }
  }
}

// GetNodes()
SCENARIO("Construct a complicated graph and get its nodes after operations") {
  GIVEN("A new graph 'g' is created") {
    std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                       tup4, tup5, tup6};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("GetNodes() is called on g to return vector of nodes 'vec'") {
      auto vec = g.GetNodes();
      THEN("vec will have {a,b,c,d}") {
        std::vector<std::string> expected{"a", "b", "c", "d"};
        REQUIRE(vec == expected);
      }
    }
    WHEN("DeleteNode('a') is called on g") {
      g.DeleteNode("a");
      auto vec = g.GetNodes();
      THEN("GetNodes() will return vec with {b,c,d}") {
        std::vector<std::string> expected{"b", "c", "d"};
        REQUIRE(vec == expected);
      }
      WHEN("DeleteNode('c') is called on g") {
        g.DeleteNode("c");
        auto vec = g.GetNodes();
        THEN("GetNodes() will return vec with {b,d}") {
          std::vector<std::string> expected{"b", "d"};
          REQUIRE(vec == expected);
        }
        WHEN("DeleteNode('d') is called on g") {
          g.DeleteNode("d");
          auto vec = g.GetNodes();
          THEN("GetNodes() will return vec with  {b}") {
            std::vector<std::string> expected{"b"};
            REQUIRE(vec == expected);
          }
          WHEN("DeleteNode('b') is called on g") {
            g.DeleteNode("b");
            auto vec = g.GetNodes();
            THEN("GetNodes() will return empty vec ") {
              std::vector<std::string> expected{};
              REQUIRE(vec == expected);
            }
          }
        }
      }
    }
  }
  GIVEN("The default constructor is used to get graph 'g'") {
    gdwg::Graph<int, int> g;
    WHEN("vec = g.GetNodes() is called") {
      auto vec = g.GetNodes();
      THEN("vec should be empty") { REQUIRE(vec.empty()); }
    }
  }
}

// Copy and move operators
SCENARIO("Graphs use copy and move equal operators") {
  GIVEN("Two existing graphs g1 & g2") {
    std::vector<std::string> v{"how", "are", "you"};
    gdwg::Graph<std::string, double> g1{v.begin(), v.end()};
    gdwg::Graph<std::string, double> g2;
    WHEN("The copy assignment operator is called g2 = g1") {
      g2 = g1;
      THEN("Graph g2 will have the nodes {are, how, you}") {
        std::vector<std::string> expected{"are", "how", "you"};
        REQUIRE(g2.GetNodes() == expected);
      }
      AND_THEN("Graph g1 will have the nodes {are, how, you}") {
        std::vector<std::string> expected{"are", "how", "you"};
        REQUIRE(g1.GetNodes() == expected);
      }
    }
  }
  GIVEN("Two Graphs <int,int>") {
    gdwg::Graph<int, int> g1{1, 2, 3};
    gdwg::Graph<int, int> g2{4, 5, 6};
    WHEN("The move assignment operator is called g2 = std::move(g1)") {
      g2 = std::move(g1);
      THEN("g2 will have nodes {1,2,3}") {
        std::vector<int> expected{1, 2, 3};
        REQUIRE(g2.GetNodes() == expected);
      }
      AND_THEN("Graph g1 will not have any nodes") { REQUIRE(g1.GetNodes().empty()); }
    }
  }
}

// IsNode()
SCENARIO("Graphs have existing nodes that can be checked for existence") {
  GIVEN("A Graph<int,int> g1") {
    gdwg::Graph<int, int> g1{1, 2, 3};
    WHEN("We check if node with value 1 exists in graph g1") {
      THEN("It will return true") { REQUIRE(g1.IsNode(1)); }
    }
    WHEN("We check if node with value 0 exists in graph g1") {
      THEN("It will return false") { REQUIRE_FALSE(g1.IsNode(0)); }
    }
  }
}

// IsConnected
SCENARIO("Graphs with exisiting nodes and edges can be checked for connectivity") {
  GIVEN("A connected Graph<char,int>") {
    char s1{'a'};
    char s2{'b'};
    char s3{'c'};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<char, char, double>>{e1, e2};
    gdwg::Graph<char, double> g{e.begin(), e.end()};
    WHEN("Checking whether node a->b") {
      THEN("It will return true") { REQUIRE(g.IsConnected('a', 'b')); }
    }
    WHEN("Checking whether node a->c") {
      THEN("It will return false as they are not connected") {
        REQUIRE_FALSE(g.IsConnected('a', 'c'));
      }
    }
    WHEN("Checking whether node b->a") {
      THEN("It will return false as a->b not b->a") { REQUIRE_FALSE(g.IsConnected('b', 'a')); }
    }
  }
}

// InsertNode()
SCENARIO("Given a graph 'a' and 'b' with strings for nodes, try and insert nodes") {
  GIVEN("A graph with some string nodes") {
    std::vector<std::string> v1{"a", "b", "z", "f"};
    std::vector<std::string> v2{"f", "o", "d"};
    gdwg::Graph<std::string, double> a{v1.begin(), v1.end()};
    gdwg::Graph<std::string, double> b{v2.begin(), v2.end()};
    WHEN("Trying to insert a node that doesnt exist in 'a'") {
      std::string str{"c"};
      a.InsertNode(str);
      THEN("Graph 'a' will have the nodes {a, b, c, f, z}") {
        std::vector<std::string> expected{"a", "b", "c", "f", "z"};
        REQUIRE(a.GetNodes() == expected);
      }
    }
    WHEN("Trying to insert a node that does exist in 'b'") {
      std::string str{"o"};
      b.InsertNode(str);
      THEN("Graph 'b' will have the nodes {d, f, o}") {
        std::vector<std::string> expected{"d", "f", "o"};
        REQUIRE(b.GetNodes() == expected);
      }
    }
  }
}

// GetConnected()
SCENARIO("A Graph can check the connections from a source") {
  GIVEN("A graph with some char nodes and double weighted edges") {
    char s1{'a'};
    char s2{'b'};
    char s3{'c'};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s1, s3, 7.6);
    auto e = std::vector<std::tuple<char, char, double>>{e1, e2};
    gdwg::Graph<char, double> g{e.begin(), e.end()};
    WHEN("GetConnected('a') is called a vector of chars are returned") {
      auto connections = g.GetConnected('a');
      THEN("The vector will contain the nodes {b,c}") {
        std::vector<char> expected{'b', 'c'};
        REQUIRE(connections == expected);
      }
    }
    WHEN("GetConnected('b') is called a vector of chars are returned") {
      auto connections = g.GetConnected('b');
      THEN("The vector should be empty as there are no connections") {
        REQUIRE(connections.empty());
      }
    }
    WHEN("GetConnected('d') is called") {
      THEN("An exception is thrown as d is not an existing node") {
        REQUIRE_THROWS_WITH(g.GetConnected('d'),
                            "Cannot call "
                            "Graph::GetConnected if src doesn't exist in the graph");
      }
    }
  }
}

// GetWeights()
SCENARIO("A Graph can have its edges checked for weighting") {
  GIVEN("A Graph with some char nodes and double weighted edges") {
    char s1{'a'};
    char s2{'b'};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s1, s2, 7.6);
    auto e = std::vector<std::tuple<char, char, double>>{e1, e2};
    gdwg::Graph<char, double> g{e.begin(), e.end()};
    WHEN("Edge a->b is checked for weights") {
      THEN("It will return a double 5.4") {
        std::vector<double> expected{5.4, 7.6};
        REQUIRE(g.GetWeights('a', 'b') == expected);
      }
    }
    WHEN("Trying to check weights between non-existant nodes") {
      THEN("An exception is thrown") {
        REQUIRE_THROWS_WITH(g.GetWeights('d', 'e'), "Cannot call Graph::GetWeights if src "
                                                    "or dst node don't exist in the graph");
      }
    }
  }
}

// DeleteNode()
SCENARIO("Given a graph 'a' and 'b', try and delete nodes") {
  GIVEN("A graph with some int nodes") {
    std::vector<int> v1{1, 2, 3, 4};
    std::vector<int> v2{5, 6, 7};
    gdwg::Graph<int, double> a{v1.begin(), v1.end()};
    gdwg::Graph<int, double> b{v2.begin(), v2.end()};
    WHEN("Trying to delete a node that exists in 'a'") {
      a.DeleteNode(1);
      THEN("Graph 'a' will have the nodes {2, 3, 4}") {
        std::vector<int> expected{2, 3, 4};
        REQUIRE(a.GetNodes() == expected);
      }
    }
    WHEN("Trying to delete a node that doesnt exist in 'b'") {
      b.DeleteNode(8);
      THEN("Graph 'b' will have the nodes {5, 6, 7}") {
        std::vector<int> expected{5, 6, 7};
        REQUIRE(b.GetNodes() == expected);
      }
    }
  }
  GIVEN("A graph with some int nodes and edge weights") {
    int s1 = 1;
    int s2 = 2;
    int s3 = 3;
    int s4 = 4;
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e3 = std::make_tuple(s3, s4, 8.3);
    auto e = std::vector<std::tuple<int, int, double>>{e1, e2, e3};
    gdwg::Graph<int, double> g{e.begin(), e.end()};
    WHEN("Trying to delete a node that exists in 'g'") {
      g.DeleteNode(s1);
      THEN("Graph 'g' will have the nodes {2, 3, 4}") {
        std::vector<int> expected{2, 3, 4};
        REQUIRE(g.GetNodes() == expected);
      }
      THEN("Graph 'g' will have the edges {7.6, 8.3}") {
        REQUIRE(g.GetWeights(2, 3)[0] == 7.6);
        REQUIRE(g.GetWeights(3, 4)[0] == 8.3);
      }
    }
    GIVEN("A large graph 'g' with many interconnected nodes") {
      std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
      std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
      std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
      std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
      std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
      std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
      auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                         tup4, tup5, tup6};
      gdwg::Graph<std::string, double> g{e.begin(), e.end()};
      WHEN("Trying to delete the node 'a' that has an edge with every other node") {
        g.DeleteNode("a");
        THEN("Graph 'g' will have nodes {b,c,d}") {
          std::vector<std::string> expected{"b", "c", "d"};
          REQUIRE(g.GetNodes() == expected);
          AND_THEN("Graph 'g' will contain no edges (as 'a' was connected to all nodes)") {
            for (const auto& i : g.GetNodes()) {
              REQUIRE(g.GetConnected(i).empty());
            }
          }
        }
      }
    }
  }
}

// InsertEdge()
SCENARIO("A Graph with existing nodes can insert new edges") {
  GIVEN("A graph with some char nodes") {
    gdwg::Graph<char, int> g{'a', 'b', 'c'};
    WHEN("An edge is inserted a->b with weight 2") {
      g.InsertEdge('a', 'b', 2);
      THEN("There will be an edge from a->b") { REQUIRE(g.IsConnected('a', 'b')); }
      AND_THEN("No edge from b->a") { REQUIRE_FALSE(g.IsConnected('b', 'a')); }
    }
    WHEN("An edge is inserted from a non-exisiting node to 'a'") {
      THEN("An exception should be thrown") {
        REQUIRE_THROWS_WITH(g.InsertEdge('d', 'a', 3),
                            "Cannot call "
                            "Graph::InsertEdge when either src or dst node does not exist");
      }
    }
  }
}

// Clear()
SCENARIO("A Graph with nodes and edges can be cleared") {
  GIVEN("A Graph with some char nodes and double weighted edges") {
    char s1{'a'};
    char s2{'b'};
    char s3{'c'};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<char, char, double>>{e1, e2};
    gdwg::Graph<char, double> g{e.begin(), e.end()};
    WHEN("The Graph is cleared") {
      g.clear();
      THEN("There should be no nodes or edges") {
        REQUIRE(g.GetNodes().empty());
        for (const auto& i : g.GetNodes()) {
          REQUIRE_THROWS_WITH(g.GetConnected(i),
                              "Cannot call Graph::GetConnected if src doesn't exist in the graph");
        }
      }
      AND_THEN("Nodes can be inserted") {
        g.InsertNode('d');
        std::vector<char> expected{'d'};
        REQUIRE(g.GetNodes() == expected);
      }
    }
  }
}

// erase()
SCENARIO("A graph can erase edges") {
  GIVEN("A Graph with some char nodes and double weighted edges") {
    char s1{'a'};
    char s2{'b'};
    char s3{'c'};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<char, char, double>>{e1, e2};
    gdwg::Graph<char, double> g{e.begin(), e.end()};
    WHEN("The edge a->b(5.4) is erased") {
      REQUIRE(g.erase('a', 'b', 5.4));
      THEN("It will not exist in the graph anymore") { REQUIRE(g.GetWeights('a', 'b').empty()); }
    }
    WHEN("An edge that does not exist is removed a->c") {
      REQUIRE_FALSE(g.erase('a', 'c', 5.4));
      THEN("No changes are made to existing edges") {
        std::vector<double> ab{5.4};
        std::vector<double> bc{7.6};
        REQUIRE(g.GetWeights('a', 'b') == ab);
        REQUIRE(g.GetWeights('b', 'c') == bc);
      }
    }
  }
}

// Replace()
// Check if this works with N = std::vector<int>
SCENARIO("A graph can replace nodes") {
  GIVEN("A Graph 'g' with some char nodes (a,b,c)") {
    std::vector<char> v{'a', 'b', 'c'};
    gdwg::Graph<char, int> g{v.begin(), v.end()};
    g.InsertEdge('a', 'b', 1);
    g.InsertEdge('c', 'a', 2);
    WHEN("The node 'a' is replaced with 'z'") {
      g.Replace('a', 'z');
      THEN("The graph 'g' is changed from (a,b,c) to (b,c,z)") {
        std::vector<char> expected{'b', 'c', 'z'};
        REQUIRE(g.GetNodes() == expected);
      }
      AND_THEN("Node z is connected to b with weights 1") {
        std::vector<char> expected_connection{'b'};
        std::vector<int> expected_weights{1};
        REQUIRE(g.GetConnected('z') == expected_connection);
        REQUIRE(g.GetWeights('z', 'b') == expected_weights);
      }
      AND_THEN("Node c is connected to z with weights 2") {
        std::vector<char> expected_connection{'z'};
        std::vector<int> expected_weights{2};
        REQUIRE(g.GetConnected('c') == expected_connection);
        REQUIRE(g.GetWeights('c', 'z') == expected_weights);
      }
    }
    WHEN("A node is replaced with a node that already exists") {
      auto result = g.Replace('a', 'b');
      THEN("The function will return false") { REQUIRE_FALSE(result); }
    }
    WHEN("A node that does not exist in 'g' is replaced") {
      THEN("No changes are made to existing nodes in graph 'g'") {
        REQUIRE_THROWS_WITH(g.Replace('f', 'g'),
                            "Cannot call Graph::Replace on a node that doesn't exist");
      }
    }
  }
}

// MergeReplace()
SCENARIO("A graph can merge replace nodes") {
  GIVEN("A graph with char nodes and int edges") {
    std::vector<char> v{'a', 'b', 'c'};
    gdwg::Graph<char, int> g{v.begin(), v.end()};
    g.InsertEdge('a', 'b', 1);
    g.InsertEdge('c', 'a', 2);
    WHEN("Node 'b' merge replaces node 'a'") {
      g.MergeReplace('a', 'b');
      THEN("Node b will be connected to itself") {
        std::vector<char> expected{'b'};
        REQUIRE(g.GetConnected('b') == expected);
      }
      AND_THEN("c->b with weights 2") {
        std::vector<int> expected{2};
        REQUIRE(g.GetWeights('c', 'b') == expected);
      }
      AND_THEN("Graph g will have nodes {b,c}") {
        std::vector<char> expected{'b', 'c'};
        REQUIRE(g.GetNodes() == expected);
      }
    }
    WHEN("Node 'a' is merge replaced with 'd'") {
      THEN("An exception is thrown as Node d does not exist") {
        REQUIRE_THROWS_WITH(g.MergeReplace('a', 'd'),
                            "Cannot call Graph::MergeReplace "
                            "on old or new data if they don't exist in the graph");
      }
    }
    WHEN("Node 'd' is merge replaced with 'a'") {
      THEN("An exception is thrown as Node d does not exist") {
        REQUIRE_THROWS_WITH(g.MergeReplace('d', 'a'),
                            "Cannot call Graph::MergeReplace "
                            "on old or new data if they don't exist in the graph");
      }
    }
  }
  GIVEN("The graph example 2 used in the assignment spec"){
    std::tuple<std::string, std::string, int> tup1{"A","B", 1};
    std::tuple<std::string, std::string, int> tup2{"A","C", 2};
    std::tuple<std::string, std::string, int> tup3{"A","D", 3};
    std::tuple<std::string, std::string, int> tup4{"B","B", 1};
    auto e = std::vector<std::tuple<std::string, std::string, int>>{tup1, tup2, tup3, tup4};
    gdwg::Graph<std::string, int> g{e.begin(), e.end()};
    WHEN("MergeReplace is used on (A,B)"){
      g.MergeReplace("A", "B");
      THEN("all instances of A will be replaced with B"){
        std::vector<std::string> expected{"B", "C", "D"};
        REQUIRE(g.GetNodes() == expected);
      }
      AND_THEN("Node B will be connected as: B-B-1, B-C-2, B-D-3"){
        std::vector<int> expected_1{1};
        REQUIRE(g.GetWeights("B", "B") == expected_1);
        std::vector<int> expected_2{2};
        REQUIRE(g.GetWeights("B", "C") == expected_2);
        std::vector<int> expected_3{3};
        REQUIRE(g.GetWeights("B", "D") == expected_3);
      }
    }
  }
  GIVEN("The graph example 3 used in the assignment spec"){
    std::tuple<std::string, std::string, int> tup1{"A","B", 3};
    std::tuple<std::string, std::string, int> tup2{"C","B", 2};
    std::tuple<std::string, std::string, int> tup3{"D","B", 4};
    auto e = std::vector<std::tuple<std::string, std::string, int>>{tup1, tup2, tup3};
    gdwg::Graph<std::string, int> g{e.begin(), e.end()};
    WHEN("MergeReplace is used on (B,A)"){
      g.MergeReplace("B", "A");
      THEN("all instances of B will be replaced with A"){
        std::vector<std::string> expected{"A", "C", "D"};
        REQUIRE(g.GetNodes() == expected);
      }
      AND_THEN("Node B will be connected as: A-A-3, C-A-2, D-A-4"){
        std::vector<int> expected_1{3};
        REQUIRE(g.GetWeights("A", "A") == expected_1);
        std::vector<int> expected_2{2};
        REQUIRE(g.GetWeights("C", "A") == expected_2);
        std::vector<int> expected_3{4};
        REQUIRE(g.GetWeights("D", "A") == expected_3);
      }
    }
  }
}

// const_iterator find(), find() const
SCENARIO("Construct a complicated graph and use an iterator to find edges") {
  GIVEN("A new graph 'g' is created (non-const)") {
    std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                       tup4, tup5, tup6};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("find(a,b,1.8) is called on a iterator of g") {
      auto it = g.find("a", "b", 1.8);
      THEN("the resultant iterator can be dereferenced to get node1, node2 and edge") {
        REQUIRE(std::get<0>(*it) == "a");
        REQUIRE(std::get<1>(*it) == "b");
        REQUIRE(std::get<2>(*it) == 1.8);
      }
    }
    WHEN("an edge cannot be found using find()") {
      auto it = g.find("a", "b", -2);
      THEN("The iterator will be pointing to the end() of the graph") { REQUIRE(it == g.end()); }
    }
  }
  GIVEN("A new graph 'g' is created (const)") {
    const std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    const std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    const std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    const std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    const std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    const std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    const auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                             tup4, tup5, tup6};
    const gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("find(a,b,1.8) is called on a iterator of g") {
      const auto it = g.find("a", "b", 1.8);
      THEN("the resultant iterator can be dereferenced to get node1, node2 and edge") {
        REQUIRE(std::get<0>(*it) == "a");
        REQUIRE(std::get<1>(*it) == "b");
        REQUIRE(std::get<2>(*it) == 1.8);
      }
    }
    WHEN("an edge cannot be found using find()") {
      const auto it = g.find("a", "b", -2);
      THEN("The iterator will be pointing to the end() of the graph") { REQUIRE(it == g.end()); }
    }
  }
}

// const_iterator erase()
SCENARIO("Construct a complicated graph and use an iterator to erase edges") {
  GIVEN("A new graph 'g' is created") {
    std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                       tup4, tup5, tup6};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("erase() is called on (a,b,1.8) using the iterator") {
      auto it = g.find("a", "b", 1.8);
      g.erase(it);
      THEN("the returned iterator points to edge (a, c, 1.1)") {
        REQUIRE(std::get<0>(*it) == "a");
        REQUIRE(std::get<1>(*it) == "c");
        REQUIRE(std::get<2>(*it) == 1.1);
      }
    }
    WHEN("an edge cannot be erased when it = end() of graph)") {
      auto it = g.find("a", "b", -2);
      THEN("The iterator will be pointing to the end() of the graph") {
        REQUIRE(g.erase(it) == g.end());
      }
    }
    WHEN("erase() is called on (d,a,5.4) using the iterator") {
      auto it = g.find("d", "a", 5.4);
      it = g.erase(it);
      THEN("The iterator will be pointing to the end() of the graph, and node 'd' will have no "
           "edges to it") {
        REQUIRE(it == g.end());
        auto vec = g.GetConnected("d");
        REQUIRE(vec.empty());
      }
    }
  }
  GIVEN("A new graph 'g' is created with one node connected to itself") {
    std::tuple<int, int, double> tup1{1, 1, 3};
    auto e = std::vector<std::tuple<int, int, double>>{tup1};
    gdwg::Graph<int, double> g{e.begin(), e.end()};
    WHEN("erase() is called on (1,1,3) using the iterator") {
      auto it = g.find(1, 1, 3);
      it = g.erase(it);
      THEN("The iterator will be pointing to the end() of the graph") { REQUIRE(it == g.end()); }
    }
  }
}

// const_iterator cbegin()
SCENARIO("A graph has a const iterator that points to the beginning of the graph") {
  GIVEN("A new const graph 'g' is created") {
    const std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    const std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    const std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    const std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    const std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    const std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    const auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                             tup4, tup5, tup6};
    const gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("cbegin() is called on the graph") {
      auto it = g.cbegin();
      THEN("The iterator can be dereferenced to get the first element in edges_") {
        REQUIRE(std::get<0>(*it) == "a");
        REQUIRE(std::get<1>(*it) == "b");
        REQUIRE(std::get<2>(*it) == -3.4);
      }
    }
  }
  GIVEN("A new non-const graph 'g' is created") {
    std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                       tup4, tup5, tup6};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("cbegin() is called on the graph") {
      auto it = g.cbegin();
      THEN("The iterator can be dereferenced to get the first element in edges_") {
        REQUIRE(std::get<0>(*it) == "a");
        REQUIRE(std::get<1>(*it) == "b");
        REQUIRE(std::get<2>(*it) == -3.4);
      }
    }
  }
}

// const_iterator begin()
SCENARIO("Calling begin() is the same as calling cbegin()") {
  GIVEN("A new const graph 'g' is created") {
    const std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    const std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    const std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    const std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    const std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    const std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    const auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                              tup4, tup5, tup6};
    const gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("begin() is called on the graph") {
      auto it = g.begin();
      THEN("The iterator can be dereferenced to get the first element in edges_") {
        REQUIRE(std::get<0>(*it) == "a");
        REQUIRE(std::get<1>(*it) == "b");
        REQUIRE(std::get<2>(*it) == -3.4);
      }
    }
  }
  GIVEN("A new non-const graph 'g' is created") {
    std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                       tup4, tup5, tup6};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("begin() is called on the graph") {
      auto it = g.begin();
      THEN("The iterator can be dereferenced to get the first element in edges_") {
        REQUIRE(std::get<0>(*it) == "a");
        REQUIRE(std::get<1>(*it) == "b");
        REQUIRE(std::get<2>(*it) == -3.4);
      }
    }
  }
}

// const_iterator cend()
SCENARIO("A graph has a const iterator that points to the end of the graph") {
  GIVEN("A new const graph 'g' is created") {
    const std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    const std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    const std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    const std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    const std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    const std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    const auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                             tup4, tup5, tup6};
    const gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("cend() is called on the graph") {
      auto it = g.cend();
      THEN("The iterator can be decremented to get the last element in the graph") {
        it = --it;
        REQUIRE(std::get<0>(*it) == "d");
        REQUIRE(std::get<1>(*it) == "a");
        REQUIRE(std::get<2>(*it) == 5.4);
      }
    }
  }
  GIVEN("A new non-const graph 'g' is created") {
    std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                       tup4, tup5, tup6};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("cend() is called on the graph") {
      auto it = g.cend();
      THEN("The iterator can be decremented to get the last element in the graph") {
        it = --it;
        REQUIRE(std::get<0>(*it) == "d");
        REQUIRE(std::get<1>(*it) == "a");
        REQUIRE(std::get<2>(*it) == 5.4);
      }
    }
  }
}

// const_iterator end()
SCENARIO("Calling end() using an iterator is the same as cend()") {
  GIVEN("A new const graph 'g' is created") {
    const std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    const std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    const std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    const std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    const std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    const std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    const auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                             tup4, tup5, tup6};
    const gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("end() is called on the graph") {
      auto it = g.end();
      THEN("The iterator can be decremented to get the last element in the graph") {
        it = --it;
        REQUIRE(std::get<0>(*it) == "d");
        REQUIRE(std::get<1>(*it) == "a");
        REQUIRE(std::get<2>(*it) == 5.4);
      }
    }
  }
  GIVEN("A new non-const graph 'g' is created") {
    std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                       tup4, tup5, tup6};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("end() is called on the graph") {
      auto it = g.end();
      THEN("The iterator can be decremented to get the last element in the graph") {
        it = --it;
        REQUIRE(std::get<0>(*it) == "d");
        REQUIRE(std::get<1>(*it) == "a");
        REQUIRE(std::get<2>(*it) == 5.4);
      }
    }
  }
}

// const_reverse_iterator crbegin()
SCENARIO("A graph has a reverse begin iterator that points to the last element") {
  GIVEN("A new const graph 'g' is created") {
    const std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    const std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    const std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    const std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    const std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    const std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    const auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                             tup4, tup5, tup6};
    const gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("crbegin() is called on the graph") {
      auto it = g.crbegin();
      THEN("The iterator can be dereferenced to get the last element in edges_") {
        REQUIRE(std::get<0>(*it) == "d");
        REQUIRE(std::get<1>(*it) == "a");
        REQUIRE(std::get<2>(*it) == 5.4);
      }
    }
  }
  GIVEN("A new non-const graph 'g' is created") {
    std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                       tup4, tup5, tup6};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("crbegin() is called on the graph") {
      auto it = g.crbegin();
      THEN("The iterator can be dereferenced to get the last element in edges_") {
        REQUIRE(std::get<0>(*it) == "d");
        REQUIRE(std::get<1>(*it) == "a");
        REQUIRE(std::get<2>(*it) == 5.4);
      }
    }
  }
}

// const_reverse_iterator crend()
SCENARIO("A graph has a reverse end iterator that points in front of the first element") {
  GIVEN("A new const graph 'g' is created") {
    const std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    const std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    const std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    const std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    const std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    const std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    const auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                             tup4, tup5, tup6};
    const gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("crend() is called on the graph") {
      auto it = g.crend();
      THEN("The iterator can be decremented to get the first element in edges_") {
        it = --it;
        REQUIRE(std::get<0>(*it) == "a");
        REQUIRE(std::get<1>(*it) == "b");
        REQUIRE(std::get<2>(*it) == -3.4);
      }
    }
  }
  GIVEN("A new non-const graph 'g' is created") {
    std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                       tup4, tup5, tup6};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("crend() is called on the graph") {
      auto it = g.crend();
      THEN("The iterator can be decremented to get the first element in edges_") {
        it = --it;
        REQUIRE(std::get<0>(*it) == "a");
        REQUIRE(std::get<1>(*it) == "b");
        REQUIRE(std::get<2>(*it) == -3.4);
      }
    }
  }
}

// const_reverse_iterator rbegin()
SCENARIO("Calling rbegin() is the same as crbegin()") {
  GIVEN("A new const graph 'g' is created") {
    const std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    const std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    const std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    const std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    const std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    const std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    const auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                             tup4, tup5, tup6};
    const gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("rbegin() is called on the graph") {
      auto it = g.rbegin();
      THEN("The iterator can be dereferenced to get the last element in edges_") {
        REQUIRE(std::get<0>(*it) == "d");
        REQUIRE(std::get<1>(*it) == "a");
        REQUIRE(std::get<2>(*it) == 5.4);
      }
    }
  }
  GIVEN("A new non-const graph 'g' is created") {
    std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                       tup4, tup5, tup6};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("rbegin() is called on the graph") {
      auto it = g.rbegin();
      THEN("The iterator can be dereferenced to get the last element in edges_") {
        REQUIRE(std::get<0>(*it) == "d");
        REQUIRE(std::get<1>(*it) == "a");
        REQUIRE(std::get<2>(*it) == 5.4);
      }
    }
  }
}

// const_reverse_iterator rend()
SCENARIO("Calling rend() is the same is crend()") {
  GIVEN("A new const graph 'g' is created") {
    const std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    const std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    const std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    const std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    const std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    const std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    const auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                             tup4, tup5, tup6};
    const gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("rend() is called on the graph") {
      auto it = g.rend();
      THEN("The iterator can be decremented to get the first element in edges_") {
        it = --it;
        REQUIRE(std::get<0>(*it) == "a");
        REQUIRE(std::get<1>(*it) == "b");
        REQUIRE(std::get<2>(*it) == -3.4);
      }
    }
  }
  GIVEN("A new non-const graph 'g' is created") {
    std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                       tup4, tup5, tup6};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("rend() is called on the graph") {
      auto it = g.rend();
      THEN("The iterator can be decremented to get the first element in edges_") {
        it = --it;
        REQUIRE(std::get<0>(*it) == "a");
        REQUIRE(std::get<1>(*it) == "b");
        REQUIRE(std::get<2>(*it) == -3.4);
      }
    }
  }
}

// Friend operator== and operator!=
SCENARIO("Two graphs can be compared using the == and != operators") {
  GIVEN("Two Equal Graphs") {
    char s1{'a'};
    char s2{'b'};
    char s3{'c'};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<char, char, double>>{e1, e2};
    gdwg::Graph<char, double> g1{e.begin(), e.end()};
    gdwg::Graph<char, double> g2{e.begin(), e.end()};
    WHEN("They are compared using the == operator") {
      bool result = (g1 == g2);
      THEN("The result should return true") { REQUIRE(result); }
    }
    WHEN("They are compared using the != operator") {
      bool result = (g1 != g2);
      THEN("The result should return false") { REQUIRE_FALSE(result); }
    }
  }
  GIVEN("Two graphs with same nodes but different edges") {
    char s1{'a'};
    char s2{'b'};
    char s3{'c'};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<char, char, double>>{e1, e2};
    gdwg::Graph<char, double> g1{e.begin(), e.end()};
    gdwg::Graph<char, double> g2{'a', 'b', 'c'};
    WHEN("They are compared using the == operator") {
      bool result = (g1 == g2);
      THEN("The result should return false") { REQUIRE_FALSE(result); }
    }
    WHEN("They are compared using the != operator") {
      bool result = (g1 != g2);
      THEN("The result should return true") { REQUIRE(result); }
    }
  }
  GIVEN("Two graphs with different nodes but same edge weights") {
    char s1{'a'};
    char s2{'b'};
    char s3{'c'};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<char, char, double>>{e1, e2};
    char t1{'d'};
    char t2{'e'};
    char t3{'f'};
    auto f1 = std::make_tuple(t1, t2, 5.4);
    auto f2 = std::make_tuple(t2, t3, 7.6);
    auto f = std::vector<std::tuple<char, char, double>>{f1, f2};
    gdwg::Graph<char, double> g1{e.begin(), e.end()};
    gdwg::Graph<char, double> g2{f.begin(), f.end()};
    WHEN("They are compared using the == operator") {
      bool result = (g1 == g2);
      THEN("The result should return false") { REQUIRE_FALSE(result); }
    }
    WHEN("They are compared using the != operator") {
      bool result = (g1 != g2);
      THEN("The result should return true") { REQUIRE(result); }
    }
  }
}

// Friend operator<<
SCENARIO("A graph can be printed out for the user") {
  GIVEN("A new const graph 'g' is created") {
    const std::tuple<std::string, std::string, double> tup1{"d", "a", 5.4};
    const std::tuple<std::string, std::string, double> tup2{"a", "b", -3.4};
    const std::tuple<std::string, std::string, double> tup3{"a", "b", 1.8};
    const std::tuple<std::string, std::string, double> tup4{"a", "c", 3.7};
    const std::tuple<std::string, std::string, double> tup5{"a", "c", 1.1};
    const std::tuple<std::string, std::string, double> tup6{"c", "a", 8.6};
    const auto e = std::vector<std::tuple<std::string, std::string, double>>{tup1, tup2, tup3,
                                                                             tup4, tup5, tup6};
    const gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    WHEN("the user calls std::cout << g") {
      std::ostringstream stream;
      stream << g;
      THEN("The graph is printed to screen") {
        REQUIRE(stream.str() == "a (\n  b | -3.4\n  b | 1.8\n  c | 1.1\n  c | 3.7\n)\nb (\n)\nc "
                                "(\n  a | 8.6\n)\nd (\n  a | 5.4\n)\n");
      }
    }
  }
  GIVEN("A new empty graph 'g' is created") {
    const gdwg::Graph<std::string, double> g;
    WHEN("the user calls std::cout << g") {
      std::ostringstream stream;
      stream << g;
      THEN("A newline is printed to screen") { REQUIRE(stream.str() == "\n"); }
    }
  }
  GIVEN("A graph with no connected nodes is printed") {
    gdwg::Graph<int, int> g{1, 2, 3};
    WHEN("the user calls std::cout << g") {
      std::ostringstream stream;
      stream << g;
      THEN("The graph is printed to screen") {
        REQUIRE(stream.str() == "1 (\n)\n2 (\n)\n3 (\n)\n");
      }
    }
  }
  GIVEN("A graph with 1 node and self edges is printed") {
    std::tuple<int, int, int> m1{1, 1, -1};
    std::tuple<int, int, int> m2{1, 1, 1};
    std::tuple<int, int, int> m3{1, 1, 2};
    std::tuple<int, int, int> m4{1, 1, -8};
    auto h = std::vector<std::tuple<int, int, int>>{m1, m2, m3, m4};
    gdwg::Graph<int, int> g{h.begin(), h.end()};
    WHEN("the user calls std::cout << g") {
      std::ostringstream stream;
      stream << g;
      THEN("The graph is printed to screen") {
        REQUIRE(stream.str() == "1 (\n  1 | -8\n  1 | -1\n  1 | 1\n  1 | 2\n)\n");
      }
    }
  }
}
