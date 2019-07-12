#include "assignments/ev/euclidean_vector.h"

#include <algorithm>

/********************* CONSTRUCTORS *************************************/
// The default constructor of EuclideanVector.
// The default constructor assigns the arguments x and y to the class members
// num_dimensions_ and magnitudes_ respectively. A unique pointer is assigned to 
// a c-style array of double, of length x, and is assigned all values of y.
EuclideanVector::EuclideanVector(int x, double y) noexcept{
  this->num_dimensions_ = x;
  this->magnitudes_ = std::make_unique<double[]>(x);

  for (int i = 0; i != x; ++i) {
    magnitudes_[i] = y;
  }
}

// An alternate constructor of the EuclideanVector Class.
// The input arguments are the end and beginning iterators to a vector<double> of length L,
// which returns an EV of num_dimensions_ = L and a c-style array of magnitudes
// from each element in the vector.
EuclideanVector::EuclideanVector(std::vector<double>::const_iterator start,
                                 std::vector<double>::const_iterator finish) noexcept{
  // if the vector is empty, construct an EV with 1 dimension with a magnitude of 0
  if (start == finish) {
    this->num_dimensions_ = 1;
    this->magnitudes_ = std::make_unique<double[]>(1);
    this->magnitudes_.get()[0] = 0.0;
  } else {
    std::vector<double> to_vector;
    std::copy(start, finish, std::back_inserter(to_vector));

    this->magnitudes_ = std::make_unique<double[]>(to_vector.size());
    this->num_dimensions_ = to_vector.size();
    for (int i = 0; i != num_dimensions_; ++i) {
      magnitudes_[i] = to_vector[i];
    }
  }
}

// Returns a deep copy of a EuclideanVector.
// A new c-style array of magnitudes with size equal to the input EV is allocated
EuclideanVector::EuclideanVector(const EuclideanVector& original) noexcept{
  this->num_dimensions_ = original.num_dimensions_;
  this->magnitudes_ = std::make_unique<double[]>(original.num_dimensions_);
  for (int i = 0; i < original.num_dimensions_; i++) {
    this->magnitudes_.get()[i] = original.magnitudes_.get()[i];
  }
}

// Returns a copy of the target EV, and puts the target EV into a valid but
// unspecified state with 0 dimensions and deallocates the magnitudes_ array
EuclideanVector::EuclideanVector(EuclideanVector&& original) noexcept {
  this->magnitudes_ = std::move(original.magnitudes_);
  this->num_dimensions_ = original.num_dimensions_;
  original.num_dimensions_ = 0;
}

/********************* METHODS *************************************/

// Returns the magnitude in the [index] position of the magnitudes_ array.
// Throws an EuclideanVectorException exception if the [index] is out of bounds of the EV.
double& EuclideanVector::at(const int& index) {
  if (index < 0 || index >= this->num_dimensions_) {
    std::string error_message = "Index " + std::to_string(index) + " is not valid for this EuclideanVector object";
    throw EuclideanVectorError(error_message);
  }
  return this->magnitudes_.get()[index];
}

// As the above function, but is used for const EuclideanVector(s) that cannot be changed
double EuclideanVector::at(const int& index) const{
  if (index < 0 || index >= this->num_dimensions_) {
    throw EuclideanVectorError("Index X is not valid for this EuclideanVector object");
  }
  return this->magnitudes_.get()[index];
}

// Returns a value which is normal of the EV given by the root of the sum of squares
// of its magnitudes.
double EuclideanVector::GetEuclideanNorm() const{
  if (this->num_dimensions_ == 0) {
    throw EuclideanVectorError("EuclideanVector with no dimensions does not have a norm");
  }
  double sum_of_squares = 0;
  for (int i = 0; i < this->num_dimensions_; i++) {
    sum_of_squares += std::pow(this->magnitudes_.get()[i], 2);
  }
  return std::sqrt(sum_of_squares);
}

