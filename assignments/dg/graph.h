/*
* Written by Tariq Mosaval and Jimmy Lin, the University of New South Wales, 
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
 /********************** CONSTRUCTORS **********************/
  Graph() noexcept;
  Graph(typename std::vector<N>::const_iterator, typename std::vector<N>::const_iterator) noexcept;
  Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator,
      typename std::vector<std::tuple<N, N, E>>::const_iterator) noexcept;
  Graph(std::initializer_list<N>) noexcept;
  Graph(const Graph&) noexcept;
  Graph(Graph&&) noexcept;
  ~Graph() = default;

  /********************** OPERATORS **********************/
  Graph& operator=(const gdwg::Graph<N, E>&) noexcept;
  Graph& operator=(gdwg::Graph<N, E>&&) noexcept;




  /********************** METHODS **********************/
  bool InsertEdge(const N&, const N&, const E&);
  bool IsNode(const N&) const noexcept;
  bool IsConnected(const N&, const N&) const noexcept;
  std::vector<N> GetNodes() const;
  bool InsertNode(const N&);
  bool DeleteNode(const N&);
  std::vector<N> GetConnected(const N&) const;
  std::vector<E> GetWeights(const N&, const N&) const;
  void clear() noexcept;
  bool erase(const N&, const N&, const E&);
  bool Replace(const N&, const N&);
  void MergeReplace(const N&, const N&);

 private:
  struct Node;
  struct Edge;

  /* Node data structure that stores a generic value,
   * incoming and outgoing edges, in and out degrees
   */
  struct Node {
    N value_;
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

//#include "assignments/dg/graph.tpp"
#include "graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
