/*
* Written by Tariq Mosaval for the University of New South Wales 
* for the course Advanced C++ Programming
* 
* This file contains the class description for a Euclidean Vector: 
* a geometric object that has a magnitude and direction. An Euclidean Vector (EV)
* can be added, subtracted and multiplied to other EVs  in accordance to vector algebra,
* and can be scaled with a scalar value in terms of their magnitudes.
*
* Contained in this header file is the class methods that are used to achieve the abovenamed
* functions, among many others, including the option to print a vector using the << operator,
* the option to access particular elements in the vector using [] subscripts, and methods
* which are used in determining the unit vector from an EV, and calculating a
* value which is normal to the EV.
* 
* Descriptions of each class method and overload can be found in the corresponding .cpp file
*/

#ifndef ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
#define ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_

#include <cassert>
#include <cmath>
#include <exception>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept { return what_.c_str(); }

 private:
  std::string what_;
};

// Creates a new Euclidean Vector as described in the licence above
// Example:
//  EuclideanVector a{1,2,3}; Euclidean Vector b{2,4,6};
//  EuclideanVector c = a + b;
//  std::cout << c;
// Outputs -> [3, 6, 9]
class EuclideanVector {
 public:
  /************** constructors ******************/
  // The default constructor for an EV has 1 dimension and this dimension has a magnitude of 0
  explicit EuclideanVector(int i = 1) : EuclideanVector(i, 0.0) {}

  // The alternate constructor uses the input arguments (x, y) to create a vector with
  // x dimensions and sets all the magnitudes for each dimension to y
  EuclideanVector(int x, double y) noexcept;

  // Should the user wish to create an EV from a vector<double> with length L and magnitudes m_1, m_2 ... m_k
  // this alternate constructor can be used to create an EV of dimensions L and set the magnitude of
  // each dimension in the EV to m_1 ... m_k. This constructor requires the beginning and end iterators of a vector<double>
  EuclideanVector(std::vector<double>::const_iterator,
                  std::vector<double>::const_iterator) noexcept;
  
  // The copy constructor of the EV class
  EuclideanVector(const EuclideanVector&) noexcept;

  // The move constructor of the EV class   
  EuclideanVector(EuclideanVector&&) noexcept;
  ~EuclideanVector() = default;

  /************** friend overloads ******************/
  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) noexcept;
  friend EuclideanVector operator+(const EuclideanVector&, const EuclideanVector&);
  friend double operator*(const EuclideanVector&, const EuclideanVector&);
  friend EuclideanVector operator*(const EuclideanVector&, const double&) noexcept;
  friend EuclideanVector operator*(const double&, const EuclideanVector&) noexcept;
  friend EuclideanVector operator/(const EuclideanVector&, const double&);
  friend EuclideanVector operator-(const EuclideanVector&, const EuclideanVector&);
  friend bool operator==(const EuclideanVector&, const EuclideanVector&) noexcept;
  friend bool operator!=(const EuclideanVector&, const EuclideanVector&) noexcept;

  /************** operations ******************/
  EuclideanVector& operator+=(const EuclideanVector&);
  EuclideanVector& operator-=(const EuclideanVector&);
  EuclideanVector& operator*=(const double&) noexcept;
  EuclideanVector& operator/=(const double&);
  EuclideanVector& operator=(const EuclideanVector&) noexcept;
  EuclideanVector& operator=(EuclideanVector&&) noexcept;
  double& operator[](int);
  const double& operator[](int) const;
  explicit operator std::vector<double>() const noexcept;
  explicit operator std::list<double>() const noexcept;

  /************** methods ******************/
  int GetNumDimensions() noexcept { return num_dimensions_; }
  double& at(const int&);
  double at(const int&) const;
  double GetEuclideanNorm() const;
  EuclideanVector CreateUnitVector() const;

 private:
 /************** private members ******************/
  int num_dimensions_;
  std::unique_ptr<double[]> magnitudes_;
};

#endif  // ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
