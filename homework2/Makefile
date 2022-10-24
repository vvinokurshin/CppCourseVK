.PHONY: check_style build test clean check_mem

check_style:
	./run_linters.sh

build:
	cd hw2 && mkdir -p build && cd build && cmake .. && cmake --build .

test:
	cd hw2 && mkdir -p build && cd build && cmake -DTEST_MODE=ON .. && cmake --build .
	cd hw2/build && ctest
	@cd hw2/build && lcov -t "tests/test_matrix" -o coverage.info -c -d matrix_lib/ > /dev/null
	@cd hw2/build && genhtml -o report coverage.info > coverage_module.txt 
	
check_coverage:	
	@./run_coverage.sh

check_mem: build
	./run_memtest.sh hw2/build/tests/test_matrix

clean: 
	cd hw2 && rm -rf build