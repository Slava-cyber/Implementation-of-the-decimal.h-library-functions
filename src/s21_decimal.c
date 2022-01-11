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

    // операции над decimal s21_
s21_decimal s21_add(s21_decimal decimalFirst, s21_decimal decimalSecond);
s21_decimal s21_sub(s21_decimal decimalFirst, s21_decimal decimalSecond);
s21_decimal s21_mul(s21_decimal decimalFirst, s21_decimal decimalSecond);

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

// операции над decimal проверка граничных условий
int check_before_add(s21_decimal first, s21_decimal second, s21_decimal *result);
int check_before_sub(s21_decimal first, s21_decimal second, s21_decimal *result);

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


int main() {
    float b = 0;
    //float a = 0.00035063;
    int d1 = 443;
    float a1 = 123;
    float a2 = 12E-26;
    printf("a:%f\n", a1);
    s21_decimal decimal1, decimal2, decimal3;
    init_decimal(&decimal3);
    //s21_from_int_to_decimal(d1, &decimal1);
    s21_from_float_to_decimal(a1, &decimal1);
    s21_from_float_to_decimal(a2, &decimal2);
    
    decimal3 = s21_mul(decimal1, decimal2);

    //additional_code(&decimal3);

    printf("\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimal3));
    printf("\n");  

    printf("less:%d\n", s21_is_greater_or_equal(decimal1, decimal2));

    s21_from_decimal_to_float(decimal3, &b);
    printf("b:%f\n",b);
    printf("bas:%f\n", a1 * a2);
    return 0;
}


// int add_array(int *first, int *second) {
//     int inMind = 0, sum = 0;
//     for (int i = 0; i < 200; i++) {
//         sum = inMind + first[i] + second[i];
//         inMind = 0
//         if (sum == 3 || sum == 1)
//             second[i] = 1;
//         else 
//             second[i] = 0;
//         if (sum >= 2)
//             inMind = 1;
//     }
//     return 1;
// }

// int delete_array(int *array) {
//     for (int i = 0; i < 200; i++)
//         array[i] = 0;
//     return 1;
// }

int multiply(s21_decimal decimalFirst, s21_decimal decimalSecond, s21_decimal *decimalResult) {
    int inf = 0;
    s21_decimal decimalBuffer;
    rewrite_decimal(decimalFirst, &decimalBuffer);
    for (int i = 0; i <= 95; i++) {
        if (check_bit(i, decimalSecond))
            inf += simple_add(*decimalResult, decimalBuffer, decimalResult);
        if (i != 95)
            inf += simple_add(decimalBuffer, decimalBuffer, &decimalBuffer);
    }
    if (inf)
        decimalResult->value_type = s21_INFINITY;
    return inf;
}

// оператор *
s21_decimal s21_mul(s21_decimal decimalFirst, s21_decimal decimalSecond) {
    s21_decimal decimalResult, decimalCompare;
    init_decimal(&decimalResult);
    int sign = (check_bit(127, decimalFirst) + check_bit(127, decimalSecond)) % 2;
    int scaleFirst = get_ten_power(decimalFirst);
    int scaleSecond = get_ten_power(decimalSecond);
    int scale = scaleFirst + scaleSecond;
    int inf = multiply(decimalFirst, decimalSecond, &decimalResult);
    if (decimalResult.value_type != s21_INFINITY && scale <= 28) {
        set_ten_power(scale, &decimalResult);
        if (sign)
            set_bit(127, &decimalResult);
        decimalResult.value_type = s21_NORMAL_VALUE;
    } else if (decimalResult.value_type != s21_INFINITY && scale > 28) {
        // делим на 10 и уменьшаем скейл сравнивая с нулем
    } else if (decimalResult.value_type == s21_INFINITY && scale != 0) {
        // сравниваем числа
        // большее делим на 10 понижая суммарный скейл на 10
        // снова пытаемся умножить
    } else if (decimalResult.value_type == s21_INFINITY && scale == 0) {
        init_decimal(&decimalResult);
        if (sign)
            decimalResult.value_type == s21_NEGATIVE_INFINITY;
        else 
            decimalResult.value_type == s21_INFINITY;   
    }
    return decimalResult;
}


// вычитание через доп код
int subtraction(s21_decimal decimalFirst, s21_decimal decimalSecond, s21_decimal *decimalResult) {
    
                printf("\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimalSecond));
    printf("\n");  
    
    additional_code(&decimalSecond);

        printf("\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimalSecond));
    printf("\n");  

        printf("\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimalFirst));
    printf("\n");  

    simple_add(decimalFirst, decimalSecond, decimalResult);

            printf("\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, *decimalResult));
    printf("\n");  
    decimalResult->value_type = s21_NORMAL_VALUE;
    return 1;
}

// оператор - 
s21_decimal s21_sub(s21_decimal decimalFirst, s21_decimal decimalSecond) {
    s21_decimal decimalResult;
    init_decimal(&decimalResult);
    if (check_bit(127, decimalSecond))
        delete_bit(127, &decimalSecond);
    else 
        set_bit(127, &decimalSecond);
    decimalResult = s21_add(decimalFirst, decimalSecond);
    return decimalResult;
}

// перевод в доп код
int additional_code(s21_decimal *decimal) {
    s21_decimal decimalBuffer;
    for (int i = 0; i < 3; i++)
        decimal->bits[i] = ~decimal->bits[i];
    s21_from_int_to_decimal(1, &decimalBuffer);
    simple_add(*decimal, decimalBuffer, decimal);
    return 1;
}

int substraction_part(s21_decimal decimalFirst, s21_decimal decimalSecond, s21_decimal *decimalResult) {
    delete_bit(127, &decimalFirst);
    int scale = convert_equal_scale(&decimalFirst, &decimalSecond);
    if (!s21_is_less(decimalFirst, decimalSecond)) {
        printf("q\n");
        subtraction(decimalSecond, decimalFirst, decimalResult);
    } else if (!s21_is_not_equal(decimalFirst, decimalSecond)) {
        printf("q1\n");
        subtraction(decimalFirst, decimalSecond, decimalResult);
        set_bit(127, decimalResult);
    } else {
        init_decimal(decimalResult);
    }
    set_ten_power(scale, decimalResult);
}


// сложение 2 decimal
s21_decimal s21_add(s21_decimal decimalFirst, s21_decimal decimalSecond) {
    s21_decimal decimalResult, decimalFirstBuffer, decimalSecondBuffer;
    init_decimal(&decimalResult);
    init_decimal(&decimalFirstBuffer);
    init_decimal(&decimalSecondBuffer);
    rewrite_decimal(decimalFirst, &decimalFirstBuffer);
    rewrite_decimal(decimalSecond, &decimalSecondBuffer);
    if (check_before_add(decimalFirst, decimalSecond, &decimalResult)) {
        int scale, inf;
        int signFirst = check_bit(127, decimalFirst);
        int signSecond = check_bit(127, decimalSecond);
        int signEqual = (signFirst + signSecond) % 2;
        if (!signEqual) {
            scale = convert_equal_scale(&decimalFirst, &decimalSecond);
            if (decimalFirst.value_type == s21_INFINITY) {
                printf("1\n");
                rewrite_decimal(decimalFirstBuffer, &decimalResult);
                decimalResult.value_type = s21_NORMAL_VALUE;
            } else if (decimalSecond.value_type == s21_INFINITY) {
                printf("2\n");
                rewrite_decimal(decimalSecondBuffer, &decimalResult);
                decimalResult.value_type = s21_NORMAL_VALUE;
            } else {
                printf("3\n");
                printf("scale:%d\n", scale);
                set_ten_power(scale, &decimalResult);
                inf = simple_add(decimalFirst, decimalSecond, &decimalResult);
                if (inf) {
                    if (signFirst)
                        decimalResult.value_type = s21_NEGATIVE_INFINITY;
                    else
                        decimalResult.value_type = s21_INFINITY;
                }
            }
            if (signFirst)
                set_bit(127, &decimalResult);
        } else {
            if (signFirst) {
                printf("4\n");
                substraction_part(decimalFirst,decimalSecond, &decimalResult);
            } else {
                substraction_part(decimalSecond, decimalFirst, &decimalResult);
            }
        }
    }
    return decimalResult;
}

// берем scale
int get_ten_power(s21_decimal decimal) {
    int tenPower = 0;
    for (int i = 119; i >= 112; i--)
        tenPower += check_bit(i, decimal) * pow(2, i - 112);
    return tenPower;
}

// устанавливаем scale
int set_ten_power(int tenPower, s21_decimal *decimal) {
    for (int i = 112; i <= 119; i++) {
        delete_bit(i, decimal);
        if (check_bit_number(tenPower, i - 112))
            set_bit(i, decimal);
    }
    return 1;
}

// переписываем decimal аналог присвоения
int rewrite_decimal(s21_decimal decimalFirst, s21_decimal *decimalSecond) {
    for (int i = 0; i < 128; i++) {
        delete_bit(i, decimalSecond);
        if (check_bit(i, decimalFirst))
            set_bit(i, decimalSecond);
    }
    return 1;
}

// повышаем scale на 1 // домнажаем decimal на 10
int multiply_ten(s21_decimal decimal, s21_decimal *decimalBuffer) {
    int result = 0;
    for (int i = 1; i < 10; i++)
        result += simple_add(*decimalBuffer, decimal, decimalBuffer);
    return result;
}

// выравниваем scale / на выходе 2 decimal с одинаковым scale
int convert_equal_scale(s21_decimal *decimalFirst, s21_decimal *decimalSecond) {
    s21_decimal decimalSecondBuffer;
    decimalSecondBuffer.value_type = s21_NORMAL_VALUE;
    init_decimal(&decimalSecondBuffer);
    int scaleFirst = get_ten_power(*decimalFirst);
    int scaleSecond = get_ten_power(*decimalSecond);
    int scale = scaleFirst;
    int inf = 0;
    printf("scaleFirst:%d\n", scaleFirst);
    printf("scaleSecond:%d\n", scaleSecond);
    if (scaleFirst > scaleSecond && scaleFirst <= 28) {
            /*    printf("\n");
        for (int i = 127; i >= 0; i--)
            printf("%d", check_bit(i, *decimalSecond));
        printf("\n");  */  

        rewrite_decimal(*decimalSecond, &decimalSecondBuffer);
        
        /*        printf("\n");
        for (int i = 127; i >= 0; i--)
            printf("%d", check_bit(i, decimalSecondBuffer));
        printf("\n");  */
        for (int i = scaleSecond; i < scaleFirst; i++) {
                inf = multiply_ten(decimalSecondBuffer, &decimalSecondBuffer);                        
        /*printf("i:%d\n", i);
        for (int i = 127; i >= 0; i--)
            printf("%d", check_bit(i, decimalSecondBuffer));
        printf("\n");  */
        }
        if (inf)
            decimalSecond->value_type = s21_INFINITY;
        
        /*        printf("\n");
        for (int i = 127; i >= 0; i--)
            printf("%d", check_bit(i, decimalSecondBuffer));
        printf("\n");  */
        rewrite_decimal(decimalSecondBuffer, decimalSecond);
        set_ten_power(scaleFirst, decimalSecond);
        scale = scaleFirst;
        /*printf("\n");
        for (int i = 127; i >= 0; i--)
            printf("%d", check_bit(i, *decimalSecond));
        printf("\n");    */
    } else if (scaleFirst < scaleSecond && scaleSecond <= 28) {
        rewrite_decimal(*decimalFirst, &decimalSecondBuffer);
        for (int i = scaleFirst; i < scaleSecond; i++)
                inf = multiply_ten(decimalSecondBuffer, &decimalSecondBuffer);
        if (inf)
            decimalFirst->value_type = s21_INFINITY;

        rewrite_decimal(decimalSecondBuffer, decimalFirst);
        set_ten_power(scaleSecond, decimalFirst);
        scale = scaleSecond;
    }
    return scale;
}


// сложение двух decimal с одинаковым scale и одинаковым знаком
int simple_add(s21_decimal decimalFirst, s21_decimal decimalSecond, s21_decimal *decimalResult) {
    int inMind = 0, sum = 0;
    for (int i = 0; i <= 95; i++) {
        sum = check_bit(i, decimalFirst) + check_bit(i, decimalSecond) + inMind;
        inMind = 0;
        if (sum == 3 || sum == 1)
            set_bit(i, decimalResult);
        else 
            delete_bit(i, decimalResult);
        if (sum >= 2)
            inMind = 1;
    }
    /*if (inMind) {
        init_decimal(decimalResult);
        decimalResult->value_type = s21_INFINITY;
    }*/
    return inMind;
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

// зануляем бит
int delete_bit(int position, s21_decimal *dst) {
    int SetBitsArray = position / 32;
    int SetBit = position % 32;
    dst->bits[SetBitsArray] = dst->bits[SetBitsArray] & ~(1 << SetBit);
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

// проверка на граничные условия перед вычитанием
int check_before_sub(s21_decimal first, s21_decimal second, s21_decimal *result) {
    int done = 1;
    if ((first.value_type == s21_NAN || second.value_type == s21_NAN)) {
        result->value_type = s21_NAN;
        done = 0;
    } else if (first.value_type != s21_NORMAL_VALUE &&
               second.value_type != s21_NORMAL_VALUE) {
        if (first.value_type == second.value_type) {
            result->value_type = s21_NAN;
        } else {
            result->value_type = first.value_type;
        }
        done = 0;
    } else if (first.value_type == s21_NORMAL_VALUE &&
               second.value_type != s21_NORMAL_VALUE) {
        result->value_type = second.value_type == s21_NEGATIVE_INFINITY
                             ? s21_INFINITY
                             : s21_NEGATIVE_INFINITY;
        done = 0;
    } else if (first.value_type != s21_NORMAL_VALUE &&
               second.value_type == s21_NORMAL_VALUE) {
        result->value_type = first.value_type;
        done = 0;
    }
    return done;
}

// проверка на граничные условия перед сложением
int check_before_add(s21_decimal first, s21_decimal second, s21_decimal *result) {
    int done = 1;
    if ((first.value_type == s21_NAN || second.value_type == s21_NAN) ||
        (first.value_type == s21_INFINITY &&
         second.value_type == s21_NEGATIVE_INFINITY) ||
        (first.value_type == s21_NEGATIVE_INFINITY &&
         second.value_type == s21_INFINITY)) {
        result->value_type = s21_NAN;
        done = 0;
    } else if (first.value_type == s21_INFINITY ||
               second.value_type == s21_INFINITY) {
        result->value_type = s21_INFINITY;
        done = 0;
    } else if (first.value_type == s21_NEGATIVE_INFINITY ||
               second.value_type == s21_NEGATIVE_INFINITY) {
        result->value_type = s21_NEGATIVE_INFINITY;
        done = 0;
    } else if (first.value_type == s21_NORMAL_VALUE && second.value_type != s21_NORMAL_VALUE) {
        result->value_type = second.value_type;
        done = 0;
    } else if (first.value_type != s21_NORMAL_VALUE && second.value_type == s21_NORMAL_VALUE) {
        result->value_type = first.value_type;
        done = 0;
    }
    return done;
}

// сравнение decimal на гран условиях для <
int compare_board_condition(s21_decimal decimalFirst, s21_decimal decimalSecond) {
    int result = 1;
    if (decimalFirst.value_type == s21_NEGATIVE_INFINITY &&
       (decimalSecond.value_type == s21_INFINITY || 
        decimalSecond.value_type == s21_NORMAL_VALUE)) {
        result = 0;
    } else if (decimalSecond.value_type == s21_NEGATIVE_INFINITY && 
              (decimalFirst.value_type == s21_INFINITY || 
               decimalFirst.value_type == s21_NORMAL_VALUE)) {
        result = 1;
    } else if (decimalFirst.value_type == s21_NAN || decimalSecond.value_type == s21_NAN) {
        result = 1;
    } else if ((decimalFirst.value_type == s21_NEGATIVE_INFINITY && 
                decimalSecond.value_type == s21_NEGATIVE_INFINITY) ||
               (decimalFirst.value_type == s21_INFINITY && 
                decimalSecond.value_type == s21_INFINITY)) {
        result = 1;
    } else if (decimalFirst.value_type == s21_INFINITY &&
               decimalSecond.value_type == s21_NORMAL_VALUE) {
        result = 1;
    } else if (decimalFirst.value_type == s21_NORMAL_VALUE &&
               decimalSecond.value_type == s21_INFINITY) {
        result = 0;
    } else if (decimalFirst.value_type == s21_NORMAL_VALUE &&
               decimalSecond.value_type == s21_NORMAL_VALUE) {
        result = -1;
    }
    return result; 
}

// оператор <
int s21_is_less(s21_decimal decimalFirst, s21_decimal decimalSecond) {
    int signFirst = check_bit(127, decimalFirst);
    int signSecond = check_bit(127, decimalSecond);
    int result = compare_board_condition(decimalFirst, decimalSecond);
    if (result == -1) {
        if (signFirst > signSecond) {
            result = 0;
        } else if (signSecond > signFirst) {
            result = 1;
        } else {
            printf("tut\n");
            convert_equal_scale(&decimalFirst, &decimalSecond);
            if (decimalFirst.value_type == s21_INFINITY) {
                if (signFirst)
                    result = 0;
                else 
                    result = 1;
            } else if (decimalSecond.value_type == s21_INFINITY) {
                if (signFirst)
                    result = 1;
                else 
                    result = 0;
            } else {
                result = compare_decimal(decimalFirst, decimalSecond);
                if ((result == -1 && !signFirst) || (result == 1 && signFirst)) {
                    result = 0;
                } else {
                    result = 1;
                }
            }
        }
    }
    return result;
}

// оператор ==
int s21_is_equal(s21_decimal decimalFirst, s21_decimal decimalSecond) {
    int result = 1;
    if (decimalFirst.value_type == decimalSecond.value_type && 
        decimalFirst.value_type == s21_NORMAL_VALUE) {
        if (check_bit(127, decimalFirst) == check_bit(127, decimalSecond)) {
            convert_equal_scale(&decimalFirst, &decimalSecond);
            if (decimalFirst.value_type != s21_INFINITY && 
                decimalSecond.value_type != s21_INFINITY) {
                if (!compare_decimal(decimalFirst, decimalSecond))
                    result = 0;
            }
        }
    } else if (decimalFirst.value_type == decimalSecond.value_type && 
               decimalFirst.value_type != s21_NAN) {
        result  = 0;
    }
    return result;
}

// оператор !=
int s21_is_not_equal(s21_decimal decimalFirst, s21_decimal decimalSecond) {
    int result = 1;
    if (s21_is_equal(decimalFirst, decimalSecond))
        result = 0;
    return result;
}

// оператор >
int s21_is_greater(s21_decimal decimalFirst, s21_decimal decimalSecond) {
    int result = 1;
    if (s21_is_less(decimalFirst, decimalSecond)) 
        result = 0;
    return result;
}

// сравнение только самих чисел decimal возвращает 1 если 1>2 и возвращает -1 если 1<2 и вовращает 0 если 1==2
int compare_decimal(s21_decimal decimalFirst, s21_decimal decimalSecond) {
    int result;
    for (int i = 95; i >= 0; i--){
        result = check_bit(i, decimalFirst) - check_bit(i, decimalSecond);
        if (result != 0)
            break;
    }
    return result;
}

// оператор <=
int s21_is_less_or_equal(s21_decimal decimalFirst, s21_decimal decimalSecond) {
    int result = s21_is_less(decimalFirst, decimalSecond);
    if (!s21_is_equal(decimalFirst, decimalSecond))
        result = 0;
    return result;
}

// оператор >=
int s21_is_greater_or_equal(s21_decimal decimalFirst, s21_decimal decimalSecond) {
    int result = s21_is_greater(decimalFirst, decimalSecond);
    if (!s21_is_equal(decimalFirst, decimalSecond))
        result = 0;
    return result;
}
