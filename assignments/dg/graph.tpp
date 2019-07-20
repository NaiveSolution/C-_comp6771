#ifndef ASSIGNMENTS_DG_GRAPH_T_
#define ASSIGNMENTS_DG_GRAPH_T_

#include <memory>
#include <iostream>
#include <unordered_set>
#include <vector>

template <typename N, typename E>
gdwg::Graph<N, E>::Graph() noexcept{
    Node empty_node = {};
    Edge empty_edge = {};
    this->nodes_.push_back(std::make_unique<Node>(empty_node));
    this->edges_.push_back(std::make_unique<Edge>(empty_edge));
};

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<N>::const_iterator start, typename std::vector<N>::const_iterator finish) noexcept{
    // if the vector is empty, construct a DG with 1 Node with an edge of 0 weight
    // side note -> vec.begin() == vec.end() is defined as an empty vector in C++11 onwards
    if (start == finish) {
        Node empty_node = {};
        Edge empty_edge = {};
        this->nodes_.push_back(std::make_unique<Node>(empty_node));
        this->edges_.push_back(std::make_unique<Edge>(empty_edge));
    } else {
        std::vector<N> to_vector;
        std::copy(start, finish, std::back_inserter(to_vector));
        for (auto& N_element : to_vector){
            Node new_node = {};
            new_node.value_ = N_element;
            this->nodes_.push_back(std::make_unique<Node>(new_node));
        }
    }
};

template <typename N, typename E>
gdwg::Graph<N,E>::Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator start,
      typename std::vector<std::tuple<N, N, E>>::const_iterator finish) noexcept{
    if (start == finish) {
        Graph();
    } else {
      std::unordered_set<N> existing_nodes;
      std::vector<std::tuple<N,N,E>> to_vector;
      std::copy(start, finish, std::back_inserter(to_vector));
      for (auto & N_element: to_vector) {
          Edge new_edge = {};
          new_edge.weight_ = N_element.at(0);
          for (const auto& n : nodes_) {
            if (n->value_ == N_element.at(0)) {
              // Node exists
              new_edge.src_ = n;
            }
          }

          //          if (existing_nodes.find(start[0]) == existing_nodes.end()) {
//              existing_nodes.insert(start[0]);
//              Node src_node = {};
//              src_node.value_ = start[0];
//              src_node.outdegree_++;
//              src_node.outedge_.push_back(new_edge);
//              new_edge.src_ = src_node;
//              this->nodes_.push_back(std::make_unique<Node>(src_node));
//          } else if (existing_nodes.find(start[0]) != existing_nodes.end()) {
//              nodes_
//          }
//          if (existing_nodes.find(start[1]) == existing_nodes) {
//              existing_nodes.insert(start[1]);
//              Node dest_node = {};
//              dest_node.value_ = start[1];
//              dest_node.indegree_++;
//              dest_node.inedge_.push_back(new_edge);
//              new_edge.dest_ = dest_node;
//              this->nodes_.push_back(std::make_unique<Node>(dest_node));
//          }
      }
    }
}

//#include "assignments/dg/graph.h"
//#include "graph.h"

#endif // ASSIGNMENTS_DG_GRAPH_T_
