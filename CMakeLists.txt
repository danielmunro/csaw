cmake_minimum_required (VERSION 2.6)
project (CSaw)
add_executable(csaw src/main.c)
set(EXECUTABLE_OUTPUT_PATH ./build CACHE PATH "Build directory" FORCE)

include_directories(/usr/local/opt/libpq/include)
find_package(PostgreSQL REQUIRED)
target_link_libraries(csaw PRIVATE ${PostgreSQL_LIBRARIES})

enable_testing()

function(add_test_suite test_name test_main)
    add_executable(${test_name} ${test_main})
    add_test(NAME ${test_name} COMMAND $<TARGET_FILE:${test_name}>)
    target_link_libraries(${test_name} PRIVATE ${PostgreSQL_LIBRARIES})
endfunction()

add_test_suite(test_socket tests/test_socket_main.c)
add_test_suite(test_client tests/test_client_main.c)
add_test_suite(test_game_service tests/test_game_service_main.c)
add_test_suite(test_actions tests/test_actions_main.c)
add_test_suite(test_room tests/test_room_main.c)
