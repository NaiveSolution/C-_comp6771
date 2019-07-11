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

/**************** CONSTRUCTOR TESTING *********************/

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

/**************** METHOD TESTING *********************/

TEST_CASE("Testing the at() method", "[at()]") {
  std::vector<double> v1{1, 2, 3, 4, 5, 6};
  EuclideanVector a{v1.begin(), v1.end()};

  REQUIRE(a.at(1) == 2);
  REQUIRE(a.at(2) == 3);
  REQUIRE(a.at(3) == 4);

  REQUIRE_THROWS_WITH(a.at(-1), "Index -1 is not valid for this EuclideanVector object");
  REQUIRE_THROWS_WITH(a.at(7), "Index 7 is not valid for this EuclideanVector object");
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

/**************** OVERLOAD TESTING *********************/

TEST_CASE("Testing overloaded operator== and operator!=", "[operator==/operator!=]") {
  std::vector<double> v1{4, 3};
  std::vector<double> v2{4, 3};
  std::vector<double> v3{4.0, 3.0};
  std::vector<double> v4{4, 3, 3, 1, 1};
  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};
  EuclideanVector c{v3.begin(), v3.end()};
  EuclideanVector d{v4.begin(), v4.end()};

  EuclideanVector e{};
  EuclideanVector f{};
  EuclideanVector g{0};

  REQUIRE(a == b);
  REQUIRE(b == c);
  REQUIRE_FALSE(a == d);
  REQUIRE(e == f);

  REQUIRE(a != d);
  REQUIRE_FALSE(a != b);
  REQUIRE(e != g);
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

TEST_CASE("Testing dot product and scalar multiplication operator*", "[operator*]") {
  std::vector<double> v1{4, 3};
  std::vector<double> v2{2, 2};
  std::vector<double> v3{4, -3, 3, -1, 1};
  std::vector<double> v4{2, 2, 2, 2, 2};
  std::vector<double> v5{0,0};

  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};
  EuclideanVector c{v3.begin(), v3.end()};
  EuclideanVector d{v4.begin(), v4.end()};
  EuclideanVector zero{v5.begin(), v5.end()};

  EuclideanVector e = 3 * a;
  EuclideanVector g{0};
  EuclideanVector h{g * 2};

  double ab{a * b};
  double cd{c * d};
  REQUIRE(ab == a.at(0) * b.at(0) + a.at(1) * b.at(1));
  REQUIRE(cd == c.at(0) * d.at(0) + c.at(1) * d.at(1) + c.at(2) * d.at(2) + c.at(3) * d.at(3) +  + c.at(4) * d.at(4));
  REQUIRE_THROWS_WITH(a * c, "Dimensions of LHS(2) and RHS(5) do not match");
  REQUIRE(e.at(0) == 12);
  REQUIRE(e.at(1) == 9);
  REQUIRE(h.at(0) == 0);

  double zero_a{a * zero};
  double zero_b{b * zero};
  REQUIRE(zero_a == a.at(0) * zero.at(0) + a.at(1) * zero.at(1));
  REQUIRE(zero_b == b.at(0) * zero.at(0) + b.at(1) * zero.at(1));

}

TEST_CASE("Testing overloaded operator/", "[operator/]") {
  std::vector<double> v1{4.1, 3.5};
  std::vector<double> v2{2.8, 2.6};

  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};

  EuclideanVector d_a{a / 2.7};
  EuclideanVector d_b{b / 1};
  EuclideanVector c{1};

  REQUIRE(d_a.at(0) == (4.1/2.7));
  REQUIRE(d_a.at(1) == (3.5/2.7));
  REQUIRE(d_b.at(0) == (2.8/1.0));
  REQUIRE(d_b.at(1) == (2.6/1.0));
  REQUIRE_THROWS_WITH(a/0, "Invalid vector division by 0");

  REQUIRE((c/2).at(0) == (0.0/2.0));
}

TEST_CASE("Testing overloaded operator-", "[operator-]") {
  std::vector<double> v1{4.1, 3.5};
  std::vector<double> v2{2.8, 2.6};
  std::vector<double> v3{0, 0};
  std::vector<double> v4{};

  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};
  EuclideanVector c{v3.begin(), v3.end()};
  EuclideanVector d{v4.begin(), v4.end()};

  EuclideanVector minus_a{a - b};
  EuclideanVector minus_b{b - a};
  EuclideanVector minus_c{c - a};

  REQUIRE(minus_a.at(0) == a.at(0) - b.at(0));
  REQUIRE(minus_a.at(1) == a.at(1) - b.at(1));
  REQUIRE(minus_b.at(0) == b.at(0) - a.at(0));
  REQUIRE(minus_b.at(1) == b.at(1) - a.at(1));
  REQUIRE(minus_c.at(0) == c.at(0) - a.at(0));
  REQUIRE(minus_c.at(1) == c.at(1) - a.at(1));

  REQUIRE_THROWS_WITH(a - d, "Dimensions of LHS(2) and RHS(1) do not match");

}

