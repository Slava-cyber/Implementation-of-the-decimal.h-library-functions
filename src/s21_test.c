#include <check.h>
#include "s21_decimal.h"
#include <stdlib.h>
#include <float.h>
#include <stdio.h>

START_TEST(s21_decimal_test_1) {

unsigned  * numbers = malloc(sizeof(unsigned) * 300);
 s21_decimal dec_y;
//  s21_decimal dec_a;
//   s21_decimal dec_b;
//   s21_decimal dec_res;


//  dec_res = s21_add(dec_a, dec_b);
s21_from_int_to_decimal(124,&dec_y);

for(int i = 0;i < 128;i++) {
    numbers[i] = check_bit(i,dec_y);
}
for(int i = 0;i < 128;i++) {
    if (i % 32 == 0) {
            printf("\n");
    }
    printf("%d",numbers[i]);
}
printf("\n");
free(numbers);
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
    // int number_failed;
    srunner_run_all(runner, CK_NORMAL);
    // number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return 0;

}