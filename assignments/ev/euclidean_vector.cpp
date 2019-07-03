#include "assignments/ev/euclidean_vector.h"

#include <algorithm>  // Look at these - they are helpful https://en.cppreference.com/w/cpp/algorithm

/********************* CONSTRUCTORS *************************************/
EuclideanVector::EuclideanVector(int x, double y) {
  this->num_dimensions_ = x;
  this->magnitudes_ = std::make_unique<double[]>(x);

  for (int i = 0; i != x; ++i){
    magnitudes_[i] = y;
  }
}

EuclideanVector::EuclideanVector(std::vector<double>::const_iterator start,
                                 std::vector<double>::const_iterator finish) {
  // if the iterators are from an empty vector
  if (start == finish) {
    this->num_dimensions_ = 1;
    this->magnitudes_ = std::make_unique<double[]>(1);
    this->magnitudes_.get()[0] = 0.0;
  } else {
    std::vector<double> to_vector;
    std::copy(start, finish, std::back_inserter(to_vector));

    this->magnitudes_ = std::make_unique<double[]>(to_vector.size());
    this->num_dimensions_ = to_vector.size();
    for (unsigned long i = 0; i != to_vector.size(); ++i){
      magnitudes_[i] = to_vector[i];
    }
  }

}

EuclideanVector::EuclideanVector(const EuclideanVector& original){
  this->num_dimensions_ = original.num_dimensions_;
  this->magnitudes_ = std::make_unique<double[]>(original.num_dimensions_);
  for (int i = 0; i < original.num_dimensions_; i++) {
    this->magnitudes_.get()[i] = original.magnitudes_.get()[i];
  }
}

/********************* METHODS *************************************/
double EuclideanVector::at(int index) {
  if (index < 0 || index >= this->num_dimensions_) {
    throw EuclideanVectorError("Index X is not valid for this EuclideanVector object");
  }
  return this->magnitudes_.get()[index];
}

double EuclideanVector::GetEuclideanNorm(){
  if (this->GetNumDimensions() == 0) {
    throw EuclideanVectorError("EuclideanVector with no dimensions does not have a norm");
  }
  double sum_of_squares = 0;
  for (int i = 0; i < this->num_dimensions_; i++)
  {
    sum_of_squares += std::pow(this->magnitudes_.get()[i], 2);
  }
  return std::sqrt(sum_of_squares);
}

EuclideanVector EuclideanVector::CreateUnitVector() {
  if (this->GetNumDimensions() == 0) {
      throw EuclideanVectorError("EuclideanVector with no dimensions does not have a unit vector" );
  }
  if (this->GetEuclideanNorm() == 0) {
    throw EuclideanVectorError("EuclideanVector with euclidean normal of 0 does not have a unit vector" );
  }
  std::vector<double> to_vector;
  double unit = this->GetEuclideanNorm();
  for (int i = 0; i < this->num_dimensions_; i++){
    to_vector.push_back((this->magnitudes_.get()[i])/unit);
  }
  return EuclideanVector(to_vector.begin(), to_vector.end());
}

/********************* FRIEND OVERLOADS *************************************/
EuclideanVector operator+(const EuclideanVector& lhs, const EuclideanVector& rhs){
  if (lhs.num_dimensions_ != rhs.num_dimensions_) {
    std::string error_message = "Dimensions of LHS(" + std::to_string(lhs.num_dimensions_) + ") and RHS(" + std::to_string(rhs.num_dimensions_) + ") do not match";
    throw EuclideanVectorError(error_message);
  }
  std::vector<double> to_vector;
  for (int i = 0; i < lhs.num_dimensions_; i++) {
      to_vector.push_back(lhs.magnitudes_.get()[i] + rhs.magnitudes_.get()[i]);
  }
  return EuclideanVector{to_vector.begin(), to_vector.end()};
}

// dot product multiplication
double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs){
  if (lhs.num_dimensions_ != rhs.num_dimensions_) {
    std::string error_message = "Dimensions of LHS(" + std::to_string(lhs.num_dimensions_) + ") and RHS(" + std::to_string(rhs.num_dimensions_) + ") do not match";
    throw EuclideanVectorError(error_message);
  }
  double sum = 0;
  for (int i = 0; i < lhs.num_dimensions_; i++) {
      sum = sum + (lhs.magnitudes_.get()[i] * rhs.magnitudes_.get()[i]);
  }
  return sum;
}

