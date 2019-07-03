/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

*/

#include "assignments/ev/euclidean_vector.h"
#include "catch.h"


TEST_CASE("Testing the default constructor", "[constructor]"){
  EuclideanVector a{4,5.5};
  EuclideanVector b{};
  EuclideanVector c{10};

  REQUIRE(a.GetNumDimensions() == 4);
  REQUIRE(a.at(0) == 5.5);

  REQUIRE(b.GetNumDimensions() == 1);
  REQUIRE(b.at(0) == 0.0);

  REQUIRE(c.GetNumDimensions() == 10);
  REQUIRE(c.at(0) == 0.0);
}

TEST_CASE("Testing the copy constructor", "[copy_constructor]"){
  EuclideanVector a{10, 6.8};
  EuclideanVector b{a};

  EuclideanVector c{};
  EuclideanVector d{c};

  REQUIRE(b.GetNumDimensions() == a.GetNumDimensions());
  REQUIRE(b.at(0) == 6.8);
  REQUIRE(b.at(9) == 6.8);

  REQUIRE(d.GetNumDimensions() == c.GetNumDimensions());
  REQUIRE(d.at(0) == 0.0);
}

TEST_CASE("Testing the iterator constructor", "[iterator_constructor]"){
  std::vector<double> v1{1,2,3,4,5,6};
  std::vector<double> v2{1};
  std::vector<double> v3{};

  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};
  EuclideanVector c{v3.begin(), v3.end()};

  REQUIRE(a.GetNumDimensions() == 6);
  REQUIRE(a.at(2) == 3);

  REQUIRE(b.GetNumDimensions() == 1);
  REQUIRE(b.at(0) == 1);

  REQUIRE(c.GetNumDimensions() == 1);
  REQUIRE(c.at(0) == 0.0);
}

TEST_CASE("Testing the at method", "[at()]"){
  std::vector<double> v1{1,2,3,4,5,6};
  EuclideanVector a{v1.begin(), v1.end()};

  REQUIRE_THROWS_WITH(a.at(-1), "Index X is not valid for this EuclideanVector object");
  REQUIRE_THROWS_WITH(a.at(7), "Index X is not valid for this EuclideanVector object");
}

TEST_CASE("Testing the GetEuclideanNorm method", "[Get Norm]"){
  std::vector<double> v1{4, 3};

  EuclideanVector a{v1.begin(), v1.end()};
  REQUIRE(a.GetEuclideanNorm() == 5);

}