// Returns a new EuclideanVector that is the unit vector of the target EV.
// The target EV is not modified as the function is const qualified.
EuclideanVector EuclideanVector::CreateUnitVector() const{
  if (this->num_dimensions_ == 0) {
    throw EuclideanVectorError("EuclideanVector with no dimensions does not have a unit vector");
  }
  if (this->GetEuclideanNorm() == 0) {
    throw EuclideanVectorError(
        "EuclideanVector with euclidean normal of 0 does not have a unit vector");
  }
  std::vector<double> to_vector;
  to_vector.reserve(this->num_dimensions_);
  double unit = this->GetEuclideanNorm();
  for (int i = 0; i < this->num_dimensions_; i++) {
    to_vector.push_back((this->magnitudes_.get()[i]) / unit);
  }
  return EuclideanVector(to_vector.begin(), to_vector.end());
}

/********************* FRIEND OVERLOADS *************************************/

// Operator overload of + to add two EVs together.
// The function will throw a EuclideanVectorError exception if the dimensions of each EV arent equal.
// The alternate constructor is used to return an EV as a new vector<double> is created
// within the function that contains the element by element summation of each magnitude.
EuclideanVector operator+(const EuclideanVector& lhs, const EuclideanVector& rhs) {
  if (lhs.num_dimensions_ != rhs.num_dimensions_) {
    std::string error_message = "Dimensions of LHS(" + std::to_string(lhs.num_dimensions_) +
                                ") and RHS(" + std::to_string(rhs.num_dimensions_) +
                                ") do not match";
    throw EuclideanVectorError(error_message);
  }
  std::vector<double> to_vector;
  to_vector.reserve(lhs.num_dimensions_);
  for (int i = 0; i < lhs.num_dimensions_; i++) {
    to_vector.push_back(lhs.magnitudes_.get()[i] + rhs.magnitudes_.get()[i]);
  }
  return EuclideanVector{to_vector.begin(), to_vector.end()};
}

// Dot product multiplication overloaded operator *.
// The function will throw a EuclideanVectorError exception if the dimensions of each EV arent equal.
// Returns the summation of each element by element multiplication of two EVs.
double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs) {
  if (lhs.num_dimensions_ != rhs.num_dimensions_) {
    std::string error_message = "Dimensions of LHS(" + std::to_string(lhs.num_dimensions_) +
                                ") and RHS(" + std::to_string(rhs.num_dimensions_) +
                                ") do not match";
    throw EuclideanVectorError(error_message);
  }
  double sum = 0;
  for (int i = 0; i < lhs.num_dimensions_; i++) {
    sum = sum + (lhs.magnitudes_.get()[i] * rhs.magnitudes_.get()[i]);
  }
  return sum;
}

// Scalar product multiplication of an EV and a double using overloaded operator *.
// The alternate constructor is used to return an EV as a new vector<double> is created
// within the function that contains the element by element product of each magnitude with the input scalar value.
EuclideanVector operator*(const EuclideanVector& ev, const double& scalar) noexcept{
  std::vector<double> to_vector;
  to_vector.reserve(ev.num_dimensions_);
  for (int i = 0; i < ev.num_dimensions_; i++) {
    to_vector.push_back(ev.magnitudes_.get()[i] * scalar);
  }
  return EuclideanVector{to_vector.begin(), to_vector.end()};
}

// As the above function, but accounts for the multiplicand on the other side of the EV
EuclideanVector operator*(const double& scalar, const EuclideanVector& ev) noexcept{
  std::vector<double> to_vector;
  to_vector.reserve(ev.num_dimensions_);
  for (int i = 0; i < ev.num_dimensions_; i++) {
    to_vector.push_back(ev.magnitudes_.get()[i] * scalar);
  }
  return EuclideanVector{to_vector.begin(), to_vector.end()};
}

