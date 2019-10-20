clean:
	rm -f build/* coverage.info test_main.gcda test_main.gcno

all:
	gcc -I/usr/local/opt/libpq/include -lpq src/main.c -o build/main

test:
	gcc -I/usr/local/opt/libpq/include -lpq -ftest-coverage -fprofile-arcs tests/test_main.c -o build/main_test; \
	build/main_test;

coverage:
	lcov --capture --directory . --output-file coverage.info; \
	lcov --list coverage.info;