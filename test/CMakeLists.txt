# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(aoc2023Tests LANGUAGES CXX)

# ---- Dependencies ----

find_package(doctest REQUIRED)

# ---- Tests ----

add_executable(aoc2023_test source/aoc2023_test.cpp)
target_link_libraries(
    aoc2023_test PRIVATE
    aoc2023_lib
    doctest::doctest
)
target_compile_features(aoc2023_test PRIVATE cxx_std_20)

# ---- End-of-file commands ----

add_folders(Test)
