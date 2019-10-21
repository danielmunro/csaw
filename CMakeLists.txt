cmake_minimum_required (VERSION 3.6)
project (CSaw)
add_executable(csaw src/main.c)
set(EXECUTABLE_OUTPUT_PATH ./build CACHE PATH "Build directory" FORCE)
include_directories(.)

include_directories(/usr/local/opt/libpq/include)
find_package(PostgreSQL REQUIRED)
target_link_libraries(csaw PRIVATE ${PostgreSQL_LIBRARIES})
set(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "--coverage")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

enable_testing()

add_executable(test_main tests/test_main.c)
add_test(NAME test_main COMMAND $<TARGET_FILE:test_main>)
target_link_libraries(test_main PRIVATE ${PostgreSQL_LIBRARIES})
