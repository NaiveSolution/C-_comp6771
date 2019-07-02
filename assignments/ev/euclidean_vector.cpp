#include "assignments/ev/euclidean_vector.h"

#include <algorithm>  // Look at these - they are helpful https://en.cppreference.com/w/cpp/algorithm

EuclideanVector::EuclideanVector(int x, double y) {
  this->num_dimensions_ = x;
  this->magnitudes_ = std::make_unique<double[]>(x);

  for (int i = 0; i != x; ++i){
    magnitudes_[i] = y;
  }
}

EuclideanVector::EuclideanVector(std::vector<double>::const_iterator start,
                                 std::vector<double>::const_iterator finish) {
  std::vector<double> to_vector;
  std::copy(start, finish, std::back_inserter(to_vector));
  
  this->magnitudes_ = std::make_unique<double[]>(to_vector.size());
  this->num_dimensions_ = to_vector.size();
  for (unsigned long i = 0; i != to_vector.size(); ++i){
    magnitudes_[i] = to_vector[i];
  }
}

EuclideanVector::EuclideanVector(const EuclideanVector& original){
  this->num_dimensions_ = original.num_dimensions_;

  for (int i = 0; i < original.num_dimensions_; i++)
  {
    this->magnitudes_.get()[i] = original.magnitudes_.get()[i];
  }

}