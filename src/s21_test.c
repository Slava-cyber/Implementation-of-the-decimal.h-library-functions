#include <check.h>
#include "s21_decimal.h"
#include <stdlib.h>
#include <float.h>
#include <stdio.h>
#include<string.h>



// MARK: - Convert functions
/*-----------Convert from int to decimal-----------*/
START_TEST(s21_decimal_test_from_int) {
    s21_decimal dec_y;
    
    char binary[8][129] = {"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100011001010",
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011110000011110011",
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001",
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011000001101011001101010",
        "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000101110111101111100001011",
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100110001001011001111111",
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000101111101011110000100000000"
    };
    
    unsigned examples[8] = {2250,123123,1,6346346,-12312331,0,9999999,1E+08};
    
    char arr[129];
    
    for (int j = 0; j < 8;j++) {
        s21_from_int_to_decimal(examples[j],&dec_y);
        for(int i = 0;i < 128;i++) {
            arr[i] = check_bit(127 - i,dec_y) + 48;
        }
        arr[128] = '\0';
        ck_assert_str_eq(binary[j], arr);
    }
}
END_TEST


/*-----------Convert from float to decimal-----------*/
START_TEST(s21_decimal_test_from_float) {
    s21_decimal dec_y;
    char binary[4][129] = {"00000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011000000101100",
        "10000000000001010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011000011011000000",
        "00000000000001010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010111",
        "00000000000000110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011000100001000101"
    };
    
    float examples[4] = {1.2332,-1.00032,0.00023,100.421};
    char arr[129];
    for (int j = 0; j < 4;j++) {
        s21_from_float_to_decimal(examples[j],&dec_y);
        for(int i = 0;i < 128;i++) {
            arr[i] = check_bit(127 - i,dec_y) + 48;
        }
        arr[128] = '\0';
        ck_assert_str_eq(binary[j], arr);
    }
}
END_TEST


/*-----------Convert from decimal to int-----------*/
START_TEST(s21_decimal_test_from_decimal_to_int) {

    
    int valuesA[] = {9403,111,0,100,-1123,};
    int valuesB[] = {202,34,0,100,-111};
    int originValues[] = {9605,145,0,200,-1234};
    s21_decimal src1, src2;
    int a;
    int b;
    int res_origin;
    int res_our_dec;
    for (int i = 0; i < 5;i++) {
        res_our_dec = 0;
        a = valuesA[i];
        b = valuesB[i];
        res_origin = originValues[i];
        
        s21_from_int_to_decimal(a, &src1);
        s21_from_int_to_decimal(b, &src2);
        s21_decimal res_od = s21_add(src1, src2);
        s21_from_decimal_to_int(res_od, &res_our_dec);
        ck_assert_int_eq(res_our_dec, res_origin);
    }
    
}
END_TEST



/*-----------Convert from decimal to float-----------*/
START_TEST(s21_decimal_test_from_decimal_to_float) {

    
    float valuesA[] = {0.111,0.002,0,-0.333,0.000001,};
    float valuesB[] = {0.111,0.003,0,-0.111,0.000005};
    float originValues[] = {0.222,0.005,0,-0.444,0.000006};
    s21_decimal src1, src2;
    float a;
    float b;
    float res_origin;
    float res_our_dec;
    for (int i = 0; i < 5;i++) {
        res_our_dec = 0;
        a = valuesA[i];
        b = valuesB[i];
        res_origin = originValues[i];
    

        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        s21_decimal res_od = s21_add(src1, src2);
        s21_from_decimal_to_float(res_od, &res_our_dec);
        ck_assert_float_eq(res_our_dec, res_origin);
    }
    
}
END_TEST





int main() {
    
    Suite *s1 = suite_create("Convertors and parsers");
    TCase *s21_decimal_tests = tcase_create("Tests");
    suite_add_tcase(s1, s21_decimal_tests);
    tcase_add_test(s21_decimal_tests, s21_decimal_test_from_int);
    tcase_add_test(s21_decimal_tests, s21_decimal_test_from_float);
    tcase_add_test(s21_decimal_tests, s21_decimal_test_from_decimal_to_int);
    tcase_add_test(s21_decimal_tests, s21_decimal_test_from_decimal_to_float);
    
    
    Suite *s2 = suite_create("Comparison Operators");
    TCase *s21_decimal_tests2 = tcase_create("Tests");
    suite_add_tcase(s2, s21_decimal_tests2);
    
    Suite *s3 = suite_create("Arithmetic Operators");
    TCase *s21_decimal_tests3 = tcase_create("Tests");
    suite_add_tcase(s3, s21_decimal_tests3);
    
    Suite *s4 = suite_create("Another functions");
       TCase *s21_decimal_tests4 = tcase_create("Tests");
       suite_add_tcase(s4, s21_decimal_tests4);
   
    
    
    
    SRunner *runner = srunner_create(s1);
    SRunner *runner1 = srunner_create(s2);
    SRunner *runner2 = srunner_create(s3);
    SRunner *runner3 = srunner_create(s4);
    
    srunner_run_all(runner, CK_NORMAL);
    srunner_run_all(runner1, CK_NORMAL);
    srunner_run_all(runner2, CK_NORMAL);
    srunner_run_all(runner3, CK_NORMAL);
    
    srunner_free(runner);
    srunner_free(runner1);
    srunner_free(runner2);
    srunner_free(runner3);
    
    return 0;
    
}
