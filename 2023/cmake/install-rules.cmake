install(
    TARGETS aoc2023_exe
    RUNTIME COMPONENT aoc2023_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
