install(TARGETS aoc2024_exe RUNTIME COMPONENT aoc2024_Runtime)

if (PROJECT_IS_TOP_LEVEL)
    include(CPack)
endif ()
