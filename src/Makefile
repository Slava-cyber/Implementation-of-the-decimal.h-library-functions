OS := $(shell uname -s)

CFLAGS = -c -Wall -Werror -Wextra

all: clean s21_decimal.a test

test: s21_decimal.a s21_test.o
ifeq ($(OS), Darwin)
	gcc s21_test.o s21_decimal.a -lcheck -o Test
	./Test
else
	gcc s21_test.o s21_decimal.a -lcheck -lm -lrt -lpthread -lsubunit -o Test
	./Test
endif

gcov_report: s21_decimal_gcov.o s21_test_gcov.o
ifeq ($(OS), Darwin)
	gcc -fprofile-arcs -ftest-coverage -lcheck s21_test_gcov.o s21_decimal_gcov.o -o Test
else
	gcc s21_test_gcov.o s21_decimal_gcov.o -fprofile-arcs -ftest-coverage -lcheck -lm -lrt -lpthread -lsubunit -o Test
endif
	./Test
	gcov s21_decimal_gcov
	gcov s21_test_gcov
	lcov -t "s21_decimal" -o s21_decimal.info -c -d .
	genhtml -o report s21_decimal.info
	open report/index.html

s21_test.o: s21_test.c
	gcc $(CFLAGS) s21_test.c -o s21_test.o

s21_decimal.o: s21_decimal.c s21_decimal.h
	gcc $(CFLAGS) s21_decimal.c -o s21_decimal.o 

s21_test_gcov.o: s21_test.c
	gcc -fprofile-arcs -ftest-coverage $(CFLAGS) s21_test.c -o s21_test_gcov.o

s21_decimal_gcov.o: s21_decimal.c s21_decimal.h
	gcc $(CFLAGS) -fprofile-arcs -ftest-coverage s21_decimal.c -o s21_decimal_gcov.o 

clean:
	rm -f *.o Test *.out *.gcov *.gcda *.gcno *.info *.a
	rm -rf ./report

rebuild: clean all

s21_decimal.a: s21_decimal.o
	ar rcs s21_decimal.a s21_decimal.o
	ranlib s21_decimal.a

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c
	CK_FORK=no leaks --atExit -- ./Test
