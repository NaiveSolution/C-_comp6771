#ifndef ASSIGNMENTS_DG_GRAPH_T_
#define ASSIGNMENTS_DG_GRAPH_T_

#include <memory>
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
            this->nodes_.pushback(std::make_unique<Node>(new_node));
        }

    }

};


//#include "assignments/dg/graph.h"
#include "graph.h"

#endif // ASSIGNMENTS_DG_GRAPH_T_
