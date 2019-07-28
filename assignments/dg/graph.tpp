#ifndef ASSIGNMENTS_DG_GRAPH_T_
#define ASSIGNMENTS_DG_GRAPH_T_

#include <algorithm>
#include <memory>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

/************** CONSTRUCTORS ******************/
template <typename N, typename E>
gdwg::Graph<N, E>::Graph() noexcept{
    Node empty_node = {};
    Edge empty_edge = {};
    this->nodes_.push_back(std::make_shared<Node>(empty_node));
    this->edges_.push_back(std::make_shared<Edge>(empty_edge));
}

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<N>::const_iterator start,
    typename std::vector<N>::const_iterator finish) noexcept{
    // if the vector is empty, construct a DG with 1 Node with an edge of 0 weight
    // side note -> vec.begin() == vec.end() is defined as an empty vector in C++11 onwards
    if (start == finish) {
      Graph();
    } else {
        std::vector<N> to_vector;
        std::copy(start, finish, std::back_inserter(to_vector));
        for (auto& N_element : to_vector){
            Node new_node = {};
            new_node.value_ = N_element;
            this->nodes_.push_back(std::make_shared<Node>(new_node));
        }
    }
}

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator start,
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

template<typename N, typename E>
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

template<typename N, typename E>
gdwg::Graph<N, E>::Graph(const gdwg::Graph<N, E>& copy) noexcept{
  this->nodes_ = copy.nodes_;
  this->edges_ = copy.edges_;
}

template<typename N, typename E>
gdwg::Graph<N,E>::Graph(gdwg::Graph<N, E>&& tmp) noexcept {
  this->nodes_ = std::move(tmp.nodes_);
  this->edges_ = std::move(tmp.edges_);
}

/********************** OPERATORS **********************/

template<typename N,typename E>
gdwg::Graph<N,E>& gdwg::Graph<N,E>::operator=(const gdwg::Graph<N, E>& tmp) noexcept {
  this->nodes_ = tmp.nodes_;
  this->edges_ = tmp.edges_;
  return *this;
}

template<typename N,typename E>
gdwg::Graph<N,E>& gdwg::Graph<N,E>::operator=(gdwg::Graph<N, E>&& tmp) noexcept {
  this->nodes_ = std::move(tmp.nodes_);
  this->edges_ = std::move(tmp.edges_);
  return *this;
}

/************** METHODS ******************/

template<typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetNodes() const{
    std::vector<N> to_vector;
    for (auto& element : this->nodes_){
        to_vector.push_back(element.get()->value_);
    }
    std::sort(to_vector.begin(), to_vector.end());
    return to_vector;
}

template<typename N, typename E>
bool gdwg::Graph<N, E>::InsertNode(const N& new_node){
    if (IsNode(new_node)){
        return false;
    }
    Node additional_node = {};
    additional_node.value_ = new_node;
    this->nodes_.push_back(std::make_shared<Node>(additional_node));
    return true;
}

