.PHONY: check_style build test clean check_mem check_coverage

check_style:
	./run_linters.sh

build:
	cd homework5 && mkdir -p build && cd build && cmake .. && cmake --build .

test:
	cd homework5 && mkdir -p build && cd build && cmake -DTEST_MODE=ON .. && cmake --build .
	cd homework5/build && ctest -V

check_mem: build
	./run_memtest.sh homework5/build/tests/test_set

clean: 
	cd homework5 && rm -rf build
	