EuclideanVector operator*(const EuclideanVector& ev, const double& scalar){
  std::vector<double> to_vector;
  for (int i = 0; i < ev.num_dimensions_; i++) {
      to_vector.push_back(ev.magnitudes_.get()[i] * scalar);
  }
  return EuclideanVector{to_vector.begin(), to_vector.end()};
}

EuclideanVector operator*(const double& scalar, const EuclideanVector& ev){
  std::vector<double> to_vector;
  for (int i = 0; i < ev.num_dimensions_; i++) {
      to_vector.push_back(ev.magnitudes_.get()[i] * scalar);
  }
  return EuclideanVector{to_vector.begin(), to_vector.end()};
}

EuclideanVector operator/(const EuclideanVector& ev, const double& scalar){
  std::vector<double> to_vector;
  for (int i = 0; i < ev.num_dimensions_; i++) {
      to_vector.push_back(ev.magnitudes_.get()[i] / scalar);
  }
  return EuclideanVector{to_vector.begin(), to_vector.end()};
}

EuclideanVector operator-(const EuclideanVector& lhs, const EuclideanVector& rhs){
  if (lhs.num_dimensions_ != rhs.num_dimensions_) {
    std::string error_message = "Dimensions of LHS(" + std::to_string(lhs.num_dimensions_) + ") and RHS(" + std::to_string(rhs.num_dimensions_) + ") do not match";
    throw EuclideanVectorError(error_message);
  }
  std::vector<double> to_vector;
  for (int i = 0; i < lhs.num_dimensions_; i++) {
      to_vector.push_back(lhs.magnitudes_.get()[i] - rhs.magnitudes_.get()[i]);
  }
  return EuclideanVector{to_vector.begin(), to_vector.end()};
}

std::ostream& operator<<(std::ostream& os, const EuclideanVector& ev){
  os << "[";
  for (int i = 0; i < ev.num_dimensions_; i++){
    if (i == ev.num_dimensions_ - 1) {
      os << ev.magnitudes_.get()[i] << "]";
    } else {
      os << ev.magnitudes_.get()[i] << " ";
    }
  }
  return os;
}

bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs){
  if (lhs.num_dimensions_ != rhs.num_dimensions_) {
    return false;
  }
  for (int i = 0; i < lhs.num_dimensions_; i++) {
      if (lhs.magnitudes_.get()[i] != rhs.magnitudes_.get()[i]) {
        return false;
      }
  }
  return true;
}

bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs){
  if (lhs.num_dimensions_ == rhs.num_dimensions_) {
    return false;
  }
  for (int i = 0; i < lhs.num_dimensions_; i++) {
      if (lhs.magnitudes_.get()[i] == rhs.magnitudes_.get()[i]) {
        return false;
      }
  }
  return true;
}

/********************* OVERLOADS *************************************/
EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& ev) {
  if (this->num_dimensions_ != ev.num_dimensions_) {
      std::string error_message = "Dimensions of LHS(" + std::to_string(this->num_dimensions_) + ") and RHS(" + std::to_string(ev.num_dimensions_) + ") do not match";
      throw EuclideanVectorError(error_message);
    }
  for (int i = 0; i < this->num_dimensions_; i++) {
        this->magnitudes_.get()[i] = this->magnitudes_.get()[i] + ev.magnitudes_.get()[i];
  }
  return *this;
}

EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& ev) {
  if (this->num_dimensions_ != ev.num_dimensions_) {
      std::string error_message = "Dimensions of LHS(" + std::to_string(this->num_dimensions_) + ") and RHS(" + std::to_string(ev.num_dimensions_) + ") do not match";
      throw EuclideanVectorError(error_message);
    }
  for (int i = 0; i < this->num_dimensions_; i++) {
        this->magnitudes_.get()[i] = this->magnitudes_.get()[i] - ev.magnitudes_.get()[i];
  }
  return *this;
}