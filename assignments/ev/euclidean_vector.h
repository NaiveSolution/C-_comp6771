// TODO(you): Include header guards

#include <exception>
#include <string>
#include <memory>
#include <vector>

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
  explicit EuclideanVector(int i = 1) : EuclideanVector(i, 0.0){}
  EuclideanVector(int x, double y);
  EuclideanVector(std::vector<double>::const_iterator, std::vector<double>::const_iterator );
  EuclideanVector(const EuclideanVector&);
  EuclideanVector(EuclideanVector&&);

  // overloads
  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);
  friend EuclideanVector operator+(const EuclideanVector& lhs, const EuclideanVector& rhs);

  // methods
  int GetNumDimensions();

 private:
  int num_dimensions_;
  std::unique_ptr<double[]> magnitudes_;


};
/*

EuclideanVector operator+(const EuclideanVector& lhs, const EuclideanVector& rhs){

}

int EuclideanVector::GetNumDimensions() {

}*/
