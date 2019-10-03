cmake_minimum_required (VERSION 2.6)
project (CSaw)
add_executable(csaw src/main.c src/event/event.h)

include_directories(/usr/local/opt/libpq/include)
find_package(PostgreSQL REQUIRED)
target_link_libraries(csaw PRIVATE ${PostgreSQL_LIBRARIES})

enable_testing()

add_executable(test_socket tests/test_socket_main.c)
add_test(test_socket test_socket)
target_link_libraries(test_socket PRIVATE ${PostgreSQL_LIBRARIES})

add_executable(test_game_service tests/test_game_service_main.c)
add_test(test_game_service test_game_service)
target_link_libraries(test_game_service PRIVATE ${PostgreSQL_LIBRARIES})