// Scalar division of an EV.
// The alternate constructor is used to return an EV as a new vector<double> is created
// within the function that contains the element by element division of each magnitude with the input scalar value. 
EuclideanVector operator/(const EuclideanVector& ev, const double& scalar) {
  if (scalar == 0) {
    throw EuclideanVectorError("Invalid vector division by 0");
  }
  std::vector<double> to_vector;
  to_vector.reserve(ev.num_dimensions_);
  for (int i = 0; i < ev.num_dimensions_; i++) {
    to_vector.push_back(ev.magnitudes_.get()[i] / scalar);
  }
  return EuclideanVector{to_vector.begin(), to_vector.end()};
}

// Scalar subtraction of an EV.
// The function will throw a EuclideanVectorError exception if the dimensions of each EV arent equal.
// The alternate constructor is used to return an EV as a new vector<double> is created
// within the function that contains the element by element subtraction between two EVs.
EuclideanVector operator-(const EuclideanVector& lhs, const EuclideanVector& rhs) {
  if (lhs.num_dimensions_ != rhs.num_dimensions_) {
    std::string error_message = "Dimensions of LHS(" + std::to_string(lhs.num_dimensions_) +
                                ") and RHS(" + std::to_string(rhs.num_dimensions_) +
                                ") do not match";
    throw EuclideanVectorError(error_message);
  }
  std::vector<double> to_vector;
  to_vector.reserve(lhs.num_dimensions_);
  for (int i = 0; i < lhs.num_dimensions_; i++) {
    to_vector.push_back(lhs.magnitudes_.get()[i] - rhs.magnitudes_.get()[i]);
  }
  return EuclideanVector{to_vector.begin(), to_vector.end()};
}

// Returns an output stream that can be used to display an EV through std::cout
std::ostream& operator<<(std::ostream& os, const EuclideanVector& ev) noexcept{
  os << "[";
  // if the EV has 0 dimensions, then display an empty bracket
  if (ev.num_dimensions_ == 0) {
    os << "]";
    return os;
  }
  for (int i = 0; i < ev.num_dimensions_; i++) {
    if (i == ev.num_dimensions_ - 1) {
      os << ev.magnitudes_.get()[i] << "]";
    } else {
      os << ev.magnitudes_.get()[i] << " ";
    }
  }
  return os;
}

// Overloaded operator of == for two EVs.
// Returns true if both sides of the == operator have the same num_dimensions_ and if
// each element[n] in their magnitudes_ array is equal. Returns false otherwise.
bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs) noexcept {
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

// Overloaded operator of != for two EVs.
// Returns true if both sides of the != operator have different num_dimensions_.
// The function will also return true if each element[n] in their magnitudes_ array is not equal.
// Returns false otherwise.
bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs) noexcept {
  if (lhs.num_dimensions_ != rhs.num_dimensions_) {
    return true;
  }
  for (int i = 0; i < lhs.num_dimensions_; i++) {
    if (lhs.magnitudes_.get()[i] == rhs.magnitudes_.get()[i]) {
      return false;
    }
  }
  return true;
}

/********************* OVERLOADS *************************************/

// Operator overload of += to add two EVs together.
// The function will throw a EuclideanVectorError exception if the dimensions of each EV arent equal.
// The original EV is overwritten while the second operand is unchanged.
EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& ev) {
  if (this->num_dimensions_ != ev.num_dimensions_) {
    std::string error_message = "Dimensions of LHS(" + std::to_string(this->num_dimensions_) +
                                ") and RHS(" + std::to_string(ev.num_dimensions_) +
                                ") do not match";
    throw EuclideanVectorError(error_message);
  }
  for (int i = 0; i < this->num_dimensions_; i++) {
    this->magnitudes_.get()[i] = this->magnitudes_.get()[i] + ev.magnitudes_.get()[i];
  }
  return *this;
}

