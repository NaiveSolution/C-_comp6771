/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

*/

#include "assignments/dg/graph.h"
#include "catch.h"

// Constructors
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
    std::vector<std::string> v{"are", "how", "you"};
    gdwg::Graph<std::string, double> a{v.begin(),v.end()};
    WHEN("A new graph 'aCopy' is constructed using the copy constructor"){
      gdwg::Graph<std::string, double> aCopy{a};
      THEN("Graph aCopy will have the nodes {are, how ,you}"){
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

// Copy and move operators
SCENARIO("Graphs use copy and move equal operators") {
  GIVEN("Two existing graphs g1 & g2"){
    std::vector<std::string> v{"how", "are", "you"};
    gdwg::Graph<std::string, double> g1{v.begin(),v.end()};
    gdwg::Graph<std::string, double> g2;
    WHEN("The copy assignment operator is called g2 = g1"){
      g2 = g1;
      THEN("Graph g2 will have the nodes {are, how, you}"){
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

// IsNode()
SCENARIO("Graphs have existing nodes that can be checked for existance") {
  GIVEN("A Graph<int,int> g1") {
    gdwg::Graph<int,int> g1{1,2,3};
    WHEN("We check if node with value 1 exists in graph g1") {
      THEN("It will return true") {
        REQUIRE(g1.IsNode(1));
      }
    }
    WHEN("We check if node with value 0 exists in graph g1") {
      THEN("It will return false") {
        REQUIRE_FALSE(g1.IsNode(0));
      }
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
      THEN("It will return true") {
        REQUIRE(g.IsConnected('a','b'));
      }
    }
    WHEN("Checking whether node a->c") {
      THEN("It will return false as they are not connected") {
        REQUIRE_FALSE(g.IsConnected('a','c'));
      }
    }
    WHEN("Checking whether node b->a") {
      THEN("It will return false as a->b not b->a") {
        REQUIRE_FALSE(g.IsConnected('b','a'));
      }
    }
  }
}

// InsertNode()
SCENARIO("Given a graph 'a' and 'b' with strings for nodes, try and insert nodes"){
  GIVEN("A graph with some string nodes"){
    std::vector<std::string> v1{"a", "b", "z", "f"};
    std::vector<std::string> v2{"f", "o", "d"};
    gdwg::Graph<std::string, double> a{v1.begin(),v1.end()};
    gdwg::Graph<std::string, double> b{v2.begin(),v2.end()};
    WHEN("Trying to insert a node that doesnt exist in 'a'"){
      std::string str{"c"};
      a.InsertNode(str);
      THEN("Graph 'a' will have the nodes {a, b, c, f, z}"){
        std::vector<std::string> expected{"a", "b", "c", "f", "z"};
        REQUIRE(a.GetNodes() == expected);
      }
    }
    WHEN("Trying to insert a node that does exist in 'b'"){
      std::string str{"o"};
      b.InsertNode(str);
      THEN("Graph 'b' will have the nodes {d, f, o}"){
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
      THEN("The vector will contain the nodes {b,c}"){
        std::vector<char> expected{'b','c'};
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
        REQUIRE_THROWS_WITH(g.GetConnected('d'), "Cannot call "
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
        std::vector<double> expected{5.4,7.6};
        REQUIRE(g.GetWeights('a','b') == expected);
      }
    }
    WHEN("Trying to check weights between non-existant nodes") {
      THEN("An exception is thrown") {
        REQUIRE_THROWS_WITH(g.GetWeights('d','e'),
            "Cannot call Graph::GetWeights if src "
            "or dst node don't exist in the graph");
      }
    }
  }
}

// DeleteNode()
SCENARIO("Given a graph 'a' and 'b' with ints for nodes, try and delete nodes"){
  GIVEN("A graph with some int nodes"){
    std::vector<int> v1{1, 2, 3, 4};
    std::vector<int> v2{5, 6, 7};
    gdwg::Graph<int, double> a{v1.begin(),v1.end()};
    gdwg::Graph<int, double> b{v2.begin(),v2.end()};
    WHEN("Trying to delete a node that exists in 'a'"){
      a.DeleteNode(1);
      THEN("Graph 'a' will have the nodes {2, 3, 4}"){
        std::vector<int> expected{2, 3, 4};
        REQUIRE(a.GetNodes() == expected);
      }
    }
    WHEN("Trying to delete a node that doesnt exist in 'b'"){
      b.DeleteNode(8);
      THEN("Graph 'b' will have the nodes {5, 6, 7}"){
        std::vector<int> expected{5, 6, 7};
        REQUIRE(b.GetNodes() == expected);
      }
    }
  }
  GIVEN("A graph with some int nodes and edge weights"){
    int s1 = 1;
    int s2 = 2;
    int s3 = 3;
    int s4 = 4;
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e3 = std::make_tuple(s3, s4, 8.3);
    auto e = std::vector<std::tuple<int, int, double>>{e1, e2, e3};
    gdwg::Graph<int, double> g{e.begin(), e.end()};
    WHEN("Trying to delete a node that exists in 'g'"){
      g.DeleteNode(s1);
      THEN("Graph 'g' will have the nodes {2, 3, 4}"){
        std::vector<int> expected{2, 3, 4};
        REQUIRE(g.GetNodes() == expected);
      }
      THEN("Graph 'g' will have the edges {7.6, 8.3}"){
        REQUIRE(g.GetWeights(2, 3)[0] == 7.6);
        REQUIRE(g.GetWeights(3, 4)[0] == 8.3);
      }
    }

  }
}

// InsertEdge() may need to further test????
SCENARIO("A Graph with existing nodes can insert new edges") {
  GIVEN("A graph with some char nodes") {
    gdwg::Graph<char,int> g{'a','b','c'};
    WHEN("An edge is inserted a->b with weight 2") {
      g.InsertEdge('a','b',2);
      THEN("There will be an edge from a->b") {
        REQUIRE(g.IsConnected('a','b'));
      }
      AND_THEN("No edge from b->a") {
        REQUIRE_FALSE(g.IsConnected('b','a'));
      }
    }
    WHEN("An edge is inserted from a non-exisiting node to 'a'") {
      THEN("An exception should be thrown") {
        REQUIRE_THROWS_WITH(g.InsertEdge('d','a',3),"Cannot call "
      "Graph::InsertEdge when either src or dst node does not exist");
      }
    }
  }
}

// Clear() --> not sure how to check if all edges are removed
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
      THEN("There should be no nodes") {
        REQUIRE(g.GetNodes().empty());
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
      REQUIRE(g.erase('a','b',5.4));
      THEN("It will not exist in the graph anymore") {
        REQUIRE(g.GetWeights('a','b').empty());
      }
    }
    WHEN("An edge that does not exist is removed a->c") {
      REQUIRE_FALSE(g.erase('a', 'c', 5.4));
      THEN("No changes are made to existing edges") {
        std::vector<double> ab{5.4};
        std::vector<double> bc{7.6};
        REQUIRE(g.GetWeights('a','b') == ab);
        REQUIRE(g.GetWeights('b','c') == bc);
      }
    }
  }
}

// Replace()
SCENARIO("A graph can replace nodes") {
  GIVEN("A Graph 'g' with some char nodes (a,b,c)") {
    std::vector<char> v{'a','b','c'};
    gdwg::Graph<char, int> g{v.begin(), v.end()};
    g.InsertEdge('a','b',1);
    g.InsertEdge('c','a',2);
    WHEN("The node 'a' is replaced with 'z'") {
      g.Replace('a','z');
      THEN("The graph 'g' is changed from (a,b,c) to (b,c,z)"){
        std::vector<char> expected{'b', 'c', 'z'};
        REQUIRE(g.GetNodes() == expected);
      }
      AND_THEN("Node z is connected to b with weights 1") {
        std::vector<char> expected_connection{'b'};
        std::vector<int> expected_weights{1};
        REQUIRE(g.GetConnected('z') == expected_connection);
        REQUIRE(g.GetWeights('z','b') == expected_weights);
      }
      AND_THEN("Node c is connected to z with weights 2") {
        std::vector<char> expected_connection{'z'};
        std::vector<int> expected_weights{2};
        REQUIRE(g.GetConnected('c') == expected_connection);
        REQUIRE(g.GetWeights('c','z') == expected_weights);
      }
    }
    WHEN("A node is replaced with a node that already exists") {
      auto result = g.Replace('a','b');
      THEN("The function will return false") {
        REQUIRE_FALSE(result);
      }
    }
    WHEN("A node that does not exist in 'g' is replaced") {
      THEN("No changes are made to existing nodes in graph 'g'") {
        REQUIRE_THROWS_WITH(g.Replace('f','g'),
            "Cannot call Graph::Replace on a node that doesn't exist");
      }
    }
  }
}

// MergeReplace()
SCENARIO("A graph can merge replace nodes") {
  GIVEN("A graph with char nodes and int edges") {
    std::vector<char> v{'a','b','c'};
    gdwg::Graph<char, int> g{v.begin(), v.end()};
    g.InsertEdge('a','b',1);
    g.InsertEdge('c','a',2);
    WHEN("Node 'b' merge replaces node 'a'") {
      g.MergeReplace('a','b');
      THEN("Node b will be connected to itself") {
        std::vector<char> expected{'b'};
        REQUIRE(g.GetConnected('b') == expected);
      }
      AND_THEN("c->b with weights 2") {
        std::vector<int> expected{2};
        REQUIRE(g.GetWeights('c','b') == expected);
      }
      AND_THEN("Graph g will have nodes {b,c}") {
        std::vector<char> expected{'b','c'};
        REQUIRE(g.GetNodes() == expected);
      }
    }
    WHEN("Node 'a' is merge replaced with 'd'") {
      THEN("An exception is thrown as Node d does not exist") {
        REQUIRE_THROWS_WITH(g.MergeReplace('a','d'),
          "Cannot call Graph::MergeReplace "
          "on old or new data if they don't exist in the graph");
      }
    }
    WHEN("Node 'd' is merge replaced with 'a'") {
      THEN("An exception is thrown as Node d does not exist") {
        REQUIRE_THROWS_WITH(g.MergeReplace('d','a'),
          "Cannot call Graph::MergeReplace "
          "on old or new data if they don't exist in the graph");
      }
    }
  }
}


/*
 * Additional test ideas:
 *  - Test for edge that connects to the same node (a->a)
 *    - Test for getConnected etc.
 */