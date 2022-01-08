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

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int set_bit(int position, s21_decimal *dst);
int init_decimal(s21_decimal *dst);
int check_bit(int position, s21_decimal dst);
int get_binary_power(value val);
int form_float_decimal(s21_decimal *dst, int binaryPower, int tenPower, value val);
void check_value_number_float(float src, s21_decimal *decimal);
int check_bit_number(unsigned int number, int position);

int main() {
float b = 0;
float a = 0.00035063;
printf("a:%f\n", a);
s21_decimal decimal;
s21_from_float_to_decimal(a, &decimal);
s21_from_decimal_to_float(decimal, &b);
printf("b:%f\n",b);
/*for (int i = 127; i >= 0; i--) {
    if (check_bit(i, decimal))
    printf("1");
    else 
    printf("0");
}*/

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

// перевод из decimal в float
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int codeError = 0;
    if (src.value_type == s21_NORMAL_VALUE || dst) {
        double number = 0;
        int tenPower = 0;
        for (int i = 0; i < 96; i++)
            number += check_bit(i, src) * pow(2, i);
        for (int i = 119; i >= 112; i--)
            tenPower += check_bit(i, src) * pow(2, i - 112);
        //printf("number1:%f\n", number);
        for (int i = tenPower; i > 0; i--)
            number = number / 10.0;
        //printf("number2:%f\n", number);
        if (check_bit(127, src))
            number *= -1;
    
        *dst = (float)number;
    } else {
        codeError = 1;
    }
    return codeError; 
}

// перевод float в decimal
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int codeError = 0, tenPower = 0;
    value val;
    int binaryPower;
    double number = (double) src;
    //printf("number:%f\n", number);
    check_value_number_float(number, dst);
    init_decimal(dst);
    val.floatValue = number;
    binaryPower = get_binary_power(val);
    if (dst->value_type == s21_NORMAL_VALUE && dst) {
        //printf("number:%f\n", number);
        if (number != 0.0) {
            for (; !(int)(number / 1E7); number *= 10)
                tenPower += 1;
            if (tenPower <= 28 && (binaryPower > -95 && binaryPower <=95)) {
                val.floatValue = number;
                binaryPower = get_binary_power(val);
                //printf("binary:%d\n", binaryPower);
                //printf("ten:%d\n", tenPower);
                form_float_decimal(dst, binaryPower, tenPower, val);
            } else {
                codeError = 1;
            }
        }
    } else {
        codeError = 1;
    }
    return codeError;
}

// формируем децимал из float
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
    for (int i = 112; tenPower; i++) {
        if (tenPower % 2)
            set_bit(i, dst);
        tenPower /= 2;
    }
return 1;
}

// перевод из int в decimal
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int codeError = 0;
    init_decimal(dst);
    if (dst != NULL) {
        if (src < 0) {
            set_bit(127, dst);
            src = src * (-1);
        }
        dst->bits[0] = src;
        dst->value_type = s21_NORMAL_VALUE;
    } else {
        codeError = 1;
    }
    return codeError;
}

// перевод из decimal в инт
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int codeError = 0;
    if (src.value_type == s21_NORMAL_VALUE) {
        for (int i = 0; i < 32; i++) {
            *dst += pow(2, i) * check_bit(i, src);
        }
        if (check_bit(127, src))
            *dst = *dst * (-1); 
    } else {
        codeError = 1;
    }
    return codeError;
}

// возвращаем значение указанного бита в числе
int check_bit_number(unsigned int number, int position) {
    return (number & (1 << position));
} 

// возвращаем значение указанного бита
int check_bit(int position, s21_decimal dst) {
    int check = 0;
    int SetBitsArray = position / 32;
    int SetBit = position % 32;
    if (dst.bits[SetBitsArray] & (1 << SetBit))
        check = 1;
    return check;
}

// ставим 1 в указанный бит
int set_bit(int position, s21_decimal *dst) {
    int SetBitsArray = position / 32;
    int SetBit = position % 32;
    dst->bits[SetBitsArray] = dst->bits[SetBitsArray] | (1 << SetBit);
    return 1; 
}

// инициализация decimal
int init_decimal(s21_decimal *dst) {
    for (int i = 0; i < 4; i++)
        dst->bits[i] = 0;
    return 1;
}

// берем двоичную степень числа
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

// проверка на граничные условия float при переводе в decimal
void check_value_number_float(float src, s21_decimal *decimal) {
  int sign = check_bit_number((unsigned int)src, 31);
  if (isinf(src) == 1 && sign == 0) {
    decimal->value_type = s21_INFINITY;
  } else if (isinf(src) == 1 && sign == 1) {
    decimal->value_type = s21_NEGATIVE_INFINITY;
  } else if (isnan(src) == 1) {
    decimal->value_type = s21_NAN;
  } else {
    decimal->value_type = s21_NORMAL_VALUE;
  }
}