template<typename N, typename E>
bool gdwg::Graph<N, E>::InsertEdge(const N& src, const N& dest, const E& w) {
  if (IsNode(src) == false || IsNode(dest) == false) {
    throw std::runtime_error("Cannot call Graph::InsertEdge when "
                             "either src or dst node does not exist");
  }
  for (const auto& edge : edges_) {
    if(edge->src_.lock()->value_ == src &&
      edge->dest_.lock()->value_ == dest &&
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

template<typename N, typename E>
bool gdwg::Graph<N, E>::DeleteNode(const N& deleted_node){
    if (!IsNode(deleted_node)){
        return false;
    }

    for (auto it = edges_.begin(); it != edges_.end();){
      if ((*it)->src_.lock()->value_ == deleted_node) {
          (*it)->dest_.lock()->indegree_--;
          (*it).reset();
          edges_.erase(it);
      }
      if ((*it)->dest_.lock()->value_ == deleted_node) {
        (*it)->src_.lock()->outdegree_--;
        (*it).reset();
        edges_.erase(it);
      }
      else {
        ++it;
      }
    }

    for (auto it = nodes_.begin(); it != nodes_.end();){
        if ((*it)->value_ == deleted_node){
            //auto i = &node - &nodes_[0];
            (*it).reset();
            nodes_.erase(it);
            break;
        } else {
          ++it;
        }
    }
    std::sort(this->edges_.begin(), this->edges_.end(), CompareSort);
    return true;
}

template<typename N, typename E>
bool gdwg::Graph<N, E>::IsNode(const N& node) const noexcept {
  for (auto& element : this->nodes_){
    if (node == element.get()->value_) {
      return true;
    }
  }
  return false;
}

template<typename N, typename E>
bool gdwg::Graph<N, E>::IsConnected(const N& src,
    const N& dest) const noexcept {
  for (const auto& edge : edges_) {
    if (edge->src_.lock()->value_ == src) {
      if (edge->dest_.lock()->value_ == dest) {
        return true;
      }
    }
  }
  return false;
}

template<typename N, typename E>
std::vector<E> gdwg::Graph<N, E>::GetWeights(const N& src, const N& dest) const{
    if (IsNode(src) == false || IsNode(dest) == false) {
      throw std::out_of_range("Cannot call Graph::GetWeights if src "
                              "or dst node don't exist in the graph");
    }
    std::vector<E> to_vector;
    for (auto& element : this->edges_){
        if (element->src_.lock()->value_ == src && element->dest_.lock()->value_ == dest){
            to_vector.push_back(element.get()->weight_);
        }
    }
    std::sort(to_vector.begin(), to_vector.end());
    return to_vector;
}

template<typename N, typename E>
void gdwg::Graph<N,E>::clear() noexcept {
  nodes_.clear();
  edges_.clear();
}

template<typename N,typename E>
bool gdwg::Graph<N,E>::erase(const N& src, const N& dest, const E& w) {
  for (auto it = edges_.begin(); it != edges_.end(); ++it) {
    if ((*it)->src_.lock()->value_ == src
        && (*it)->dest_.lock()->value_ == dest
        && (*it)->weight_ == w) {
      (*it)->src_.lock()->outdegree_--;
      (*it)->dest_.lock()->indegree_--;
      (*it).reset();
      edges_.erase(it);
      std::sort(this->edges_.begin(), this->edges_.end(), CompareSort);
      return true;
    }
  }
  return false;
}

template<typename N, typename E>
std::vector<N> gdwg::Graph<N,E>::GetConnected(const N& src) const {
  if (IsNode(src) == false) {
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

template<typename N, typename E>
bool gdwg::Graph<N,E>::Replace(const N& oldData, const N& newData) {
  if (IsNode(oldData) == false) {
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

template<typename N, typename E>
void gdwg::Graph<N,E>::MergeReplace(const N& oldData, const N& newData) {
  if (IsNode(oldData) == false ||
      IsNode(newData) == false) {
    throw std::runtime_error("Cannot call Graph::MergeReplace "
       "on old or new data if they don't exist in the graph");
  }
  for (auto& node : nodes_) {
    if (node->value_ == newData) {
      for (const auto& edge : edges_) {
        if (edge->src_.lock()->value_ == oldData) {
          edge->src_ = node;
          node->indegree_++;
        }
        if (edge->dest_.lock()->value_ == oldData) {
          edge->dest_ = node;
          node->outdegree_++;
        }
      }
      break;
    }
  }
  DeleteNode(oldData);
}

// NOT IN SPEC
template<typename N, typename E>
bool gdwg::Graph<N,E>::CompareSort(const std::shared_ptr<Edge>& a, const std::shared_ptr<Edge>& b){
  auto new_a = a.get();
  auto new_b = b.get();
  if (new_a->src_.lock()->value_ < new_b->src_.lock()->value_){
    return true;
  }
  if (new_a->src_.lock()->value_ == new_b->src_.lock()->value_){
    if (new_a->dest_.lock()->value_ < new_b->dest_.lock()->value_)
      return true;
    if (new_a->dest_.lock()->value_ == new_b->dest_.lock()->value_ &&  new_a->weight_ < new_b->weight_)
      return true;
  }
  return false;
}

// NOT IN SPEC
template<typename N, typename E>
void gdwg::Graph<N,E>::PrintEdges(){
  std::cout << "vector of edges before sorting: " << std::endl;
  for (const auto& i : this->edges_){
    std::cout << (*i).src_.lock()->value_ << "-" << (*i).dest_.lock()->value_ << "-" << (*i).weight_ << std::endl;
  }
  std::cout << "vector of edges after sorting: " << std::endl;
  std::sort(this->edges_.begin(), this->edges_.end(), CompareSort);
  for (const auto& i : this->edges_){
    std::cout << (*i).src_.lock()->value_ << "-" << (*i).dest_.lock()->value_ << "-" << (*i).weight_ << std::endl;
  }
}

/************** FRIENDS ******************/




/************** ITERATORS ******************/
template<typename N, typename E>
typename gdwg::Graph<N,E>::const_iterator& gdwg::Graph<N,E>::const_iterator::operator++() {
  ++iterator_;
  return *this;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator& gdwg::Graph<N, E>::const_iterator::operator--(){
  --iterator_;
  return *this;
}

template<typename N, typename E>
typename gdwg::Graph<N,E>::const_iterator gdwg::Graph<N,E>::cbegin() noexcept{
  const_iterator it;
  it.iterator_ =  edges_.cbegin();
  it.end_iterator_ = edges_.cend();
  return it;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N,E>::cend() noexcept{
  const_iterator it;
  it.iterator_ =  edges_.cend();
  it.end_iterator_ = edges_.cend();
  return it;
}

template<typename N, typename E>
typename gdwg::Graph<N,E>::const_reverse_iterator& gdwg::Graph<N,E>::const_reverse_iterator::operator++() {
  ++iterator_;
  return *this;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_reverse_iterator& gdwg::Graph<N, E>::const_reverse_iterator::operator--(){
  --iterator_;
  return *this;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_reverse_iterator gdwg::Graph<N,E>::crbegin() noexcept{
  const_reverse_iterator it;
  it.iterator_ =  edges_.crbegin();
  it.end_iterator_ = edges_.crend();
  return it;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_reverse_iterator gdwg::Graph<N,E>::crend() noexcept{
  const_reverse_iterator it;
  it.iterator_ =  edges_.crend();
  it.end_iterator_ = edges_.crend();
  return it;
}

#endif // ASSIGNMENTS_DG_GRAPH_T_
