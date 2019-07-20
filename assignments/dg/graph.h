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

#include "assignments/dg/graph.tpp"
//#include "graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
