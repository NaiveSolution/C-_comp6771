#ifndef ASSIGNMENTS_DG_GRAPH_T_
#define ASSIGNMENTS_DG_GRAPH_T_

#include <algorithm>
#include <iostream>
#include <memory>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

/************** CONSTRUCTORS ******************/
// An alternate (input vector) constructor of the Graph Class.
// The input arguments are the end and beginning iterators to a vector<N> of length L,
// which returns a graph of nodes_ of size L with no edges.
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<N>::const_iterator start,
                         typename std::vector<N>::const_iterator finish) noexcept {
  // if the vector is empty, construct a default graph.
  // side note => vec.begin() == vec.end() is defined as an empty vector in C++11 onwards
  if (start == finish) {
    Graph();
  } else {
    std::vector<N> to_vector;
    std::copy(start, finish, std::back_inserter(to_vector));
    for (auto& N_element : to_vector) {
      Node new_node = {};
      new_node.value_ = N_element;
      this->nodes_.push_back(std::make_shared<Node>(new_node));
    }
  }
}
// An alternate (tuple) constructor of the Graph Class.
// The input arguments are the beginning and end of a vector of tuples each containing
// data of 2 nodes, src_ and dest_, connected with an edge of weight_.
// A variety of checks occur in the algorithm that determine the validity of each <src_, dest_, weight_>
// in each input tuple and what already exists in the graph.
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(
    typename std::vector<std::tuple<N, N, E>>::const_iterator start,
    typename std::vector<std::tuple<N, N, E>>::const_iterator finish) noexcept {
  if (start == finish) {
    Graph();
  } else {
    std::vector<std::tuple<N, N, E>> to_vector;
    std::copy(start, finish, std::back_inserter(to_vector));
    for (auto& N_element : to_vector) {
      bool exists_edge = false;
      bool exists_src = false;
      bool exists_dest = false;
      for (const auto& edge : edges_) {
        if (std::get<0>(N_element) == edge->src_.lock()->value_ &&
            std::get<1>(N_element) == edge->dest_.lock()->value_ &&
            std::get<2>(N_element) == edge->weight_) {
          exists_edge = true;
          break;
        }
      }
      if (exists_edge) {
        continue;
      }
      Edge new_edge = {};
      new_edge.weight_ = std::get<2>(N_element);
      for (const auto& node : nodes_) {
        if (node->value_ == std::get<0>(N_element)) {
          // Source node exists
          node->outdegree_++;
          new_edge.src_ = node;
          exists_src = true;
        }
        if (node->value_ == std::get<1>(N_element)) {
          // Dest node exists
          node->indegree_++;
          new_edge.dest_ = node;
          exists_dest = true;
        }
      }
      if (exists_src == false && std::get<0>(N_element) == std::get<1>(N_element)) {
        Node src_node = {};
        src_node.value_ = std::get<0>(N_element);
        src_node.outdegree_++;
        src_node.indegree_++;
        this->nodes_.push_back(std::make_shared<Node>(src_node));
        new_edge.src_ = this->nodes_.back();
        new_edge.dest_ = this->nodes_.back();
        this->edges_.push_back(std::make_shared<Edge>(new_edge));
        continue;
      }
      if (exists_src == false) {
        // Source node doesn't exist create new node
        Node src_node = {};
        src_node.value_ = std::get<0>(N_element);
        src_node.outdegree_++;
        this->nodes_.push_back(std::make_shared<Node>(src_node));
        new_edge.src_ = this->nodes_.back();
      }
      if (exists_dest == false) {
        // dest node doesn't exist create new node
        Node dest_node = {};
        dest_node.value_ = std::get<1>(N_element);
        dest_node.indegree_++;
        this->nodes_.push_back(std::make_shared<Node>(dest_node));
        new_edge.dest_ = this->nodes_.back();
      }
      this->edges_.push_back(std::make_shared<Edge>(new_edge));
    }
    std::sort(this->edges_.begin(), this->edges_.end(), CompareSort);
  }
}

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(std::initializer_list<N> list) noexcept {
  if (list.size() == 0) {
    Graph();
  } else {
    for (const auto& N_element : list) {
      Node new_node = {};
      new_node.value_ = N_element;
      this->nodes_.push_back(std::make_shared<Node>(new_node));
    }
  }
}

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(const gdwg::Graph<N, E>& copy) noexcept {
  this->nodes_ = copy.nodes_;
  this->edges_ = copy.edges_;
}

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(gdwg::Graph<N, E>&& tmp) noexcept {
  this->nodes_ = std::move(tmp.nodes_);
  this->edges_ = std::move(tmp.edges_);
}