// Operator overload of -= to subtract two EVs together.
// The function will throw a EuclideanVectorError exception if the dimensions of each EV arent equal.
// The original EV is overwritten while the second operand is unchanged.
EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& ev) {
  if (this->num_dimensions_ != ev.num_dimensions_) {
    std::string error_message = "Dimensions of LHS(" + std::to_string(this->num_dimensions_) +
                                ") and RHS(" + std::to_string(ev.num_dimensions_) +
                                ") do not match";
    throw EuclideanVectorError(error_message);
  }
  for (int i = 0; i < this->num_dimensions_; i++) {
    this->magnitudes_.get()[i] = this->magnitudes_.get()[i] - ev.magnitudes_.get()[i];
  }
  return *this;
}

// Operator overload of *= to multiply an EV with a scalar value.
// The original EV is overwritten.
EuclideanVector& EuclideanVector::operator*=(const double& scalar) noexcept{
  std::vector<double> to_vector;
  for (int i = 0; i < this->num_dimensions_; i++) {
    this->magnitudes_.get()[i] = this->magnitudes_.get()[i] * scalar;
  }
  return *this;
}

// Operator overload of /= to divide an EV with a scalar value.
// The original EV is overwritten.
EuclideanVector& EuclideanVector::operator/=(const double& scalar) {
  if (scalar == 0) {
    throw EuclideanVectorError("Invalid vector division by 0");
  }
  std::vector<double> to_vector;
  for (int i = 0; i < this->num_dimensions_; i++) {
    this->magnitudes_.get()[i] = this->magnitudes_.get()[i] / scalar;
  }
  return *this;
}

// Operator overload of = to copy assign a new EV from an existing one.
// The original EV is overwritten with the new properties of the target EV.
// The pointer to the magnitudes_ array is released and destroyed, and a new
// unique pointer is created and filled with the magnitudes of the target EV.
EuclideanVector& EuclideanVector::operator=(const EuclideanVector& copy) noexcept {
  if (&copy == this)
    return *this;
  if (num_dimensions_ != copy.num_dimensions_) {
    magnitudes_.reset();
    num_dimensions_ = copy.num_dimensions_;
  }
  magnitudes_ = std::make_unique<double[]>(num_dimensions_);
  for (int i = 0; i < this->num_dimensions_; i++) {
    magnitudes_.get()[i] = copy.magnitudes_.get()[i];
  }
  return *this;
}

// Operator overload of = to move construct a new EV from an existing one.
// The target EV has its properties set to an unspecified but valid state, its
// ownership of the pointer to the magnitudes_ array is transferred to the target,
// and its num_dimensions_ is set to 0.
EuclideanVector& EuclideanVector::operator=(EuclideanVector&& mv) noexcept {
  magnitudes_ = std::move(mv.magnitudes_);
  num_dimensions_ = mv.num_dimensions_;
  mv.num_dimensions_ = 0;
  return *this;
}

// Operator overload of [] to access a particular [index] of an EVs magnitudes_ array.
// The function will crash the program if the user attempts to access an element in the magnitudes_
// array that is out of bounds through the usage of a c-style assert.
// This function is used to SET the value in the given index.
double& EuclideanVector::operator[](int index) {
  assert(index >= 0 && index < this->num_dimensions_);
  return this->magnitudes_[index];
}

// Operator overload of [] to access a particular [index] of an EVs magnitudes_ array.
// The function will crash the program if the user attempts to access an element in the magnitudes_
// array that is out of bounds through the usage of a c-style assert.
// This function is used to GET the value in the given index.
const double& EuclideanVector::operator[](int index) const{
  assert(index >= 0 && index < this->num_dimensions_);
  return this->magnitudes_[index];
}

// This function performs the inverse of the alternate constructor, and returns a
// std::vector<double> from a given EuclideanVector.
EuclideanVector::operator std::vector<double>() const noexcept{
  std::vector<double> to_vector(&this->magnitudes_[0],
                                &this->magnitudes_[0] + this->num_dimensions_);
  return to_vector;
}

// This function performs the inverse of the alternate constructor, and returns a
// std::list<double> from a given EuclideanVector.
EuclideanVector::operator std::list<double>() const noexcept{
  std::list<double> to_list(&this->magnitudes_[0], &this->magnitudes_[0] + this->num_dimensions_);
  return to_list;
}
