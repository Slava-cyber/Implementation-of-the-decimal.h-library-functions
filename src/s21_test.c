#include <check.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include "s21_decimal.h"
// MARK: - Convert functions
/*-----------Convert from int to decimal-----------*/
START_TEST(s21_decimal_test_from_int) {
    s21_decimal dec_y;
    char binary[8][129] = {
        "000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000100011001010",
        "000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000011110000011110011",
        "000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000001",
        "000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000011000001101011001101010",
        "100000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000101110111101111100001011",
        "000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000",
        "000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000100110001001011001111111",
        "000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000101111101011110000100000000"};
    unsigned examples[8] = {2250, 123123, 1, 6346346, -12312331, 0, 9999999, 1E+08};
    char arr[129];
    for (int j = 0; j < 8; j++) {
        s21_from_int_to_decimal(examples[j], &dec_y);
        for (int i = 0; i < 128; i++) {
            arr[i] = check_bit(127 - i, dec_y) + 48;
        }
        arr[128] = '\0';
        ck_assert_str_eq(binary[j], arr);
    }
}
END_TEST
/*-----------Convert from float to decimal-----------*/
START_TEST(s21_decimal_test_from_float) {
    s21_decimal dec_y;
    char binary[4][129] = {
"00000000000001000000000000000000000000000000000000000"
"000000000000000000000000000000000000000000000000000000000000011000000101100",
"10000000000001010000000000000000000000000000000000000"
"000000000000000000000000000000000000000000000000000000000011000011011000000",
"000000000000010100000000000000000000000000000000000000"
"000000000000000000"
"00000000000000000000000000000000000000000000000000010111",
"000000000000010000000000000000000000000000000000000000000"
"00000000000000000000000000000000000000000000000000011110101001010110001"};
    float examples[4] = {1.2332, -1.00032, 0.00023, 100.421};
    char arr[129];
    for (int j = 0; j < 2; j++) {
        s21_from_float_to_decimal(examples[j], &dec_y);
        for (int i = 0; i < 128; i++) {
            arr[i] = check_bit(127 - i, dec_y) + 48;
        }
        arr[128] = '\0';
        ck_assert_str_eq(binary[j], arr);
    }
}
END_TEST
/*-----------Convert from decimal to int-----------*/
START_TEST(s21_decimal_test_from_decimal_to_int) {
    int valuesA[] = {
        9403, 111, 0, 100, -1123,
    };
    int valuesB[] = {202, 34, 0, 100, -111};
    int originValues[] = {9605, 145, 0, 200, -1234};
    s21_decimal src1, src2;
    int a;
    int b;
    int res_origin;
    int res_our_dec;
    for (int i = 0; i < 5; i++) {
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
    float valuesA[] = {
        0.111, 0.002, 0, -0.333, 0.000001,
    };
    float valuesB[] = {0.111, 0.003, 0, -0.111, 0.000005};
    float originValues[] = {0.222, 0.005, 0, -0.444, 0.000006};
    s21_decimal src1, src2;
    float a;
    float b;
    float res_origin;
    float res_our_dec;
    for (int i = 0; i < 5; i++) {
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

// MARK: - Arithmetics operations

/*-----------add-----------*/
START_TEST(s21_decimal_test_add) {
    int valuesA[] = {100, -100000, 0, -111111, 1E+02};
    int valuesB[] = {100, -100000, 0, 111111, 1E+03};
    int originValues[] = { 200, -200000, 0, 0, 1100 };
    s21_decimal src1, src2;
    int a;
    int b;
    int res_origin;
    int res_our_dec;
    for (int i = 0; i < 5; i++) {
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
} END_TEST

START_TEST(s21_decimal_test_add1) {
    s21_decimal src1, src2;
    int a = -46;
    float b = 0.0 / 0.0;
    float res_our_dec = 0.0;
    float res_origin;
    s21_from_int_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NAN);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
    a = -1234;
    b = -221.234;
    res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    res_origin = -1455.234009;
    res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
    a = -1.0;
    b = 1.0;
    res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NORMAL_VALUE);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
    a = -1234;
    b = -221.234;
    res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    res_origin = -1455.234009;
    res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
    a = -9403;
    b = 0.00234;
    res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    res_origin = -9402.99766;
    res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
    a = -9403;
    b = 234;
    res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    res_origin = -9169;
    res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
    a = -0.94e03;
    b = -112.0234;
    res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    res_origin = -1052.023438;
    res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
    a = -0.94e03;
    b = -112.0e2;
    res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    res_origin = -12140;
    res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);

    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x300000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xF;
    src1.bits[0] = 0x67E4FEEF;
    src2.bits[3] = 0x300000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFF;
    src2.bits[0] = 0x67E4FFFF;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x300000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x10E;
    result_origin.bits[0] = 0xCFC9FEEE;
    s21_decimal result_our = s21_add(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x30000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFF;
    src1.bits[0] = 0x67E4F;
    src2.bits[3] = 0x60000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xEA;
    src2.bits[0] = 0x67E4F;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x60000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x3E502;
    result_origin.bits[0] = 0x1963E2E7;
     result_our = s21_add(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);


    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x30000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x80070000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x70000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x270FEFED;
    result_origin.bits[0] = 0x00F26FA1;
    result_our = s21_add(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x80030000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x80070000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x80070000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x27100FEC;
    result_origin.bits[0] = 0xFFF96C3F;
    result_our = s21_add(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x80030000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x70000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x80070000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x270FEFED;
    result_origin.bits[0] = 0x00F26FA1;
    result_our = s21_add(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}  END_TEST


START_TEST(s21_decimal_test_nan) {
  s21_decimal src1, src2, res;
  src1.value_type = s21_NAN;
  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.value_type = s21_NORMAL_VALUE;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  res = s21_sub(src1, src2);
  ck_assert_int_eq(res.value_type, s21_NAN);
  res = s21_div(src1, src2);
  ck_assert_int_eq(res.value_type, s21_NAN);
  src1.value_type = s21_INFINITY;
  src2.value_type = s21_NEGATIVE_INFINITY;
  res = s21_add(src1, src2);
  ck_assert_int_eq(res.value_type, s21_NAN);
  src1.value_type = s21_INFINITY;
  res = s21_round(src1);
  ck_assert_int_eq(res.value_type, s21_INFINITY);
  res = s21_floor(src1);
  ck_assert_int_eq(res.value_type, s21_INFINITY);
  src1.value_type = s21_NAN;
  res = s21_truncate(src1);
  ck_assert_int_eq(res.value_type, s21_NAN);
  res = s21_negate(src1);
  ck_assert_int_eq(res.value_type, s21_NAN);
  src1.value_type = s21_INFINITY;
  res = s21_negate(src1);
  ck_assert_int_eq(res.value_type, s21_NEGATIVE_INFINITY);
  src1.value_type = s21_NEGATIVE_INFINITY;
  res = s21_negate(src1);
  ck_assert_int_eq(res.value_type, s21_INFINITY);
  src1.value_type = s21_INFINITY;
  src2.value_type = s21_INFINITY;
  ck_assert_int_eq(s21_is_equal(src1, src2), 0);
  src2.value_type = s21_NORMAL_VALUE;
  src1.value_type = s21_NORMAL_VALUE;
  src2.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(s21_is_less(src1, src2), 1);
  src2.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(s21_is_less(src1, src2), 1);
  src1.value_type = s21_INFINITY;
  ck_assert_int_eq(s21_is_less(src1, src2), 1);
  src1.value_type = s21_NEGATIVE_INFINITY;
  ck_assert_int_eq(s21_is_less(src1, src2), 0);
  src2.value_type = s21_INFINITY;
  ck_assert_int_eq(s21_is_less(src1, src2), 0);
  src2.value_type = s21_NEGATIVE_INFINITY;
  src1.value_type = s21_INFINITY;
  ck_assert_int_eq(s21_is_less(src1, src2), 1);
  src1.value_type = s21_NORMAL_VALUE;
  ck_assert_int_eq(s21_is_less(src1, src2), 1);
  src1.value_type = s21_NEGATIVE_INFINITY;
  src2.value_type = s21_NEGATIVE_INFINITY;
  ck_assert_int_eq(s21_is_less(src1, src2), 1);
  src1.value_type = s21_NORMAL_VALUE;
  src2.value_type = s21_INFINITY;
  ck_assert_int_eq(s21_is_less(src1, src2), 0);
  src2.value_type = s21_NAN;
  ck_assert_int_eq(s21_is_less(src1, src2), 1);
  src1.value_type = s21_NEGATIVE_INFINITY;
  src2.value_type = s21_INFINITY;
  res = s21_add(src1, src2);
  ck_assert_int_eq(res.value_type, s21_NAN);
  src1.value_type = s21_NORMAL_VALUE;
  src2.value_type = s21_INFINITY;
  res = s21_add(src1, src2);
  ck_assert_int_eq(res.value_type, s21_INFINITY);
  src2.value_type = s21_NEGATIVE_INFINITY;
  res = s21_add(src1, src2);
  ck_assert_int_eq(res.value_type, s21_NEGATIVE_INFINITY);
}
END_TEST



/*-----------Sub-----------*/
START_TEST(s21_decimal_test_sub) {
    int valuesA[] = {100, 100000, 1E+3, -111111, 1E+02};
    int valuesB[] = {100, 100000, 1E+2, -1, 1E+03};
    int originValues[] = {0, 0, 900, -111110, -900};
    s21_decimal src1, src2;
    int a;
    int b;
    int res_origin;
    int res_our_dec;
    for (int i = 0; i < 4; i++) {
        res_our_dec = 0;
        a = valuesA[i];
        b = valuesB[i];
        res_origin = originValues[i];
        s21_from_int_to_decimal(a, &src1);
        s21_from_int_to_decimal(b, &src2);
        s21_decimal res_od = s21_sub(src1, src2);
        s21_from_decimal_to_int(res_od, &res_our_dec);
        ck_assert_int_eq(res_our_dec, res_origin);
}
} END_TEST
START_TEST(s21_decimal_test_sub2) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0b00000000000000010000000000000000;
    src1.bits[2] = 0;
    src1.bits[1] = 0;
    src1.bits[0] = 0b00000000000000000110011011110000;
    src2.bits[3] = 0b00000000000000110000000000000000;
    src2.bits[2] = 0;
    src2.bits[1] = 0;
    src2.bits[0] = 0b00000000000001000101000111010110;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0b00000000000000110000000000000000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0;
    result_origin.bits[0] = 0b00000000001000111110001111101010;
    s21_decimal result_our = s21_sub(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0b00000000000000110000000000000000;
    src1.bits[2] = 0;
    src1.bits[1] = 0;
    src1.bits[0] = 0b00000000000001000101000111010110;
    src2.bits[3] = 0b00000000000000010000000000000000;
    src2.bits[2] = 0;
    src2.bits[1] = 0;
    src2.bits[0] = 0b00000000000000000000101110111100;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0b10000000000000110000000000000000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0;
    result_origin.bits[0] = 0b00000000000000000100001110011010;
     result_our = s21_sub(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
     src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x80030000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x80070000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x80070000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x270FEFED;
    result_origin.bits[0] = 0x00F26FA1;
     result_our = s21_sub(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x30000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x80070000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x70000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x27100FEC;
    result_origin.bits[0] = 0xFFF96C3F;
     result_our = s21_sub(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
     src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0b10000000000000010000000000000000;
    src1.bits[2] = 0;
    src1.bits[1] = 0;
    src1.bits[0] = 0b00000000000000000000000100110000;
    src2.bits[3] = 0b10000000000001100000000000000000;
    src2.bits[2] = 0;
    src2.bits[1] = 0;
    src2.bits[0] = 0b00010001001000010001101001100000;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0b00000000000001100000000000000000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0;
    result_origin.bits[0] = 0b00001111010100010011110001100000;
    result_our = s21_sub(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x80030000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x70000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x80070000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x27100FEC;
    result_origin.bits[0] = 0xFFF96C3F;
     result_our = s21_sub(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b00000000000000000000011111100100;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000000000000000000000;
    src2.bits[0] = 0b00000101100110111101101000011001;
    src2.bits[1] = 0b00000000000000000000000000000000;
    src2.bits[2] = 0b00000000000000000000000000000000;
    src2.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal result;
    result_our = s21_sub(src2, src1);
    result.value_type = s21_NORMAL_VALUE;
    result.bits[0] = 0b00000101100110111101001000110101;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(result.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result.bits[0], result_our.bits[0]);
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b00000000000000000000011111100100;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b10000000000000000000000000000000;
    src2.bits[0] = 0b00000000000000000010010010111011;
    src2.bits[1] = 0b00000000000000000000000000000000;
    src2.bits[2] = 0b00000000000000000000000000000000;
    src2.bits[3] = 0b10000000000000000000000000000000;
    result_our = s21_sub(src2, src1);
    result.value_type = s21_NORMAL_VALUE;
    result.bits[0] = 0b00000000000000000001110011010111;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_int_eq(result.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result.bits[0], result_our.bits[0]);
    float value;
    s21_decimal dec3, dec4, dec5;
    init_decimal(&dec3);
    init_decimal(&dec4);
    dec3.value_type = s21_NAN;
    dec4.value_type = s21_NAN;
    dec5 = s21_sub(dec3, dec4);
    s21_from_decimal_to_float(dec5, &value);
    if (dec5.value_type == 3) {
    ck_assert_int_eq(dec5.value_type, 3);
    }
    dec4.value_type = s21_NORMAL_VALUE;
    dec3.value_type = s21_INFINITY;
    dec5 = s21_sub(dec3, dec4);
    ck_assert_int_eq(dec5.value_type, 1);

    dec4.value_type = s21_NEGATIVE_INFINITY;
    dec3.value_type = s21_INFINITY;
    dec5 = s21_sub(dec3, dec4);
    ck_assert_int_eq(dec5.value_type, 3);
//
    dec4.value_type = s21_NAN;
    dec3.value_type = s21_NORMAL_VALUE;
    dec5 = s21_sub(dec3, dec4);
    ck_assert_int_eq(dec5.value_type, 3);
//
    dec4.value_type = s21_NORMAL_VALUE;
    dec3.value_type = s21_NORMAL_VALUE;
    dec5 = s21_sub(dec3, dec4);
    ck_assert_int_eq(dec5.value_type, 0);
} END_TEST
/*-----------Mult-----------*/
START_TEST(s21_decimal_test_mult) {
float valuesA[] = { 1010.123, 123, 1E+3, -1111.11, 11, 9403.0e2, 9403.0e2, -32768, -32768 };
float valuesB[] = { 100.1123, 123, 1E+2, -1, 1E+03, 202, 9403.0e2, 2, 32768 };

    s21_decimal src1, src2;
    float a;
    float b;
    float res_origin;
    float res_our_dec;
    for (int i = 0; i < 10; i++) {
    res_our_dec = 0;
    a = valuesA[i];
    b = valuesB[i];
        res_origin = a*b;
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        s21_decimal res_od = s21_mul(src1, src2);
        s21_from_decimal_to_float(res_od, &res_our_dec);
        ck_assert_float_eq(res_our_dec, res_origin);
}
} END_TEST
START_TEST(s21_decimal_test_mult1) {
    s21_decimal src1, src2;
    float a = 1.0 / 0.0;
    int b = 0;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NAN);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
} END_TEST
START_TEST(s21_decimal_test_mult2) {
    s21_decimal src1, src2;
    float a = 1.0 / 0.0;
    float b = 132 / 0.0;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_INFINITY);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
} END_TEST
START_TEST(s21_decimal_test_mult3) {
    s21_decimal src1, src2;
    float a = 1.0 / 0.0;
    float b = 1.0 / 0.0;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_INFINITY);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
} END_TEST
START_TEST(s21_decimal_test_mult4) {
    s21_decimal src1, src2;
    float a = 1.0 / 0.0;
    float b = 0.0 / 0.0;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NAN);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
} END_TEST
START_TEST(s21_decimal_test_mult5) {
    s21_decimal src1, src2;
    float a = 9403.0e2;
    float b = 9403.0e2;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = 884164090000;
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
     a = 9403;
     b = 202;
    res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    res_origin = 1899406;
     res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
     a = -32768;
     b = 2;
     res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
     res_origin = -65536;
     res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
     a = -32768;
     b = 32768;
     res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
     res_origin = -1073741824;
     res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
    float d = 1.0 / 0.0;
     b = 0;
     res_our_dec = 0.0;
    s21_from_float_to_decimal(d, &src1);
    s21_from_float_to_decimal(b, &src2);
     res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NAN);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
    d = 1.0 / 0.0;
    b = 1.0 / 0.0;
     res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
     res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NEGATIVE_INFINITY);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
    d = 1.0 / 0.0;
     b = 0.0 / 0.0;
     res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
     res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NAN);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
     d = 1.0 / 0.0;
     b = -1.0 / 0.0;
     res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
     res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NEGATIVE_INFINITY);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);

      d = -1.0 / 0.0;
     b = 123;
     res_our_dec = 0.0;
    s21_from_float_to_decimal(d, &src1);
    s21_from_float_to_decimal(b, &src2);
     res_od = s21_mul(src2, src1);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NEGATIVE_INFINITY);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);

      d = 1.0 / 0.0;
     b = 0;
     res_our_dec = 0.0;
    s21_from_float_to_decimal(d, &src1);
    s21_from_int_to_decimal(b, &src2);
     res_od = s21_mul(src2, src1);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NAN);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);

     d = -1.0 / 0.0;
     b = 0.0 / 0.0;
     res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
     res_od = s21_mul(src2, src1);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NAN);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
     d = -1.0 / 0.0;
     b = 0.0 / 0.0;
     res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
     res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NAN);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
      d = 0.0 / 0.0;
     b = 0.0 / 0.0;
     res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
     res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NAN);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
} END_TEST

