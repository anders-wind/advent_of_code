include(cmake/folders.cmake)

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()

add_custom_target(
    run-exe
    COMMAND aoc2023_exe
    VERBATIM
)
add_dependencies(run-exe aoc2023_exe)

include(cmake/lint-targets.cmake)

add_folders(Project)