TEST_CASE("Testing overloaded operator<<", "[operator<<]") {
  std::vector<double> v1{4.1, 3.5};
  std::vector<double> v2{2.8};
  std::vector<double> v3{};
  std::vector<double> v4{0};


  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};
  EuclideanVector c{v3.begin(), v3.end()};
  EuclideanVector d{v4.begin(), v4.end()};

  std::ostringstream stream_1, stream_2, stream_3, stream_4;
  stream_1 << a;
  REQUIRE(stream_1.str() == "[4.1 3.5]");
  stream_2 << b;
  REQUIRE(stream_2.str() == "[2.8]");
  stream_3 << c;
  REQUIRE(stream_3.str() == "[0]");
  stream_4 << d;
  REQUIRE(stream_d.str() == "[]");

}

TEST_CASE("Testing overloaded operator+=", "[operator+=]") {
  std::vector<double> v1{4.1, 3.5};
  std::vector<double> v2{2.8, 2.6};
  std::vector<double> v4{};

  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};
  EuclideanVector c{v4.begin(), v4.end()};

  a += b;
  REQUIRE(a.at(0) == 4.1 + b.at(0));
  REQUIRE(a.at(1) == 3.5 + b.at(1));
  REQUIRE_THROWS_WITH(a += c, "Dimensions of LHS(2) and RHS(1) do not match");
}

TEST_CASE("Testing overloaded operator-=", "[operator-=]") {
  std::vector<double> v1{4.1, 3.5};
  std::vector<double> v2{2.8, 2.6};
  std::vector<double> v3{0,0,0};
  std::vector<double> v4{0,0,0};

  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};
  EuclideanVector c{v3.begin(), v3.end()};
  EuclideanVector d{v4.begin(), v4.end()};

  a -= b;
  c -= d;

  REQUIRE(a.at(0) == 4.1 - b.at(0));
  REQUIRE(a.at(1) == 3.5 - b.at(1));
  REQUIRE(c.at(0) == 0 - d.at(0));
  REQUIRE(c.at(1) == 0 - d.at(1));
  REQUIRE_THROWS_WITH(a -= c, "Dimensions of LHS(2) and RHS(3) do not match");
}

TEST_CASE("Testing overloaded operator*=", "[operator*=]") {
  std::vector<double> v1{4.1, 3.5};
  std::vector<double> v2{};

  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};

  a *= 3;
  b *= 3;
  REQUIRE(a.at(0) == 4.1 * 3);
  REQUIRE(a.at(1) == 3.5 * 3);
  REQUIRE(b.at(0) == 0.0 * 3);

}

TEST_CASE("Testing overloaded operator/=", "[operator/=]") {
  std::vector<double> v1{4.1, 3.5};
  std::vector<double> v2{};

  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};

  a /= 3;
  b /= 3;

  REQUIRE(a.at(0) == 4.1 / 3);
  REQUIRE(a.at(1) == 3.5 / 3);
  REQUIRE(b.at(0) == 0.0 / 3);
  REQUIRE_THROWS_WITH(b /= 0, "Invalid vector division by 0");

}

TEST_CASE("Testing copy assignment operator=", "[operator=]") {
  std::vector<double> v1{4.1, 3.5};
  std::vector<double> v2{};
  std::vector<double> v3{0,1,0,1,0,1};

  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};
  EuclideanVector c{v3.begin(), v3.end()};

  b = a;
  REQUIRE(b.at(0) == a.at(0));
  REQUIRE(b.at(1) == a.at(1));

  a = c;
  REQUIRE(a.at(0) == c.at(0));
  REQUIRE(a.at(1) == c.at(1));
  REQUIRE(a.GetNumDimensions() == c.GetNumDimensions());

}

