include(cmake/folders.cmake)

add_custom_target(
    run-exe
    COMMAND aoc2023_exe
    VERBATIM
)
add_dependencies(run-exe aoc2023_exe)

include(cmake/lint-targets.cmake)

add_folders(Project)
