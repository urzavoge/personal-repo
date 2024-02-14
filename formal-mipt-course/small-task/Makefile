CC=clang++ -std=c++20
CFLAGS=-pg
CCOV=-fPIC -fprofile-arcs -ftest-coverage

run:
	$(CC) -c $(CFLAGS) $(CCOV) test.cpp
	$(CC) $(CFLAGS) $(CCOV) test.o
	./a.out

clean:
	rm *.o *.out *.gcov *.gcda *.gcno
	rm -rf lcov-report

coverage:
	gcov test.cpp -r

lcov-report: coverage ## Generate lcov report
	mkdir lcov-report
	lcov --capture --directory . --output-file lcov-report/coverage.info --ignore-errors inconsistent

gen-html: lcov-report
	genhtml lcov-report/coverage.info --output-directory lcov-report --ignore-errors inconsistent