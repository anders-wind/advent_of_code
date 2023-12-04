#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "lib.hpp"


TEST_SUITE("Name is aoc2023")
{
  
TEST_CASE("[library]")
{
  auto const lib = library {};
  REQUIRE(lib.name == "aoc2023");
}
}
