cmake_minimum_required (VERSION 2.6)
project (CSaw)
add_executable(csaw src/main.c src/event/event.h)

find_package(PostgreSQL REQUIRED)
target_link_libraries(csaw PRIVATE ${PostgreSQL_LIBRARIES})
include_directories(/usr/local/opt/libpq/include)

enable_testing()
add_executable(test_csaw tests/test_main.c)
add_test(test_socket test_csaw)
add_test(test_client test_csaw)
add_test(test_event_dispatcher test_csaw)
target_link_libraries(test_csaw PRIVATE ${PostgreSQL_LIBRARIES})