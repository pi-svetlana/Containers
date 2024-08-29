all: build test

build:
	mkdir build
	cmake -S ../ -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS_DEBUG="-g -fprofile-arcs -ftest-coverage"
	cmake --build build


clean:
	rm -rf *.a containers_test *.html *.css
	rm -rf build containers_test* *.gc* .leaks_log.txt

test: build
	cp build/tests/containers_test containers_test
	./containers_test --gtest_repeat=1


ps_containers.a: build
	cp build/src/libcontainers_lib.a ps_containers.a

leaks: test
ifeq ($(shell uname -s), Linux)
	valgrind --leak-check=full --track-origins=yes --undef-value-errors=yes --quiet --log-file=.leaks_log.txt ./containers_test
else
	CK_FORK=no leaks --atExit -- ./containers_test
endif

gcov_report: test
	./containers_test
	gcovr -r . --html --html-details -e '/.*/build/' -o gcov_report.html
	open gcov_report.html

clang-check:
	clang-format -n --style=Google *.h *.cc ../tests/*.cc

clang-format:
	clang-format -i --style=Google *.h *.cc ../tests/*.cc