TEST_CASE("Testing move assignment operator=", "[operator=]") {
  std::vector<double> v1{4.1, 3.5};
  std::vector<double> v2{};
  std::vector<double> v3{0,1,0,1,0,1};

  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};
  EuclideanVector c{v3.begin(), v3.end()};

  b = std::move(a);
  REQUIRE(b.at(0) == 4.1);
  REQUIRE(b.at(1) == 3.5);
  REQUIRE(a.GetNumDimensions() == 0);
  REQUIRE_THROWS_WITH(a.at(0), "Index 0 is not valid for this EuclideanVector object");

  a = std::move(c);
  REQUIRE(a.at(0) == 0);
  REQUIRE(a.at(1) == 1);
  REQUIRE(c.GetNumDimensions() == 0);
  REQUIRE_THROWS_WITH(c.at(0), "Index 0 is not valid for this EuclideanVector object");
}

TEST_CASE("Testing vector type conversion operator", "[vector_convert]") {
  std::vector<double> v1{4.1, 3.5};
  std::vector<double> v2{};
  std::vector<double> v3{0,1,0,1,0,1};
  std::vector<double> v4{0};

  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};
  EuclideanVector c{v3.begin(), v3.end()};
  EuclideanVector d{v4.begin(), v4.end()};

  auto v_a = std::vector<double>{a};
  auto v_b = std::vector<double>{b};
  auto v_c = std::vector<double>{c};
  auto v_d = std::vector<double>{d};

  REQUIRE(v_a.size() == 2);
  REQUIRE(v_a[0] == a.at(0));
  REQUIRE(v_a[1] == a.at(1));

  REQUIRE(v_b.size() == 1);
  REQUIRE(v_b[0] == b.at(0));

  REQUIRE(v_c.size() == 6);
  REQUIRE(v_c[0] == c.at(0));
  REQUIRE(v_c[1] == c.at(1));
  REQUIRE(v_c[2] == c.at(2));

  REQUIRE(v_d.size() == 1);
  REQUIRE(v_d[0] == d.at(0));

}

TEST_CASE("Testing list type conversion operator", "[list_convert]") {
  std::vector<double> v1{4.1, 3.5};
  std::vector<double> v2{};
  std::vector<double> v3{0,1,0,1,0,1};
  std::vector<double> v4{0};

  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};
  EuclideanVector c{v3.begin(), v3.end()};
  EuclideanVector d{v4.begin(), v4.end()};

  auto vec_a = std::list<double>{a};
  auto vec_b = std::list<double>{b};
  auto vec_c = std::list<double>{c};
  auto vec_d = std::list<double>{d};

  auto v_a = vec_a.begin();
  auto v_c = vec_c.begin();

  REQUIRE(vec_a.size() == 2);
  REQUIRE(vec_a.front() == a.at(0));
  std::advance(v_a, 1);
  REQUIRE(*v_a == a.at(1));

  REQUIRE(vec_b.size() == 1);
  REQUIRE(vec_b.front() == b.at(0));

  REQUIRE(vec_c.size() == 6);
  REQUIRE(vec_c.front() == c.at(0));
  std::advance(v_c, 1);
  REQUIRE(*v_c == c.at(1));
  std::advance(v_c, 1);
  REQUIRE(*v_c == c.at(2));

  REQUIRE(vec_d.size() == 1);
  REQUIRE(vec_d.front() == d.at(0));

}

TEST_CASE("Testing subscript operator[]", "[operator=]") {
  std::vector<double> v1{4.1, 3.5};
  std::vector<double> v2{};
  std::vector<double> v3{0};

  EuclideanVector a{v1.begin(), v1.end()};
  EuclideanVector b{v2.begin(), v2.end()};
  EuclideanVector c{v3.begin(), v3.end()};

  REQUIRE(a[0] == a.at(0));
  REQUIRE(a[1] == a.at(1));
  REQUIRE(b[0] == b.at(0));
  REQUIRE(c[0] == c.at(0));

  a[0] = 0.0;
  a[1] = -(3.7/8.6);
  b[0] = -0.0;
  c[0] = a[1];

  REQUIRE(a[0] == 0.0);
  REQUIRE(a[1] == -(3.7/8.6));
  REQUIRE(b[0] == 0.0);
  REQUIRE(c[0] == -(3.7/8.6));

  a[1] = b[0];

  REQUIRE(a[1] == 0.0);
  REQUIRE(c[0] == -(3.7/8.6));

  b[0] = b[0] + 5.0;
  REQUIRE(b[0] == 5.0);

  a[0] = a[0] + 2.0;
  a[0] = a[0] + b[0];
  REQUIRE(a[0] == 2.0 + 5.0);

  double d {a[0]};
  REQUIRE(d == 7.0);

}