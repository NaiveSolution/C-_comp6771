/*

  Since we are testing class functionality only, testing all (most) functions and methods
  separately is the best approach as the class design is highly modular. Testing of simple
  1 liner methods, such as GetNumDimensions(), doesnt really need to be tested as it is
  trivial. Overloaded operators, on the other hand, require significantly more testing than
  the other methods as there is more flexibility (and hence possibilities of exceptions)
  with the choices of operands.

  Testing of all components was done with the outlying cases in mind; inputs of 0, of no inputs,
  of negative inputs and out of bounds inputs. It is assumed that basic and valid inputs will not,
  or should not, throw errors/exceptions in terms of constructors or methods.

  Testing of overloaded operators generally involves testing when two valid, but unusual operands
  are used in the assignment, such as - two EVs with 0 dimensions, two EVs with negative values,
  two EVs where one has no magnitudes.

  Where an exception can be thrown by a method, it has a test case written for it.

*/

#include "assignments/ev/euclidean_vector.h"
#include "catch.h"

TEST_CASE("Testing the default constructor", "[constructor]") {
  EuclideanVector a{4, 5.5};
  EuclideanVector b{};
  EuclideanVector c{10};

  REQUIRE(a.GetNumDimensions() == 4);
  REQUIRE(a.at(0) == 5.5);

  REQUIRE(b.GetNumDimensions() == 1);
  REQUIRE(b.at(0) == 0.0);

  REQUIRE(c.GetNumDimensions() == 10);
  REQUIRE(c.at(0) == 0.0);
}

TEST_CASE("Testing the copy constructor", "[copy_constructor]") {
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

TEST_CASE("Testing the iterator constructor", "[iterator_constructor]") {
  std::vector<double> v1{1, 2, 3, 4, 5, 6};
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

TEST_CASE("Testing the move constructor", "[move_constructor]") {
  std::vector<double> v1{1, 2, 3, 4, 5, 6};
  std::vector<double> v2{1};
  std::vector<double> v3{};

  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};
  EuclideanVector c{v3.begin(), v3.end()};

  EuclideanVector move_a{std::move(a)};
  EuclideanVector move_b{std::move(b)};
  EuclideanVector move_c{std::move(c)};

  REQUIRE(a.GetNumDimensions() == 0);
  REQUIRE(b.GetNumDimensions() == 0);
  REQUIRE(c.GetNumDimensions() == 0);

  REQUIRE(move_a.GetNumDimensions() == 6);
  REQUIRE(move_b.GetNumDimensions() == 1);
  REQUIRE(move_c.GetNumDimensions() == 1);

  REQUIRE(move_a.at(2) == 3);
  REQUIRE(move_b.at(0) == 1);
  REQUIRE(move_c.at(0) == 0.0);
}

TEST_CASE("Testing the at() method", "[at()]") {
  std::vector<double> v1{1, 2, 3, 4, 5, 6};
  EuclideanVector a{v1.begin(), v1.end()};

  REQUIRE(a.at(1) == 2);
  REQUIRE(a.at(2) == 3);
  REQUIRE(a.at(3) == 4);

  REQUIRE_THROWS_WITH(a.at(-1), "Index X is not valid for this EuclideanVector object");
  REQUIRE_THROWS_WITH(a.at(7), "Index X is not valid for this EuclideanVector object");
}

TEST_CASE("Testing the GetEuclideanNorm() method", "[Get Norm]") {
  std::vector<double> v1{4, 3};
  std::vector<double> v2{4, 3, 3, 1, 1};
  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};
  EuclideanVector c{0};

  REQUIRE(a.GetEuclideanNorm() == 5);
  REQUIRE(b.GetEuclideanNorm() == 6);
  REQUIRE_THROWS_WITH(c.GetEuclideanNorm() == 0,
                      "EuclideanVector with no dimensions does not have a norm");
}

TEST_CASE("Testing the CreateUnitVector() method", "[create unit vector]") {
  std::vector<double> v1{4, 3};
  std::vector<double> v2{4, 3, 3, 1, 1};
  std::vector<double> v3{0, 0, 0, 0};

  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};
  EuclideanVector e{0};
  EuclideanVector f{};
  EuclideanVector g{v3.begin(), v3.end()};

  EuclideanVector c = a.CreateUnitVector();
  EuclideanVector d = b.CreateUnitVector();

  // sqrt(4^2 + 3^2) = sqrt(25) = 5
  REQUIRE(c.at(0) == (4.0 / 5.0));
  REQUIRE(c.at(1) == (3.0 / 5.0));
  // sqrt(4^2 + 3^2 + 3^2 + 1 + 1) = sqrt(36) = 6
  REQUIRE(d.at(0) == (4.0 / 6.0));
  REQUIRE(d.at(1) == 0.5);
  REQUIRE(d.at(2) == 0.5);
  REQUIRE(d.at(3) == (1.0 / 6.0));
  REQUIRE(d.at(4) == (1.0 / 6.0));

  REQUIRE_THROWS_WITH(e.CreateUnitVector(),
                      "EuclideanVector with no dimensions does not have a unit vector");
  REQUIRE_THROWS_WITH(f.CreateUnitVector(),
                      "EuclideanVector with euclidean normal of 0 does not have a unit vector");
  REQUIRE_THROWS_WITH(g.CreateUnitVector(),
                      "EuclideanVector with euclidean normal of 0 does not have a unit vector");
}

TEST_CASE("Testing overloaded operator+", "[operator+]") {
  std::vector<double> v1{4, 3};
  std::vector<double> v2{12, 30};
  std::vector<double> v3{4, 3, 3, 1, 1};
  std::vector<double> v4{8, -2, 5.5, 12, -3.8};
  std::vector<double> v5{0};
  std::vector<double> v6{0};

  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};
  EuclideanVector c{v3.begin(), v3.end()};
  EuclideanVector d{v4.begin(), v4.end()};
  EuclideanVector e{v5.begin(), v5.end()};
  EuclideanVector f{v6.begin(), v6.end()};

  EuclideanVector ab{a + b};
  EuclideanVector cd{c + d};
  EuclideanVector ef{e + f};

  REQUIRE(ab.GetNumDimensions() == 2);
  REQUIRE(ab.at(0) == (4 + 12));
  REQUIRE(ab.at(1) == (3 + 30));

  REQUIRE(cd.GetNumDimensions() == 5);
  REQUIRE(cd.at(0) == (8 + 4));
  REQUIRE(cd.at(1) == (3 + (-2)));
  REQUIRE(cd.at(2) == (3.0 + 5.5));
  REQUIRE(cd.at(3) == (1 + 12));
  REQUIRE(cd.at(4) == (1.0 + (-3.8)));

  REQUIRE(ef.GetNumDimensions() == 1);
  REQUIRE(ef.at(0) == (0));

  REQUIRE_THROWS_WITH(a + c, "Dimensions of LHS(2) and RHS(5) do not match");
}
