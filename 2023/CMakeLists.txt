cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    aoc2023
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)
include(CTEST)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

find_package(fmt CONFIG REQUIRED)
find_package(doctest CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)

# ---- Declare executable ----

add_executable(
    aoc2023_exe
    ${MY_RESOURCE_FILES}
    source/day01/part1.cpp
    source/day01/part2.cpp
    source/day02/part1.cpp
    source/day02/part2.cpp
    source/main.cpp
)
add_executable(aoc2023::exe ALIAS aoc2023_exe)

set_property(TARGET aoc2023_exe PROPERTY OUTPUT_NAME aoc2023)

target_compile_features(aoc2023_exe PRIVATE cxx_std_23)
target_include_directories(aoc2023_exe ${warning_guard} PUBLIC "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>")
target_include_directories(aoc2023_exe SYSTEM PUBLIC "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>")

target_link_libraries(
    aoc2023_exe
    PRIVATE fmt::fmt
            doctest::doctest
            range-v3::meta
            range-v3::concepts
            range-v3::range-v3
)

# copy data files to build directory
add_custom_command(
    TARGET aoc2023_exe
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data/ $<TARGET_FILE_DIR:aoc2023_exe>/data
)

# ---- Install rules ----

if (NOT CMAKE_SKIP_INSTALL_RULES)
    include(cmake/install-rules.cmake)
endif ()

# ---- Developer mode ----

if (NOT aoc2023_DEVELOPER_MODE)
    return()
elseif (NOT PROJECT_IS_TOP_LEVEL)
    message(AUTHOR_WARNING "Developer mode is intended for developers of aoc2023")
endif ()

include(cmake/dev-mode.cmake)
