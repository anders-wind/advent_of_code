include(cmake/folders.cmake)

add_custom_target(
    run-exe
    COMMAND aoc2024_exe
    VERBATIM
)
add_dependencies(run-exe aoc2024_exe)

include(cmake/lint-targets.cmake)

add_folders(Project)
