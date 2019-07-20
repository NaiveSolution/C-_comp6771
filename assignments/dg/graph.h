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
#include <ostream>
#include <vector>

namespace gdwg {

template<typename N, typename E>
class Graph {
 public:
  Graph() noexcept;
  Graph(typename std::vector<N>::const_iterator, typename std::vector<N>::const_iterator) noexcept;
  Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator,
      typename std::vector<std::tuple<N, N, E>>::const_iterator) noexcept;

  std::vector<N> GetNodes() const noexcept;

 private:
  struct Node;
  struct Edge;

  /* Node data structure that stores a generic value,
   * incoming and outgoing edges, in and out degrees
   */
  struct Node {
    N value_;
    std::vector<std::shared_ptr<Edge>> inedge_;
    std::vector<std::shared_ptr<Edge>> outedge_;
    int indegree_ = 0;
    int outdegree_ = 0;
  };

  /* Edge data structure that stores a generic weight,
   * source and destination nodes.
   */
  struct Edge {
    E weight_;
    std::weak_ptr<Node> src_;
    std::weak_ptr<Node> dest_;
  };

  std::vector<std::shared_ptr<Node>> nodes_;
  std::vector<std::shared_ptr<Edge>> edges_;
};
// Define your graph_iterator here
// Define your graph_const_iterator here

}

#include "assignments/dg/graph.tpp"
//#include "graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
