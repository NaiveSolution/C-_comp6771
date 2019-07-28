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

 public:

  /********************** ITERATOR **********************/
  class graph_iterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::tuple<N, N, E>;
    using reference = std::tuple<const N&, const N&, const E&>;
    using pointer = std::tuple<N,N,E>*;
    using difference_type = int;

    reference operator*() const { return *iterator_;}
    reference operator*();

    // Preincrement
    graph_iterator& operator++();
    // Post increment
    graph_iterator operator++(int) {
      auto copy{*this};
      ++(*this);
      return copy;
    }

    pointer operator->() const { return &(operator*());}

    friend bool operator==(const graph_iterator& lhs, const graph_iterator& rhs) {
      return lhs.iterator_ == rhs.iterator_ && lhs.iterator_ == lhs.end_iterator_;
    }

    friend bool operator!=(const graph_iterator& lhs, const graph_iterator& rhs) {
      return !(lhs == rhs);
    }

   private:
    friend class Graph<N,E>;
    typename std::vector<std::shared_ptr<Edge>>::iterator iterator_;
    typename std::vector<std::shared_ptr<Edge>>::iterator end_iterator_;
  };

  graph_iterator begin();
  graph_iterator end();

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
  void PrintEdges();
  static bool CompareSort(const std::shared_ptr<Edge>&, const std::shared_ptr<Edge>&);


 private:
  std::vector<std::shared_ptr<Node>> nodes_;
  std::vector<std::shared_ptr<Edge>> edges_;
};

}

//#include "assignments/dg/graph.tpp"
#include "graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
