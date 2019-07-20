#ifndef ASSIGNMENTS_DG_GRAPH_T_
#define ASSIGNMENTS_DG_GRAPH_T_

#include <memory>
#include <iostream>
#include <unordered_set>
#include <vector>

/************** CONSTRUCTORS ******************/
template <typename N, typename E>
gdwg::Graph<N, E>::Graph() noexcept{
    Node empty_node = {};
    Edge empty_edge = {};
    this->nodes_.push_back(std::make_shared<Node>(empty_node));
    this->edges_.push_back(std::make_shared<Edge>(empty_edge));
};

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<N>::const_iterator start, typename std::vector<N>::const_iterator finish) noexcept{
    // if the vector is empty, construct a DG with 1 Node with an edge of 0 weight
    // side note -> vec.begin() == vec.end() is defined as an empty vector in C++11 onwards
    if (start == finish) {
        Node empty_node = {};
        Edge empty_edge = {};
        this->nodes_.push_back(std::make_shared<Node>(empty_node));
        this->edges_.push_back(std::make_shared<Edge>(empty_edge));
    } else {
        std::vector<N> to_vector;
        std::copy(start, finish, std::back_inserter(to_vector));
        for (auto& N_element : to_vector){
            Node new_node = {};
            new_node.value_ = N_element;
            this->nodes_.push_back(std::make_shared<Node>(new_node));
        }
    }
};

template <typename N, typename E>
gdwg::Graph<N,E>::Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator start,
      typename std::vector<std::tuple<N, N, E>>::const_iterator finish) noexcept {
  if (start == finish) {
    Graph();
  } else {
    std::vector<std::tuple<N, N, E>> to_vector;
    std::copy(start, finish, std::back_inserter(to_vector));
    for (auto& N_element : to_vector) {
      bool exists_src = false;
      bool exists_dest = false;
      Edge new_edge = {};
      new_edge.weight_ = std::get<2>(N_element);
      for (const auto& node : nodes_) {
        if (node->value_ == std::get<0>(N_element)) {
          // Source node exists
          node->outdegree_++;
          node->outedge_.push_back(std::make_shared<Edge>(new_edge));
          new_edge.src_ = node;
          exists_src = true;
        }
        if (node->value_ == std::get<1>(N_element)) {
          // Dest node exists
          node->indegree_++;
          node->inedge_.push_back(std::make_shared<Edge>(new_edge));
          new_edge.dest_ = node;
          exists_dest = true;
        }
      }
//      if (exists_dest == false) {
//        // Source node doesn't exist create new node
//        Node src_node = {};
//        src_node.value_ = start[0];
//        src_node.outdegree_++;
//        src_node.outedge_.push_back(new_edge);
//        this->nodes_.push_back(std::make_shared<Node>(src_node));
//        new_edge.src_ = this->nodes_.back();
//      }
//      if (exists_src == false) {
//        // dest node doesn't exist create new node
//        Node dest_node = {};
//        dest_node.value_ = start[1];
//        dest_node.indegree_++;
//        dest_node.inedge_.push_back(new_edge);
//        new_edge.dest_ = dest_node;
//        this->nodes_.push_back(std::make_shared<Node>(dest_node));
//        new_edge.dest_ = this->nodes_.back();
//      }
//      this->edges_.push_back(std::make_shared<Edge>(new_edge));
    }
  }
}
// more constructors...

/************** METHODS ******************/

template <typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetNodes() const noexcept{
    std::vector<N> to_vector;
    for (auto& element : this->nodes_){
        to_vector.push_back(element.get()->value_);
    }
    return to_vector;
}

//#include "assignments/dg/graph.h"
//#include "graph.h"

#endif // ASSIGNMENTS_DG_GRAPH_T_
