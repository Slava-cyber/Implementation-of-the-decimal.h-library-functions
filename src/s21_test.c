#include <check.h>
#include "s21_decimal.h"
#include <stdlib.h>
#include <float.h>
#include <stdio.h>
#include <string.h>


START_TEST(s21_decimal_test_1) {
int numbers[] = {
    0,1,2,
    1, 1, 2,
    9, 1, 10,
    99, 1, 100,
    19, 1, 20,
    91, 3, 94,
    0, 0, 0,
    101, 9, 110,
    101, 909, 1010,
    24610, 33081, 57691,    
};
int value1 = numbers[1];
int value2 = numbers[3];
ck_assert_int_eq(value1, value2);
}
END_TEST

 
Suite *example_suite_create() {
    Suite *s1 = suite_create("Test");
    TCase *s21_decimal_tests = tcase_create("Tests");
    suite_add_tcase(s1, s21_decimal_tests);
    tcase_add_test(s21_decimal_tests, s21_decimal_test_1);
 
    return s1;
}


int main() {

  Suite *s1 = example_suite_create();
    // Runner
    SRunner *runner = srunner_create(s1);
    int number_failed;
    srunner_run_all(runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return number_failed == 0 ? 0 : 1;

}