/********************** OPERATORS **********************/
template <typename N, typename E>
gdwg::Graph<N, E>& gdwg::Graph<N, E>::operator=(const gdwg::Graph<N, E>& tmp) noexcept {
  this->nodes_ = tmp.nodes_;
  this->edges_ = tmp.edges_;
  return *this;
}

template <typename N, typename E>
gdwg::Graph<N, E>& gdwg::Graph<N, E>::operator=(gdwg::Graph<N, E>&& tmp) noexcept {
  this->nodes_ = std::move(tmp.nodes_);
  this->edges_ = std::move(tmp.edges_);
  return *this;
}

/************** METHODS ******************/
// Returns a vector of nodes_ that currently represent the graph.
template <typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetNodes() const {
  std::vector<N> to_vector;
  for (auto& element : this->nodes_) {
    to_vector.push_back(element.get()->value_);
  }
  std::sort(to_vector.begin(), to_vector.end());
  return to_vector;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertNode(const N& new_node) {
  if (IsNode(new_node)) {
    return false;
  }
  Node additional_node = {};
  additional_node.value_ = new_node;
  this->nodes_.push_back(std::make_shared<Node>(additional_node));
  return true;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertEdge(const N& src, const N& dest, const E& w) {
  if (!IsNode(src) || !IsNode(dest)) {
    throw std::runtime_error("Cannot call Graph::InsertEdge when "
                             "either src or dst node does not exist");
  }
  // if the edge between src->dst with weight w exists, return false
  for (const auto& edge : edges_) {
    if (edge->src_.lock()->value_ == src && edge->dest_.lock()->value_ == dest &&
        edge->weight_ == w) {
      return false;
    }
  }
  Edge new_edge = {};
  new_edge.weight_ = w;
  for (const auto& node : nodes_) {
    if (node->value_ == src) {
      node->outdegree_++;
      new_edge.src_ = node;
    }
    if (node->value_ == dest) {
      node->indegree_++;
      new_edge.dest_ = node;
    }
  }
  this->edges_.push_back(std::make_shared<Edge>(new_edge));
  std::sort(this->edges_.begin(), this->edges_.end(), CompareSort);
  return true;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::DeleteNode(const N& deleted_node) {
  if (!IsNode(deleted_node)) {
    return false;
  }

  for (auto it = edges_.begin(); it != edges_.end();) {
    if ((*it)->src_.lock()->value_ == deleted_node) {
      (*it)->dest_.lock()->indegree_--;
      (*it).reset();
      it = edges_.erase(it);
    } else {
      ++it;
    }
  }
  for (auto it = edges_.begin(); it != edges_.end();) {
    if ((*it)->dest_.lock()->value_ == deleted_node) {
      (*it)->src_.lock()->outdegree_--;
      (*it).reset();
      it = edges_.erase(it);
    } else {
      ++it;
    }
  }
  for (auto it = nodes_.begin(); it != nodes_.end(); ++it) {
    if ((*it)->value_ == deleted_node) {
      // auto i = &node - &nodes_[0];
      (*it).reset();
      nodes_.erase(it);
      break;
    }
  }
  // After every change to the edges_ vector of the graph, reshuffle the edges
  // using CompareSort.  
  std::sort(this->edges_.begin(), this->edges_.end(), CompareSort);
  return true;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::IsNode(const N& node) const noexcept {
  for (auto& element : this->nodes_) {
    if (node == element.get()->value_) {
      return true;
    }
  }
  return false;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::IsConnected(const N& src, const N& dest) const noexcept {
  for (const auto& edge : edges_) {
    if (edge->src_.lock()->value_ == src) {
      if (edge->dest_.lock()->value_ == dest) {
        return true;
      }
    }
  }
  return false;
}

template <typename N, typename E>
std::vector<E> gdwg::Graph<N, E>::GetWeights(const N& src, const N& dest) const {
  if (IsNode(src) == false || IsNode(dest) == false) {
    throw std::out_of_range("Cannot call Graph::GetWeights if src "
                            "or dst node don't exist in the graph");
  }
  std::vector<E> to_vector;
  for (auto& element : this->edges_) {
    if (element->src_.lock()->value_ == src && element->dest_.lock()->value_ == dest) {
      to_vector.push_back(element.get()->weight_);
    }
  }
  std::sort(to_vector.begin(), to_vector.end());
  return to_vector;
}

template <typename N, typename E>
void gdwg::Graph<N, E>::clear() noexcept {
  nodes_.clear();
  edges_.clear();
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::erase(const N& src, const N& dest, const E& w) {
  for (auto it = edges_.begin(); it != edges_.end(); ++it) {
    if ((*it)->src_.lock()->value_ == src && (*it)->dest_.lock()->value_ == dest &&
        (*it)->weight_ == w) {
      (*it)->src_.lock()->outdegree_--;
      (*it)->dest_.lock()->indegree_--;
      (*it).reset();
      edges_.erase(it);
      // After every change to the edges_ vector of the graph, reshuffle the edges
      // using CompareSort. 
      std::sort(this->edges_.begin(), this->edges_.end(), CompareSort);
      return true;
    }
  }
  return false;
}

template <typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetConnected(const N& src) const {
  if (!IsNode(src)) {
    throw std::out_of_range("Cannot call Graph::GetConnected "
                            "if src doesn't exist in the graph");
  }
  std::vector<N> new_vector;
  for (const auto& edge : edges_) {
    if (edge->src_.lock()->value_ == src) {
      new_vector.push_back(edge->dest_.lock()->value_);
    }
  }
  std::sort(new_vector.begin(), new_vector.end());
  return new_vector;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::Replace(const N& oldData, const N& newData) {
  if (!IsNode(oldData)) {
    throw std::runtime_error("Cannot call Graph::Replace on a node that doesn't exist");
  }
  if (IsNode(newData)) {
    return false;
  }
  for (auto& node : nodes_) {
    if (node->value_ == oldData) {
      node->value_ = newData;
      break;
    }
  }
  return true;
}

template <typename N, typename E>
void gdwg::Graph<N, E>::MergeReplace(const N& oldData, const N& newData) {
  if (!IsNode(oldData) || !IsNode(newData)) {
    throw std::runtime_error("Cannot call Graph::MergeReplace "
                             "on old or new data if they don't exist in the graph");
  }

  auto future_edges = GetWeights(newData, newData);

  // loop through nodes_, find the node we want to change to (newData)
  for (auto& node : nodes_) {
    if (node->value_ == newData) {
      // loop through edges_, replace all the src_ and dest_ nodes in each edge with newData
      for (const auto& edge : edges_) {
        if (edge->src_.lock()->value_ == oldData) {
          auto current_edge = edge->weight_;
          // if the edge of newData -> newData + weight already exists in the graph, the current
          // edge, oldData -> newData + weight, wont be inserted into the graph
          if (std::find(future_edges.begin(), future_edges.end(), current_edge) != future_edges.end())
            continue;
          edge->src_ = node;
          node->outdegree_++;
        }
        if (edge->dest_.lock()->value_ == oldData) {
          auto current_edge = edge->weight_;
          // as above
          if (std::find(future_edges.begin(), future_edges.end(), current_edge) != future_edges.end())
            continue;
          edge->dest_ = node;
          node->indegree_++;
        }
      }
      break;
    }
  }
  DeleteNode(oldData);
}

// CompareSort -- NOT IN SPECIFICATION --
// A function that is called as a lambda function to std::sort
// The function uses the properties of each node of type N's operator< overload.
// The function takes as an input two edges, a and b, where each edge has a {source, destination, weight}
// and will determine if the input edges need to be swapped - if they do, the function will return 
// a boolean that is itself an input to std::sort. The algorithm will return true if:
// 1) source_node(a) < source_node(b)
// 2) source_node(a) = source_node(b) AND dest_node(a) < dest_node(b)
// 3) source_node(a) = source_node(b) AND dest_node(a) = dest_node(b) AND weight(a) < weight(b)
// Returns false otherwise.
template <typename N, typename E>
bool gdwg::Graph<N, E>::CompareSort(const std::shared_ptr<Edge>& a,
                                    const std::shared_ptr<Edge>& b) {
  auto new_a = a.get();
  auto new_b = b.get();
  if (new_a->src_.lock()->value_ < new_b->src_.lock()->value_) {
    return true;
  }
  if (new_a->src_.lock()->value_ == new_b->src_.lock()->value_) {
    if (new_a->dest_.lock()->value_ < new_b->dest_.lock()->value_)
      return true;
    if (new_a->dest_.lock()->value_ == new_b->dest_.lock()->value_ &&
        new_a->weight_ < new_b->weight_)
      return true;
  }
  return false;
}

/************** ITERATORS ******************/
template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator& gdwg::Graph<N, E>::const_iterator::operator++() {
  ++iterator_;
  return *this;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator& gdwg::Graph<N, E>::const_iterator::operator--() {
  --iterator_;
  return *this;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::cbegin() const noexcept {
  const_iterator it;
  it.iterator_ = edges_.cbegin();
  it.end_iterator_ = edges_.cend();
  return it;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::cend() const noexcept {
  const_iterator it;
  it.iterator_ = edges_.cend();
  it.end_iterator_ = edges_.cend();
  return it;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::cbegin() noexcept {
  const_iterator it;
  it.iterator_ = edges_.cbegin();
  it.end_iterator_ = edges_.cend();
  return it;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::cend() noexcept {
  const_iterator it;
  it.iterator_ = edges_.cend();
  it.end_iterator_ = edges_.cend();
  return it;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator
gdwg::Graph<N, E>::find(const N& src, const N& dest, const E& weight) {
  const_iterator it;
  it.iterator_ = edges_.cbegin();
  it.end_iterator_ = edges_.cend();

  while (it.iterator_ != it.end_iterator_) {
    auto node = *(it.iterator_);
    if (node->src_.lock()->value_ == src && node->dest_.lock()->value_ == dest &&
        node->weight_ == weight) {
      break;
    }
    ++it.iterator_;
  }
  return it;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator
gdwg::Graph<N, E>::find(const N& src, const N& dest, const E& weight) const {
  const_iterator it;
  it.iterator_ = edges_.cbegin();
  it.end_iterator_ = edges_.cend();

  while (it.iterator_ != it.end_iterator_) {
    auto node = *(it.iterator_);
    if (node->src_.lock()->value_ == src && node->dest_.lock()->value_ == dest &&
        node->weight_ == weight) {
      break;
    }
    ++it.iterator_;
  }
  return it;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::erase(const_iterator old_it) {
  if (old_it.iterator_ == old_it.end_iterator_ || *old_it.iterator_ == nullptr) {
    return old_it;
  }
  N& erase_src = old_it.iterator_->get()->src_.lock()->value_;
  N& erase_dest = old_it.iterator_->get()->dest_.lock()->value_;
  E& erase_weight = old_it.iterator_->get()->weight_;

  // If the iterator is pointing to the last element already, delete it and return end()
  if ((old_it.iterator_ != old_it.end_iterator_) &&
      (next(old_it.iterator_) == old_it.end_iterator_)) {
    this->erase(erase_src, erase_dest, erase_weight);
    return this->end();
  }

  ++old_it.iterator_;
  N& new_src = old_it.iterator_->get()->src_.lock()->value_;
  N& new_dest = old_it.iterator_->get()->dest_.lock()->value_;
  E& new_weight = old_it.iterator_->get()->weight_;
  bool deleted = this->erase(erase_src, erase_dest, erase_weight);

  // If no erase can be made, the equivalent of gdwg::Graph<N, E>::end() is returned.
  if (deleted == false) {
    return this->end();
  }
  return this->find(new_src, new_dest, new_weight);
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_reverse_iterator& gdwg::Graph<N, E>::const_reverse_iterator::
operator++() {
  ++iterator_;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_reverse_iterator& gdwg::Graph<N, E>::const_reverse_iterator::
operator--() {
  --iterator_;
  return *this;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_reverse_iterator gdwg::Graph<N, E>::crbegin() noexcept {
  const_reverse_iterator it;
  it.iterator_ = edges_.crbegin();
  it.end_iterator_ = edges_.crend();
  return it;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_reverse_iterator gdwg::Graph<N, E>::crend() noexcept {
  const_reverse_iterator it;
  it.iterator_ = edges_.crend();
  it.end_iterator_ = edges_.crend();
  return it;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_reverse_iterator gdwg::Graph<N, E>::crbegin() const noexcept {
  const_reverse_iterator it;
  it.iterator_ = edges_.crbegin();
  it.end_iterator_ = edges_.crend();
  return it;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_reverse_iterator gdwg::Graph<N, E>::crend() const noexcept {
  const_reverse_iterator it;
  it.iterator_ = edges_.crend();
  it.end_iterator_ = edges_.crend();
  return it;
}

#endif  // ASSIGNMENTS_DG_GRAPH_T_
