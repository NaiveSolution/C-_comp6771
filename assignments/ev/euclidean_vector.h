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

class EuclideanVector {
 public:
  // constructors
  explicit EuclideanVector(int i = 1) : EuclideanVector(i, 0.0) {}  // default
  EuclideanVector(int x, double y) noexcept;                        // alternate
  EuclideanVector(std::vector<double>::const_iterator,
                  std::vector<double>::const_iterator) noexcept;  // alternate
  EuclideanVector(const EuclideanVector&) noexcept;               // copy
  EuclideanVector(EuclideanVector&&) noexcept;                    // move
  ~EuclideanVector() = default;                                   // destructor

  // friend overloads
  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) noexcept;
  friend EuclideanVector operator+(const EuclideanVector&, const EuclideanVector&);
  friend double operator*(const EuclideanVector&, const EuclideanVector&);
  friend EuclideanVector operator*(const EuclideanVector&, const double&) noexcept;
  friend EuclideanVector operator*(const double&, const EuclideanVector&) noexcept;
  friend EuclideanVector operator/(const EuclideanVector&, const double&);
  friend EuclideanVector operator-(const EuclideanVector&, const EuclideanVector&);
  friend bool operator==(const EuclideanVector&, const EuclideanVector&) noexcept;
  friend bool operator!=(const EuclideanVector&, const EuclideanVector&) noexcept;

  // overloads and operations
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

  // methods
  int GetNumDimensions() noexcept { return num_dimensions_; }
  double& at(const int&);
  double at(const int&) const;
  double GetEuclideanNorm() const;
  EuclideanVector CreateUnitVector() const;

 private:
  int num_dimensions_;
  std::unique_ptr<double[]> magnitudes_;
};

#endif  // ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
