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

typedef union {
  unsigned int integerValue;
  float floatValue;
} value;

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);

int set_bit(int position, s21_decimal *dst);
int init_decimal(s21_decimal *dst);
int check_bit(int position, s21_decimal dst);
int get_binary_power(value val);
int form_float_decimal(s21_decimal *dst, int binaryPower, int tenPower, value val);

int main() {
float a = 1E24;
s21_decimal decimal;
init_decimal(&decimal);
s21_from_float_to_decimal(a, &decimal);
for (int i = 95; i >= 0; i--) {
    if (check_bit(i, decimal))
    printf("1");
    else 
    printf("0");
}

// value val;
// val.floatValue = (int)a;
// for (int i = 31; i >= 0; i--) {
//     if (val.integerValue & (1 << i))
//     printf("1");
//     else 
//     printf("0");
// }

// printf("\n%d\n", get_binary_power(val));
// for (int i = 31; i >= 0; i--) {
//     if ((a & (1 << i)) == 0)
//         printf("0");
//     else 
//         printf("1");
// }
    // s21_decimal decimal;
    // init_decimal(&decimal);
    // int start = -24;
    // int result = 0;
    // s21_from_int_to_decimal(start, &decimal);
    // s21_from_decimal_to_int(decimal, &result);
    // printf("%d\n%d\n", start, result);
    return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int result = 1;
    int tenPower = 0;
    value val;
    int binaryPower;
    double number = (double) src;
    if (number != 0.0 && dst) {
        for (; !(int)(number / 1E7); number *= 10)
            tenPower += 1;
        val.floatValue = number;
        binaryPower = get_binary_power(val);
        printf("binary:%d\n", binaryPower);
        form_float_decimal(dst, binaryPower, tenPower, val);
    }
    return result;
}


int form_float_decimal(s21_decimal *dst, int binaryPower, int tenPower, value val) {
    if (val.integerValue & (1 << 31))
        set_bit(127, dst);
    set_bit(binaryPower, dst);
    int j = binaryPower;
    for (int i = 22; i >= 0; i--) {
        j--;
        if (val.integerValue & (1 << i))
            set_bit(j, dst);
    }
    return 1;
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

int get_binary_power(value val) {
    int result = 0, mult = 0;
    for (int i = 30; i > 22; i--){
        if ((val.integerValue & (1 << i)) == 0)
            mult = 0;
        else 
            mult = 1;
    result += mult * pow(2, i - 23);
    }
    result -= 127;
    return result;
}