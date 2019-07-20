/*
* Written by Tariq Mosaval and Jimmy Lin for the University of New South Wales 
* for the course Advanced C++ Programming
* 
* This file contains the class description for a Directed Weighted Graph: 
* a <description> object that has <some properties>. A Directed Weighted Graph (DG)
* can be <operations of graphs> in accordance to graph theory,
* and can be <other things that graphs can do>.
*
* Contained in this header file is the class methods that are used to achieve the abovenamed
* functions, among many others, including the option to <other thing it can do>,
* <another thing it can do>, and methods that <that do some other things, particular to our graph>
* 
* Descriptions of each class method and overload can be found in the corresponding .tpp file
*/

#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <memory>
#include <vector>

namespace gdwg {

template<typename N, typename E>
class Graph {
 public:
  Graph() noexcept;
  Graph(typename std::vector<N>::const_iterator, typename std::vector<N>::const_iterator) noexcept;
  //Graph(std::vector<std::tuple<N, N, E>>::const_iterator, std::vector<std::tuple<N, N, E>>::const_iterator) noexcept;

  std::vector<N> GetNodes() const noexcept;

 private:
  struct Node;
  struct Edge;

  /* Node data structure that stores a generic value,
   * incoming and outgoing edges, in and out degrees
   */
  struct Node {
    N value_;
    std::vector<Edge> inedge_;
    std::vector<Edge> outedge_;
    int indegree_;
    int outdegree_;
  };

  /* Edge data structure that stores a generic weight,
   * source and destination nodes.
   */
  struct Edge {
    E weight_;
    Node src_;
    Node dest_;
  };

  std::vector<std::unique_ptr<Node>> nodes_;
  std::vector<std::unique_ptr<Edge>> edges_;
};
// Define your graph_iterator here
// Define your graph_const_iterator here

}

//#include "assignments/dg/graph.tpp"
#include "graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
