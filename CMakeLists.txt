cmake_minimum_required (VERSION 3.6)
project (CSaw)
add_executable(csaw src/main.c)
set(EXECUTABLE_OUTPUT_PATH ./build CACHE PATH "Build directory" FORCE)
include_directories(.)

include_directories(/usr/local/opt/libpq/include)
find_package(PostgreSQL REQUIRED)
target_link_libraries(csaw ${PostgreSQL_LIBRARIES})

enable_testing()

add_executable(test_main tests/test_main.c)
add_test(NAME test_main COMMAND $<TARGET_FILE:test_main>)
target_link_libraries(test_main ${PostgreSQL_LIBRARIES})

add_custom_target(create-coverage
        COMMAND gcc -I/usr/local/opt/libpq/include -lpq -ftest-coverage -fprofile-arcs tests/test_main.c -o build/main_test;
        COMMAND build/main_test;)

add_custom_target(show-coverage
        COMMAND lcov --capture --directory . --output-file coverage.info
        COMMAND lcov --list coverage.info)
