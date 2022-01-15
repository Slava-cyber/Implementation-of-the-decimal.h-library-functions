#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <stdio.h>
#include <math.h>
#include <limits.h>


typedef enum {
    s21_NORMAL_VALUE = 0,
    s21_INFINITY = 1,
    s21_NEGATIVE_INFINITY = 2,
    s21_NAN = 3
} value_type_t;

typedef struct {
    int bits[4];
    value_type_t value_type;
} s21_decimal;

typedef union {
  unsigned int integerValue;
  float floatValue;
} value;

    // функции конвертации s21_
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// функции конвертации вспомогательные
int set_bit(int position, s21_decimal *dst);
int delete_bit(int position, s21_decimal *dst);
int init_decimal(s21_decimal *dst);
int check_bit(int position, s21_decimal dst);
int get_binary_power(value val);
int form_float_decimal(s21_decimal *dst, int binaryPower, int tenPower, value val);
void check_value_number_float(float src, s21_decimal *decimal);
int check_bit_number(unsigned int number, int position);
int shift(s21_decimal *decimal, int step);
int first_number_position(s21_decimal decimal);

    // операции над decimal s21_
s21_decimal s21_add(s21_decimal decimalFirst, s21_decimal decimalSecond);
s21_decimal s21_sub(s21_decimal decimalFirst, s21_decimal decimalSecond);
s21_decimal s21_mul(s21_decimal decimalFirst, s21_decimal decimalSecond);
s21_decimal s21_div(s21_decimal decimalFirst, s21_decimal decimalSecond);
s21_decimal s21_mod(s21_decimal decimalFirst, s21_decimal decimalSecond);

// операции над decimal вспомогательные
int simple_add(s21_decimal decimalFirst, s21_decimal decimalSecond, s21_decimal *decimalResult);
int get_ten_power(s21_decimal decimal);
int convert_equal_scale(s21_decimal *decimalFirst, s21_decimal *decimalSecond);
int set_ten_power(int tenPower, s21_decimal *decimal);
int rewrite_decimal(s21_decimal decimalFirst, s21_decimal *decimalSecond);
int multiply_ten(s21_decimal decimal, s21_decimal *decimalBuffer);
int additional_code(s21_decimal *decimal);
int subtraction(s21_decimal decimalFirst, s21_decimal decimalSecond, s21_decimal *decimalResult);
int substraction_part(s21_decimal decimalFirst, s21_decimal decimalSecond, s21_decimal *decimalResult);
int multiply(s21_decimal decimalFirst, s21_decimal decimalSecond, s21_decimal *decimalResult);
s21_decimal divide_int(s21_decimal decimalFirst, s21_decimal decimalSecond, s21_decimal *decimalResult);

// операции над decimal проверка граничных условий
int check_before_add(s21_decimal first, s21_decimal second, s21_decimal *result);
int check_before_sub(s21_decimal first, s21_decimal second, s21_decimal *result);
int check_before_mul(s21_decimal first, s21_decimal second, s21_decimal *result);
int check_before_div(s21_decimal first, s21_decimal second, s21_decimal *result);
int check_before_mod(s21_decimal first, s21_decimal second, s21_decimal *result);

    // операторы сравнения s21_
int s21_is_not_equal(s21_decimal decimalFirst, s21_decimal decimalSecond);
int s21_is_equal(s21_decimal decimalFirst, s21_decimal decimalSecond);
int s21_is_greater(s21_decimal decimalFirst, s21_decimal decimalSecond);
int s21_is_less(s21_decimal decimalFirst, s21_decimal decimalSecond);
int s21_is_less_or_equal(s21_decimal decimalFirst, s21_decimal decimalSecond);
int s21_is_greater_or_equal(s21_decimal decimalFirst, s21_decimal decimalSecond);

// операторы сравнение вспомогательные
int compare_board_condition(s21_decimal decimalFirst, s21_decimal decimalSecond);
int compare_decimal(s21_decimal decimalFirst, s21_decimal decimalSecond);


    // другие функции
s21_decimal s21_negate(s21_decimal decimal);
s21_decimal s21_truncate(s21_decimal decimal);
s21_decimal s21_floor(s21_decimal decimal);
s21_decimal s21_round(s21_decimal decimal);

#endif  // SRC_S21_DECIMAL_H_