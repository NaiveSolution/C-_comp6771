/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

*/

#include "assignments/ev/euclidean_vector.h"
#include "catch.h"

EuclideanVector a{4,5.5};
TEST_CASE("Testing the constructor", "[constructor]"){
  REQUIRE(a.GetNumDimensions() == 4);
}