START_TEST(s21_decimal_test_mult6) {
    float b = 0, c = 0.001999999862164;
    float a1 = 2;
    float a2 = 10E26;
    s21_decimal decimal1, decimal2, decimal3;
    init_decimal(&decimal3);
    s21_from_float_to_decimal(a1, &decimal1);
    s21_from_float_to_decimal(a2, &decimal2);
    set_ten_power(30, &decimal2);
    decimal3 = s21_mul(decimal2, decimal1);
    s21_from_decimal_to_float(decimal3, &b);
    ck_assert_float_eq(b, c);
} END_TEST

START_TEST(s21_decimal_test_mult7) {
    float b = 0;
    float a1 = 0.02454;
    float a2 = 10E26;
    s21_decimal decimal1, decimal2, decimal3;
    init_decimal(&decimal3);
    s21_from_float_to_decimal(a1, &decimal1);
    s21_from_float_to_decimal(a2, &decimal2);
    set_ten_power(30, &decimal2);
    decimal3 = s21_mul(decimal2, decimal1);
    s21_from_decimal_to_float(decimal3, &b);
    ck_assert_float_eq(b, 2.45e-05);
} END_TEST










/*-----------Div-----------*/
START_TEST(s21_decimal_test_div) {
    float valuesA[] = { 1010.123, 5232, 1E+3, -1111.11, 11 };
    float valuesB[] = { 100.1123, 2, 1E+2, -1, 1E+03 };

    s21_decimal src1, src2;
    float a;
    float b;
    float res_origin;
    float res_our_dec;
    for (int i = 0; i < 5; i++) {
        res_our_dec = 0;
        a = valuesA[i];
        b = valuesB[i];
        res_origin = a / b;
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        s21_decimal res_od = s21_div(src1, src2);
        s21_from_decimal_to_float(res_od, &res_our_dec);
        ck_assert_float_eq(res_our_dec, res_origin);
}
} END_TEST
START_TEST(s21_decimal_test_div1) {
    float valuesA[] = { 0, 0, 1E+3, -1111.11, 11, 312};
    float valuesB[] = { 100.1123, -2, 1E+2, -1, 1E+03, 0.003 };
    s21_decimal src1, src2;
    float a;
    float b;
    float res_origin;
    float res_our_dec;
    for (int i = 0; i < 6; i++) {
        res_our_dec = 0;
        a = valuesA[i];
        b = valuesB[i];
        res_origin = a / b;
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        s21_decimal res_od = s21_div(src1, src2);
        s21_from_decimal_to_float(res_od, &res_our_dec);
        ck_assert_float_eq(res_our_dec, res_origin);
}
} END_TEST
/*-----------Mod-----------*/
START_TEST(s21_decimal_test_mod) {
    int valuesA[] = { 11240, 0, 1, 1E+09 };
    int valuesB[] = { 142, 0, 532, 1E+08 };
    int originValues[] = { 22, 0, 1, 0 };
    s21_decimal src1, src2;
    int a;
    int b;
    int res_origin;
    int res_our_dec;
    for (int i = 0; i < 4; i++) {
        res_our_dec = 0;
        a = valuesA[i];
        b = valuesB[i];
        res_origin = originValues[i];
        s21_from_int_to_decimal(a, &src1);
        s21_from_int_to_decimal(b, &src2);
        s21_decimal res_od = s21_mod(src1, src2);
        s21_from_decimal_to_int(res_od, &res_our_dec);
        ck_assert_int_eq(res_our_dec, res_origin);
}
} END_TEST
START_TEST(s21_decimal_test_mod1) {
s21_decimal src1, src2, res_mod;
    int a = 3;
    int b = 2;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    res_mod = s21_mod(src1, src2);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
} END_TEST
// MARK: - Another functions
/*-----------Negate-----------*/
START_TEST(s21_decimal_test_negate) {
    int valuesA[] = { 11240, 0, 1, 1E+04 };
    int originValues[] = { -11240, 0, -1, -10000 };
    s21_decimal src1;
    int a;
    int res_origin;
    int res_our_dec;
    for (int i = 0; i < 4; i++) {
        res_our_dec = 0;
        a = valuesA[i];
        res_origin = originValues[i];
        s21_from_int_to_decimal(a, &src1);
        s21_decimal res_od = s21_negate(src1);
        s21_from_decimal_to_int(res_od, &res_our_dec);
        ck_assert_int_eq(res_our_dec, res_origin);
}
} END_TEST
/*-----------Truncate-----------*/
START_TEST(s21_decimal_test_truncate) {
    s21_decimal src1;
    s21_decimal result;
    s21_decimal res_od;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x000A0000;
    src1.bits[2] = 0x0;
    src1.bits[1] = 0xFFFFFFFF;
    src1.bits[0] = 0xFFFFFFFF;
    result.bits[3] = 0x0;
    result.bits[2] = 0x0;
    result.bits[1] = 0x0;
    result.bits[0] = 0x6DF37F67;
    res_od = s21_truncate(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
    src1.bits[3] = 0x800C0000;
    src1.bits[2] = 0x0;
    src1.bits[1] = 0xFFFFFFFF;
    src1.bits[0] = 0xFFFFFFFF;
    result.bits[3] = 0x80000000;
    result.bits[2] = 0x0;
    result.bits[1] = 0x0;
    result.bits[0] = 0x1197998;
    res_od = s21_truncate(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x80000000;
    src1.bits[2] = 0x0;
    src1.bits[1] = 0xFFFFFFFF;
    src1.bits[0] = 0xFFFFFFFF;
    result.bits[3] = 0x80000000;
    result.bits[2] = 0x0;
    result.bits[1] = 0xFFFFFFFF;
    result.bits[0] = 0xFFFFFFFF;
    res_od = s21_truncate(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b00000000000000000000000001101101;
    src1.bits[1] = 0b00000000000011000110010101011011;
    src1.bits[2] = 0b00000000000000000011000000111001;
    src1.bits[3] = 0b00000000000011100000000000000000;
    result.bits[0] = 0b10000111101111000001011000011110;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    res_od = s21_truncate(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b11011110101001001000000010110110;
    src1.bits[1] = 0b01011111101001011101111110100000;
    src1.bits[2] = 0b00011111111010011010111101100000;
    src1.bits[3] = 0b00000000000010010000000000000000;
    result.bits[0] = 0b00110100101011011100000100111110;
    result.bits[1] = 0b10001001000100001000011110111001;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    res_od = s21_truncate(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
} END_TEST
START_TEST(s21_decimal_test_truncate1) {
    float valuesA[] = { 1123.1123, 0, -12.4124, -321 };
    float originValues[] = { 1123, 0, -12, -321 };
    s21_decimal src1, res_od;
    float a, b;
    for (int i = 0; i < 4; i++) {
        a = valuesA[i];
        s21_from_float_to_decimal(a, &src1);
        res_od = s21_truncate(src1);
        s21_from_decimal_to_float(res_od, &b);
        ck_assert_float_eq(b, originValues[i]);
        }
} END_TEST
/*-----------Round-----------*/
START_TEST(s21_decimal_test_round) {
    s21_decimal src1;
    s21_decimal result;
    s21_decimal res_od;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b01100011000011111111111111111111;
    src1.bits[1] = 0b01101011110001110101111000101101;
    src1.bits[2] = 0b00000000000000000000000000000101;
    src1.bits[3] = 0b10000000000010100000000000000000;
    result.bits[0] = 0b01010100000010111110010000000000;
    result.bits[1] = 0b00000000000000000000000000000010;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    res_od = s21_round(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b01010101001110101110101110110001;
    src1.bits[1] = 0b00001101101101001101101001011111;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b10000000000100100000000000000000;
    result.bits[0] = 0b00000000000000000000000000000001;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    res_od = s21_round(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b10010011111100000001110001010010;
    src1.bits[1] = 0b00000000000000000000000100100000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000010100000000000000000;
    result.bits[0] = 0b00000000000000000000000001111100;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    res_od = s21_round(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b11001101110001110111110001000000;
    src1.bits[1] = 0b00111110001001010000001001100000;
    src1.bits[2] = 0b00100000010011111100111001011110;
    src1.bits[3] = 0b10000000000001000000000000000000;
    result.bits[0] = 0b10100000111111100100111000000100;
    result.bits[1] = 0b00011011110011101100110011101101;
    result.bits[2] = 0b00000000000000001101001111000010;
    result.bits[3] = 0b10000000000000000000000000000000;
    res_od = s21_round(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b10100000111111100100111000000100;
    src1.bits[1] = 0b00011011110011101100110011101101;
    src1.bits[2] = 0b00000000000000001101001111000010;
    src1.bits[3] = 0b00000000000000000000000000000000;
    res_od = s21_round(src1);
    result.bits[0] = 0b10100000111111100100111000000100;
    result.bits[1] = 0b00011011110011101100110011101101;
    result.bits[2] = 0b00000000000000001101001111000010;
    result.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
} END_TEST
/*-----------Floor-----------*/
START_TEST(s21_decimal_test_floor) {
    s21_decimal src1;
    s21_decimal result;
    s21_decimal res_od;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b00001111111111111111111111111111;
    src1.bits[1] = 0b00111110001001010000001001100001;
    src1.bits[2] = 0b00100000010011111100111001011110;
    src1.bits[3] = 0b00000000000010100000000000000000;
    res_od = s21_floor(src1);
    result.bits[0] = 0b10100111011000111111111111111111;
    result.bits[1] = 0b00001101111000001011011010110011;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b00001111111111111111111111111111;
    src1.bits[1] = 0b00111110001001010000001001100001;
    src1.bits[2] = 0b00100000010011111100111001011110;
    src1.bits[3] = 0b10000000000010100000000000000000;
    res_od = s21_floor(src1);
    result.bits[0] = 0b10100111011001000000000000000000;
    result.bits[1] = 0b00001101111000001011011010110011;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b10111101001001111000010001010010;
    src1.bits[1] = 0b00000000000000000000000000011100;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b10000000000010010000000000000000;
    res_od = s21_floor(src1);
    result.bits[0] = 0b00000000000000000000000001111100;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b10010011111100000001110001010010;
    src1.bits[1] = 0b00000000000000000000000100100000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000010100000000000000000;
    res_od = s21_floor(src1);
    result.bits[0] = 0b00000000000000000000000001111011;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b01010101001110101110101110110001;
    src1.bits[1] = 0b00001101101101001101101001011111;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b10000000000100100000000000000000;
    res_od = s21_floor(src1);
    result.bits[0] = 0b00000000000000000000000000000001;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b01010101001110101110101110110001;
    src1.bits[1] = 0b00001101101101001101101001011111;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000100100000000000000000;
    res_od = s21_floor(src1);
    result.bits[0] = 0b00000000000000000000000000000000;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
} END_TEST
// MARK: - Comparison operatots
/*-----------Less-----------*/
START_TEST(s21_decimal_test_less) {
    float valuesA[] = { 11240, 1, 12.4124, 1E+03 };
    float valuesB[] = { 11240, 0, 1.6532, 1E+04 };
    float originValues[] = { 1, 1, 1, 0 };
    s21_decimal src1, src2;
    int a, b;
    for (int i = 0; i < 4; i++) {
        a = valuesA[i];
        b = valuesB[i];
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        ck_assert_int_eq(s21_is_less(src1, src2), originValues[i]);
        }
} END_TEST
/*-----------Less_or_equal-----------*/
START_TEST(s21_decimal_test_less_or_equal) {
    float valuesA[] = { 11240, 1, 12.4124, 1E+03 };
    float valuesB[] = { 11240, 0, 1.6532, 1E+04 };
    float originValues[] = { 0, 1, 1, 0 };
    s21_decimal src1, src2;
    int a, b;
    for (int i = 0; i < 4; i++) {
        a = valuesA[i];
        b = valuesB[i];
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        ck_assert_int_eq(s21_is_less_or_equal(src1, src2), originValues[i]);
        }
} END_TEST
/*-----------Greater than-----------*/
START_TEST(s21_decimal_test_greather) {
    float valuesA[] = { 11241, 1, 12.4124, 1E+03 };
    float valuesB[] = { 11240, 0, 1.6532, 1E+04 };
    float originValues[] = { 0, 0, 0, 1 };
    s21_decimal src1, src2;
    int a, b;
    for (int i = 0; i < 1; i++) {
        a = valuesA[i];
        b = valuesB[i];
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        ck_assert_int_eq(s21_is_greater(src1, src2), originValues[i]);
        }
} END_TEST
/*-----------Greater than or equal to-----------*/
START_TEST(s21_decimal_test_greather_or_equal) {
    float valuesA[] = { 11240, 1, 12.4124, 1E+03 };
    float valuesB[] = { 11240, 0, 1.6532, 1E+04 };
    float originValues[] = { 0, 0, 0, 1 };
    s21_decimal src1, src2;
    int a, b;
    for (int i = 0; i < 4; i++) {
        a = valuesA[i];
        b = valuesB[i];
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        ck_assert_int_eq(s21_is_greater_or_equal(src1, src2), originValues[i]);
        }
} END_TEST
/*-----------Equal to-----------*/
START_TEST(s21_decimal_test_equal_to) {
    float valuesA[] = {11240, 1, 12.4124, 1E+03 };
    float valuesB[] = { 11240, 0, 1.6532, 1E+04 };
    float originValues[] = { 0, 1, 1, 1 };
    s21_decimal src1, src2;
    int a, b;
    for (int i = 0; i < 4; i++) {
        a = valuesA[i];
        b = valuesB[i];
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        ck_assert_int_eq(s21_is_equal(src1, src2), originValues[i]);
        }
} END_TEST
/*-----------Not equal to-----------*/
START_TEST(s21_decimal_test_is_not_equal_to) {
    float valuesA[] = { 11240, 1, 12.4124, 1E+04 };
    float valuesB[] = { 1120, 0, 1.6532, 1E+04 };
    float originValues[] = { 0, 0, 0, 1 };
    s21_decimal src1, src2;
    int a, b;
    for (int i = 0; i < 4; i++) {
        a = valuesA[i];
        b = valuesB[i];
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        ck_assert_int_eq(s21_is_not_equal(src1, src2), originValues[i]);
        }
} END_TEST
/*-----------Check before sub-----------*/
START_TEST(s21_decimal_test_check_before_sub) {
    float valuesA[] = { -2147483647, 0, 22.22, -22.22 };
    float valuesB[] = { 2147483647, 1, 2, -22.22 };
    float originValues[] = { 2, 0, 11.11, 1 };
    int values[] = { 1, 1, 1, 1 };
    float a, b, c;
    s21_decimal src1, src2, src3;
    for (int i = 0; i < 4; i++) {
        a = valuesA[i];
        b = valuesB[i];
        c = originValues[i];
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        s21_from_float_to_decimal(c, &src3);
        ck_assert_int_eq(check_before_sub(src1, src2, &src3), values[i]);
        }
} END_TEST
START_TEST(s21_decimal_shift) {
        float a = 100;
        float res;
        float res_origin = 50.000000;
        s21_decimal src1;
        s21_from_float_to_decimal(a, &src1);
        shift(&src1, -1);
        s21_from_decimal_to_float(src1, &res);
        ck_assert_float_eq(res_origin, res);
} END_TEST
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
    tcase_add_test(s21_decimal_tests2, s21_decimal_test_less);
    tcase_add_test(s21_decimal_tests2, s21_decimal_test_less_or_equal);
    tcase_add_test(s21_decimal_tests2,   s21_decimal_test_greather);
    tcase_add_test(s21_decimal_tests2,   s21_decimal_test_greather_or_equal);
    tcase_add_test(s21_decimal_tests2,   s21_decimal_test_equal_to);
    tcase_add_test(s21_decimal_tests2,   s21_decimal_test_is_not_equal_to);
    tcase_add_test(s21_decimal_tests2,   s21_decimal_test_check_before_sub);
    Suite *s3 = suite_create("Arithmetic Operators");
    TCase *s21_decimal_tests3 = tcase_create("Tests");
    suite_add_tcase(s3, s21_decimal_tests3);
    tcase_add_test(s21_decimal_tests3, s21_decimal_test_add);
    tcase_add_test(s21_decimal_tests3, s21_decimal_test_sub);
    tcase_add_test(s21_decimal_tests3, s21_decimal_test_mult);
    tcase_add_test(s21_decimal_tests3, s21_decimal_test_mult1);
    tcase_add_test(s21_decimal_tests3, s21_decimal_test_mult2);
    tcase_add_test(s21_decimal_tests3, s21_decimal_test_mult3);
    tcase_add_test(s21_decimal_tests3, s21_decimal_test_mult4);
    tcase_add_test(s21_decimal_tests3, s21_decimal_test_div);
    tcase_add_test(s21_decimal_tests3, s21_decimal_test_div1);
    tcase_add_test(s21_decimal_tests3, s21_decimal_test_mod);
     tcase_add_test(s21_decimal_tests3, s21_decimal_test_mod1);
    tcase_add_test(s21_decimal_tests3, s21_decimal_shift);
    tcase_add_test(s21_decimal_tests3, s21_decimal_test_add1);
    tcase_add_test(s21_decimal_tests3, s21_decimal_test_sub2);
    tcase_add_test(s21_decimal_tests3, s21_decimal_test_mult5);
    tcase_add_test(s21_decimal_tests3, s21_decimal_test_mult6);
    tcase_add_test(s21_decimal_tests3, s21_decimal_test_mult7);
    tcase_add_test(s21_decimal_tests3, s21_decimal_test_nan);
    Suite *s4 = suite_create("Another functions");
    TCase *s21_decimal_tests4 = tcase_create("Tests");
    suite_add_tcase(s4, s21_decimal_tests4);
    tcase_add_test(s21_decimal_tests4, s21_decimal_test_negate);
    tcase_add_test(s21_decimal_tests4, s21_decimal_test_truncate);
    tcase_add_test(s21_decimal_tests4, s21_decimal_test_truncate1);
    tcase_add_test(s21_decimal_tests4, s21_decimal_test_round);
    tcase_add_test(s21_decimal_tests4, s21_decimal_test_floor);
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
