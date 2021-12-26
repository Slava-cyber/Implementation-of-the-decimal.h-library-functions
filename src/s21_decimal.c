#include <stdio.h>
#include <math.h>

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

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);

int set_bit(int position, s21_decimal *dst);
int init_decimal(s21_decimal *dst);
int check_bit(int position, s21_decimal dst);

int main() {
    s21_decimal decimal;
    init_decimal(&decimal);
    int start = -24;
    int result = 0;
    s21_from_int_to_decimal(start, &decimal);
    s21_from_decimal_to_int(decimal, &result);
    printf("%d\n%d\n", start, result);
    return 0;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int result = 1;
    if (dst != NULL) {
        if (src < 0) {
            set_bit(127, dst);
            src = src * (-1);
        }
        dst->bits[0] = src;
    } else {
        result = 0;
    }
    return result;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int result = 1;
    for (int i = 0; i < 32; i++) {
        *dst += pow(2, i) * check_bit(i, src);
    }
    if (check_bit(127, src))
        *dst = *dst * (-1); 
    return result;
}

int check_bit(int position, s21_decimal dst) {
    int check = 0;
    int SetBitsArray = position / 32;
    int SetBit = position % 32;
    if (dst.bits[SetBitsArray] & (1 << SetBit))
        check = 1;
    return check;
}

int set_bit(int position, s21_decimal *dst) {
    int SetBitsArray = position / 32;
    int SetBit = position % 32;
    dst->bits[SetBitsArray] = dst->bits[SetBitsArray] | (1 << SetBit);
    return 1; 
}

int init_decimal(s21_decimal *dst) {
    for (int i = 0; i < 4; i++)
        dst->bits[i] = 0;
    return 1;
}