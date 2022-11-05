.PHONY: check_style build test clean check_mem

check_style:
	./run_linters.sh

build:
	cd homework2 && mkdir -p build && cd build && cmake .. && cmake --build .

test:
	cd homework2 && mkdir -p build && cd build && cmake -DTEST_MODE=ON .. && cmake --build .
	cd homework2/build && ctest
	@cd homework2/build && lcov -t "tests/test_matrix" -o coverage.info -c -d matrix_lib/ > /dev/null
	@cd homework2/build && genhtml -o report coverage.info > coverage_module.txt 
	
check_coverage:	
	@./run_coverage.sh

check_mem: build
	./run_memtest.sh homework2/build/tests/test_matrix

clean: 
	cd homework2 && rm -rf build
	