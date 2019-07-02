#include "assignments/ev/euclidean_vector.h"

#include <algorithm>  // Look at these - they are helpful https://en.cppreference.com/w/cpp/algorithm

EuclideanVector::EuclideanVector(int x, double y) {
  this->num_dimensions_ = x;
  this->magnitudes_ = std::make_unique<double[]>(x);

  for (int i = 0; i != x; ++i){
    magnitudes_[i] = y;
  }
}

EuclideanVector::EuclideanVector(std::vector<double>::const_iterator front_it,
                                 std::vector<double>::const_iterator back_it) {

}