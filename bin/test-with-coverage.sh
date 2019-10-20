set -e

rm -f coverage.info coverage2.info test_main.gcno a.out
make
gcc -I/usr/local/opt/libpq/include -lpq -ftest-coverage -fprofile-arcs tests/test_main.c
lcov --capture --directory . --output-file coverage.info
lcov --list coverage.info
