// TODO(you): Include header guards

#include <exception>
#include <string>
#include <memory>
#include <vector>
#include <cmath>
#include <iostream>

class EuclideanVectorError : public std::exception {

 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept{ return what_.c_str(); }

 private:
  std::string what_;
};

class EuclideanVector {

 public:
  // constructors
  explicit EuclideanVector(int i = 1) : EuclideanVector(i, 0.0){} // default
  EuclideanVector(int x, double y); // alternate
  EuclideanVector(std::vector<double>::const_iterator, std::vector<double>::const_iterator ); // alternate
  EuclideanVector(const EuclideanVector&);  // copy
  //EuclideanVector(EuclideanVector&&); // move

  // friend overloads
  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);
  friend EuclideanVector operator+(const EuclideanVector&, const EuclideanVector&);
  friend double operator*(const EuclideanVector&, const EuclideanVector&);
  friend EuclideanVector operator*(const EuclideanVector&, const double&);
  friend EuclideanVector operator*(const double&, const EuclideanVector&);
  friend EuclideanVector operator/(const EuclideanVector&, const double&);
  friend EuclideanVector operator-(const EuclideanVector&, const EuclideanVector&);
  friend bool operator==(const EuclideanVector&, const EuclideanVector&);
  friend bool operator!=(const EuclideanVector&, const EuclideanVector&);

  // overloads
  EuclideanVector& operator+=(const EuclideanVector& ev);
  EuclideanVector& operator-=(const EuclideanVector& ev);

  // methods
  int GetNumDimensions() { return num_dimensions_;}
  double at(int);
  double GetEuclideanNorm();
  EuclideanVector CreateUnitVector();

 private:
  int num_dimensions_;
  std::unique_ptr<double[]> magnitudes_;


};
