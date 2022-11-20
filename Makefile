.PHONY: check_style build test clean check_mem check_coverage

check_style:
	./run_linters.sh

build:
	cd homework5 && mkdir -p build && cd build && cmake .. && cmake --build .

test:
	cd homework5 && mkdir -p build && cd build && cmake -DTEST_MODE=ON .. && cmake --build .
	cd homework5/build && ctest
	@cd homework5/build && lcov -t "tests/test_set" -o coverage.info -c -d src/ > /dev/null
	@cd homework5/build && genhtml -o report coverage.info > coverage_module.txt 
	
check_coverage:	
	@./run_coverage.sh

check_mem: build
	./run_memtest.sh homework5/build/tests/test_set

clean: 
	cd homework5 && rm -rf build
	