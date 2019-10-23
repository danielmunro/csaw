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

add_custom_command(
        OUTPUT test_main.gcno
        COMMAND gcc -I/usr/local/opt/libpq/include -lpq -ftest-coverage -fprofile-arcs tests/test_main.c -o build/main_test)

add_custom_command(
        OUTPUT test_main.gcda
        COMMAND build/main_test
        DEPENDS test_main.gcno)

add_custom_command(
        OUTPUT coverage.info
        COMMAND lcov --capture --directory . --output-file coverage.info;
        DEPENDS test_main.gcda)

add_custom_target(test-coverage
        COMMAND lcov --list coverage.info
        DEPENDS coverage.info)
