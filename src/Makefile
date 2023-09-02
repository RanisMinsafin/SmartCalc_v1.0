CC = gcc -c
FLAGS = -Wall -Werror -Wextra
SOURCE = s21*.c
CALC_SOURCE = s21_smartcalc.c s21_stack.c s21_parser.c
TEST = tests.c
SOURCE_OBJ = s21*.o
TEST_OBJ = tests/test*.o
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
 CC += -D OS_MAC
 ADD_LIB =
 TEST_FLAGS =-lm -lpthread -lcheck
endif
ifeq ($(OS), Linux)
 CC += -D OS_LINUX
 ADD_LIB = -lcheck -lm -lrt -lpthread
 TEST_FLAGS =-lpthread -lcheck -pthread -lrt -lm
endif
ifeq ($(OS), Darwin)
 CC += -D OS_MAC
 ADD_LIB =
 TEST_FLAGS =-lm -lpthread -lcheck
endif

all: s21_smartcalc.a install dist

install: clean
	mkdir build
	cd QT/TestCalc && qmake && make && make clean && rm Makefile && cd ../../ && mv QT/TestCalc/TestCalc.app build

uninstall:
	rm -rf build*

dist:
	rm -rf Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/src
	mv ./build/TestCalc.app Archive_SmartCalc_v1.0/src/
	tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/
	rm -rf Archive_SmartCalc_v1.0/

dvi:
		open dvi_description/dvi.html
		
valgrind: valgrind_build clean_o clean_a

valgrind_build: s21_smartcalc.a
	gcc $(TEST) -L. -lcheck -lsubunit s21_smartcalc.a -lm -ggdb  -o test_exec 
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./test_exec

s21_smartcalc.a: s21_smartcalc.a clean_o

s21_smartcalc.a:
	$(CC) $(FLAGS) $(SOURCE)
	ar cr s21_smartcalc.a *.o
	ranlib 	s21_smartcalc.a

test: test_build clean_o

test_build: s21_smartcalc.a
	gcc s21_smartcalc.a $(TEST) $(FLAGS) $(TEST_FLAGS) -o check_filetest && ./check_filetest

gcov_report: clean_r report clean

report:
	gcc -fprofile-arcs -ftest-coverage $(CALC_SOURCE) $(TEST) -o s21_test -lcheck
	./s21_test
	lcov -t "test" -o *.info -c -d .
	genhtml -o report/ *.info
	open ./report/index.html

clean_o:
	rm -rf *.o

clean_a:
	rm -rf *.a

clean:
	rm -rf *.o | rm -rf *.a && rm -rf *.so | rm -rf hello* | rm *filetest | rm source/*.gch | rm tests/*.gch | rm *.gcno | rm *.gcda | rm s21_test | rm *.info | rm *_exec | rm RESULT_VALGRIND.txt | rm -rf test_exec*

clean_all: clean clean_o

clean_gcov:
	rm *.gcda | rm *.gcno

clean_r:
	rm -rf report

check:
	clang-format -style=Google -n *.c  *.h QT/TestCalc/*.cpp QT/TestCalc/*.h

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

rebuild: clean all

