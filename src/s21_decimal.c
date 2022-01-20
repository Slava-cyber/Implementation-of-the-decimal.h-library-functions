#include"s21_decimal.h"

int main() {
    float b = 0;
    //float a = 0.0003506;
    float d1 = 1;
    float d2 = 3*10e-24;

    float a1 = -0.2332;
    float a2 = -111;
    //printf("a1:%f\n", a1);
    s21_decimal decimal1, decimal2, decimal3;
    init_decimal(&decimal3);
    s21_from_float_to_decimal(a1, &decimal1);
    s21_from_float_to_decimal(a2, &decimal2);
    //set_ten_power(30, &decimal2);
    //        printf("decimal1\n");
    // for (int i = 127; i >= 0; i--)
    // printf("%d", check_bit(i, decimal1));
    // printf("\n");  

    // printf("decimal2\n");
    // for (int i = 127; i >= 0; i--)
    // printf("%d", check_bit(i, decimal2));
    // printf("\n");
        printf("|||||decimal1\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimal1));
    printf("\n");  

    s21_from_decimal_to_float(decimal1, &b);
        printf("b:%.27f\n",b);
      printf("a:%.27f\n",a1);
    decimal3 = s21_div(decimal2, decimal1);
        printf("|||||decimal1\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimal1));
    printf("\n");  

    printf("decimal2\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimal2));
    printf("\n");

    printf("decimal3\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimal3));
    printf("\n");  

    //printf("less:%d\n", s21_is_greater_or_equal(decimal2, decimal1));
    //decimal2 = s21_round(decimal2);
    s21_from_decimal_to_float(decimal3, &b);
    if (decimal3.value_type == s21_NORMAL_VALUE)
        printf("b:%.15f\n",b);
    printf("bas:%f\n", a2 / a1 );
    return 0;
}

// деление целочисленное
s21_decimal divide_int(s21_decimal decimalFirst, s21_decimal decimalSecond, s21_decimal *decimalResult) {
    s21_decimal decimalBuffer;
    init_decimal(&decimalBuffer);
    decimalBuffer.value_type = s21_NORMAL_VALUE;
    
    set_ten_power(get_ten_power(decimalFirst), &decimalBuffer);   

    for (int i = 95; i >= 0; i--) {
        shift(&decimalBuffer, 1);
        if (check_bit(i, decimalFirst)) {
            set_bit(0, &decimalBuffer);
        }
        if (!s21_is_greater_or_equal(decimalBuffer, decimalSecond)) {
            decimalBuffer = s21_sub(decimalBuffer, decimalSecond);
            //set_ten_power(scale, &decimalBuffer);
            shift(decimalResult, 1);
            set_bit(0, decimalResult);
        } else {
            shift(decimalResult, 1);
        }
    }
    set_ten_power(0, decimalResult);
    return decimalBuffer;
}
// формирование дробной части при делении
int divide_fractional(s21_decimal decimalRemainder, s21_decimal decimalSecond, s21_decimal *decimalResult) {
    s21_decimal decimalBuffer;
    init_decimal(&decimalBuffer);
    decimalBuffer.value_type = s21_NORMAL_VALUE;

    s21_decimal decimalBuffer2;
    init_decimal(&decimalBuffer2);
    decimalBuffer2.value_type = s21_NORMAL_VALUE;

    s21_decimal decimalTen;
    init_decimal(&decimalTen);
    decimalTen.value_type = s21_NORMAL_VALUE;
    s21_from_int_to_decimal(10, &decimalTen);


    s21_decimal decimalZero;
    init_decimal(&decimalZero);
    decimalZero.value_type = s21_NORMAL_VALUE;
    s21_from_int_to_decimal(0, &decimalZero);

                printf("decimalTen\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimalTen));
    printf("\n");
            printf("decimalSecond\n");

           printf("decimalRemainder\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimalRemainder));
    printf("\n");
            printf("decimalSecond\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimalSecond));
    printf("\n");
                printf("decimalResult\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, *decimalResult));
    printf("\n");

    int scale = get_ten_power(*decimalResult);
    int inf;
    while (scale <= 28 && !s21_is_not_equal(decimalZero, decimalRemainder)) {
        //init_decimal(&decimalBuffer);
        decimalRemainder = s21_mul(decimalTen, decimalRemainder);
        decimalBuffer = *decimalResult;
        inf = multiply_ten(*decimalResult, &decimalBuffer);
        
        if (!inf) {
            //multiply(*decimalResult, decimalTen, decimalResult);
            multiply_ten(*decimalResult, decimalResult);
            scale += 1;
        } else {
            break;
        }


                printf("decimalBufferbefore\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimalBuffer));
    printf("\n");

    //         printf("decimalRemainder\n");
    // for (int i = 127; i >= 0; i--)
    // printf("%d", check_bit(i, decimalRemainder));
    // printf("\n");

        if (!s21_is_greater_or_equal(decimalRemainder, decimalSecond)) {
            printf("gg\n");
            decimalRemainder = divide_int(decimalRemainder, decimalSecond, &decimalBuffer);
            inf = simple_add(decimalBuffer, *decimalResult, &decimalBuffer2);

            if (!inf) {
                simple_add(decimalBuffer, *decimalResult, decimalResult);
            } else {
                break;
            }

            printf("decimalBuffer\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimalBuffer));
    printf("\n");


            printf("decimalRemainder\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimalRemainder));
    printf("\n");


                printf("decimalResult\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, *decimalResult));
    printf("\n");

        }
    }
    set_ten_power(scale, decimalResult);
    return 1;
}
// оператор /
s21_decimal s21_div(s21_decimal decimalFirst, s21_decimal decimalSecond) {
    s21_decimal decimalOne;
    init_decimal(&decimalOne);
    decimalOne.value_type = s21_NORMAL_VALUE;
    s21_from_int_to_decimal(1, &decimalOne);

    s21_decimal decimalResult;
    init_decimal(&decimalResult);
    decimalResult.value_type = s21_NORMAL_VALUE;
    

    if (check_before_div(decimalFirst, decimalSecond, &decimalResult)) {
        int sign = (check_bit(127, decimalFirst) + check_bit(127, decimalSecond)) % 2;
        delete_bit(127, &decimalFirst);
        delete_bit(127, &decimalSecond);
        printf("ggggg\n");
        if (!s21_is_less(decimalSecond, decimalOne)) {
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            int scale = get_ten_power(decimalSecond);
            set_ten_power(0, &decimalSecond);
            decimalResult = div_algoritm(decimalFirst, decimalSecond);
            printf("scaleResult:%d\n", get_ten_power(decimalResult));
            s21_decimal decimalScale;
            init_decimal(&decimalScale);
            decimalScale.value_type = s21_NORMAL_VALUE;
            s21_from_int_to_decimal(10, &decimalScale);
            printf("scale:%d\n", scale);
            for (int i = 1; i < scale; i++)
                multiply_ten(decimalScale, &decimalScale);

                printf("decimalScale\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimalScale));
    printf("\n");


                printf("decimalResult\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimalResult));
    printf("\n");

            decimalResult = s21_mul(decimalResult, decimalScale);
        } else {
            decimalResult = div_algoritm(decimalFirst, decimalSecond);
      }
              if (sign)
            set_bit(127, &decimalResult);
    }
    return decimalResult;
}
// оператор /
s21_decimal div_algoritm(s21_decimal decimalFirst, s21_decimal decimalSecond) {
    s21_decimal decimalZero;
    init_decimal(&decimalZero);
    decimalZero.value_type = s21_NORMAL_VALUE;
    s21_from_int_to_decimal(0, &decimalZero);

    s21_decimal decimalResult;
    init_decimal(&decimalResult);
    decimalResult.value_type = s21_NORMAL_VALUE;
    
    s21_decimal decimalRemainder;
    init_decimal(&decimalRemainder);
    decimalRemainder.value_type = s21_NORMAL_VALUE;

    //int sign = (check_bit(127, decimalFirst) + check_bit(127, decimalSecond)) % 2;
        delete_bit(127, &decimalSecond);
        convert_equal_scale(&decimalFirst, &decimalSecond);
        get_ten_power(decimalFirst);
        decimalRemainder = divide_int(decimalFirst, decimalSecond, &decimalResult);
        if (!s21_is_not_equal(decimalRemainder, decimalZero))
            divide_fractional(decimalRemainder, decimalSecond, &decimalResult);
        // if (sign)
        //     set_bit(127, &decimalResult);
    return decimalResult;
}
// оператор mod
s21_decimal s21_mod(s21_decimal decimalFirst, s21_decimal decimalSecond) {
    s21_decimal decimalResult;
    init_decimal(&decimalResult);
    if (check_before_mod(decimalFirst, decimalSecond, &decimalResult)) {
        int sign = (check_bit(127, decimalFirst) + check_bit(127, decimalSecond)) % 2;
        s21_decimal decimalDivision;
        delete_bit(127, &decimalSecond);
        convert_equal_scale(&decimalFirst, &decimalSecond);
         get_ten_power(decimalFirst);
        // rewrite_decimal(divide_int(decimalFirst, decimalSecond, &decimalDivision), &decimalResult);
        decimalResult = divide_int(decimalFirst, decimalSecond, &decimalDivision);
        if (sign)
            set_bit(127, &decimalResult);
    }
    return decimalResult;
}
// умножение алгоритм
int multiply(s21_decimal decimalFirst, s21_decimal decimalSecond, s21_decimal *decimalResult) {
    int inf = 0;
    s21_decimal decimalBuffer;
    rewrite_decimal(decimalFirst, &decimalBuffer);
    int position;
    for (position = 95; position >= 0; position--)
        if (check_bit(position, decimalSecond))  
            break;

    for (int i = 0; i <= position; i++) {
        if (check_bit(i, decimalSecond))
            inf += simple_add(*decimalResult, decimalBuffer, decimalResult);
        if (i != 95)
            inf += simple_add(decimalBuffer, decimalBuffer, &decimalBuffer);
        /*printf("\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimalBuffer));
    printf("\n"); */
    }
    return inf;
}
// оператор *
s21_decimal s21_mul(s21_decimal decimalFirst, s21_decimal decimalSecond) {
            s21_decimal decimalFirstBuffer;
    init_decimal(&decimalFirstBuffer);
        s21_decimal decimalSecondBuffer;
    init_decimal(&decimalSecondBuffer);
        decimalFirstBuffer.value_type = s21_NORMAL_VALUE;
            decimalSecondBuffer.value_type = s21_NORMAL_VALUE;
    s21_decimal decimalResult;
    init_decimal(&decimalResult);
    decimalResult.value_type = s21_NORMAL_VALUE;
    int sign = (check_bit(127, decimalFirst) + check_bit(127, decimalSecond)) % 2;
    delete_bit(127, &decimalFirst);
    delete_bit(127, &decimalSecond);
    int scaleFirst = get_ten_power(decimalFirst);
    int scaleSecond = get_ten_power(decimalSecond);
    int scale = scaleFirst + scaleSecond;
    int inf = multiply(decimalFirst, decimalSecond, &decimalResult);

    
    if (check_before_mul(decimalFirst, decimalSecond, &decimalResult)) {
        if (!inf && scale <= 28) {
            // printf("tuta\n");
            set_ten_power(scale, &decimalResult);
            if (sign)
                set_bit(127, &decimalResult);
            decimalResult.value_type = s21_NORMAL_VALUE;
        } else if (!inf && scale > 28) {
            s21_decimal decimalOne;
            init_decimal(&decimalOne);
            s21_from_int_to_decimal(10, &decimalOne);
            // printf("!!!\n");
            while (scale > 28) {
                divide_int(decimalResult, decimalOne, &decimalResult);
                scale -= 1;
                set_ten_power(scale, &decimalResult);
            }
            decimalResult.value_type = s21_NORMAL_VALUE;
            // делим на 10 и уменьшаем скейл сравнивая с нулем
        } else if (inf && scale != 0) {
             printf("new!\n");
            s21_decimal decimalOne;
            init_decimal(&decimalOne);
            s21_from_int_to_decimal(10, &decimalOne);
            while (inf && scale != 0) {
                // decimalSecondBuffer = decimalSecond;
                // decimalFirstBuffer = decimalFirst;
                // set_ten_power(0, &decimalSecondBuffer);
                // set_ten_power(0, &decimalFirstBuffer);
                if (!s21_is_greater(decimalFirst, decimalSecond)) {
                    set_ten_power(0, &decimalFirst);
                    divide_int(decimalFirst, decimalOne, &decimalFirst);
                    if (scaleFirst) {
                        scaleFirst -= 1;
                        set_ten_power(scaleFirst-1, &decimalFirst);
                    }
                } else {
                    set_ten_power(0, &decimalSecond);
                    divide_int(decimalSecond, decimalOne, &decimalSecond);
                    if (scaleSecond) {
                        scaleSecond -= 1;
                        set_ten_power(scaleSecond-1, &decimalSecond);
                    }
                }
                init_decimal(&decimalResult);
                decimalResult.value_type = s21_NORMAL_VALUE;
                inf = multiply(decimalFirst, decimalSecond, &decimalResult);
                scale -= 1;
                set_ten_power(scale, &decimalResult);
                 printf("scaleFirst:%d\n", scaleFirst);
                 
                 printf("scale:%d\n", scale);
                printf("decimalResult\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimalResult));
    printf("\n");

                printf("decimalFirst\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimalFirst));
    printf("\n");

                printf("decimalSecond\n");
    for (int i = 127; i >= 0; i--)
    printf("%d", check_bit(i, decimalSecond));
    printf("\n");

            }
            printf("scale:%d\n", scale);
            // сравниваем числа
            // большее делим на 10 понижая суммарный скейл на 10
            // снова пытаемся умножить
        } else if (inf && scale == 0) {
            init_decimal(&decimalResult);
            if (sign) {
                decimalResult.value_type = s21_NEGATIVE_INFINITY;
                //printf("-inf\n");
            } else {
                decimalResult.value_type = s21_INFINITY;   
                //printf("inf\n");
            }
        }
    }
    return decimalResult;
}
// вычитание через доп код
int subtraction(s21_decimal decimalFirst, s21_decimal decimalSecond, s21_decimal *decimalResult) {
    
    //             printf("\n");
    // for (int i = 127; i >= 0; i--)
    // printf("%d", check_bit(i, decimalSecond));
    // printf("\n");  
    
    additional_code(&decimalSecond);

    //     printf("\n");
    // for (int i = 127; i >= 0; i--)
    // printf("%d", check_bit(i, decimalSecond));
    // printf("\n");  

    //     printf("\n");
    // for (int i = 127; i >= 0; i--)
    // printf("%d", check_bit(i, decimalFirst));
    // printf("\n");  

    simple_add(decimalFirst, decimalSecond, decimalResult);

    //         printf("\n");
    // for (int i = 127; i >= 0; i--)
    // printf("%d", check_bit(i, *decimalResult));
    // printf("\n");  
    decimalResult->value_type = s21_NORMAL_VALUE;
    return 1;
}
// оператор - 
s21_decimal s21_sub(s21_decimal decimalFirst, s21_decimal decimalSecond) {
    s21_decimal decimalResult;
    init_decimal(&decimalResult);
    decimalResult.value_type = s21_NORMAL_VALUE;
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
// вычитание с условиями
int substraction_part(s21_decimal decimalFirst, s21_decimal decimalSecond, s21_decimal *decimalResult) {
    delete_bit(127, &decimalFirst);
    int scale = convert_equal_scale(&decimalFirst, &decimalSecond);
    if (!s21_is_less(decimalFirst, decimalSecond)) {
        //printf("q\n");
        subtraction(decimalSecond, decimalFirst, decimalResult);
    } else if (!s21_is_not_equal(decimalFirst, decimalSecond)) {
        //printf("q1\n");
        subtraction(decimalFirst, decimalSecond, decimalResult);
        set_bit(127, decimalResult);
    } else {
        init_decimal(decimalResult);
    }
    set_ten_power(scale, decimalResult);
    return 0;
}
// сложение 2 decimal
s21_decimal s21_add(s21_decimal decimalFirst, s21_decimal decimalSecond) {
    s21_decimal decimalResult, decimalFirstBuffer, decimalSecondBuffer;
    init_decimal(&decimalResult);
    decimalResult.value_type = s21_NORMAL_VALUE;
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
                // printf("1\n");
                rewrite_decimal(decimalFirstBuffer, &decimalResult);
                decimalResult.value_type = s21_NORMAL_VALUE;
            } else if (decimalSecond.value_type == s21_INFINITY) {
                // printf("2\n");
                rewrite_decimal(decimalSecondBuffer, &decimalResult);
                decimalResult.value_type = s21_NORMAL_VALUE;
            } else {
                // printf("3\n");
                // printf("scale:%d\n", scale);
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
                // printf("4\n");
                substraction_part(decimalFirst, decimalSecond, &decimalResult);
            } else {
                substraction_part(decimalSecond, decimalFirst, &decimalResult);
            }
            decimalResult.value_type = s21_NORMAL_VALUE;
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
    // printf("scaleFirst:%d\n", scaleFirst);
    // printf("scaleSecond:%d\n", scaleSecond);
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
    printf("src:%f\n", src);
    int codeError = 0, tenPower = 0;
    value val;
    int binaryPower;
    double number = (double) src;
    // printf("number1:%f\n", number);
    printf("number:%f\n", number);
    check_value_number_float(number, dst);
    init_decimal(dst);
    val.floatValue = number;
    binaryPower = get_binary_power(val);
    if (dst->value_type == s21_NORMAL_VALUE && dst) {
        printf("number:%f\n", number);
                                printf("number1:%f\n", number);
        if (number != 0.0) {
            for (; !(int)(number / 1E6); number *= 10)
                tenPower += 1;
            number = (float) number;
                        //printf("number:%f\n", number);
            while (fmod(number, 10.0) == 0 && tenPower > 0) {
                number = number / 10;
                tenPower -= 1;
            }
             printf("number:%f\n", number);
            printf("tenPower:%d\n", tenPower);
            if (tenPower <= 28 && (binaryPower > -95 && binaryPower <=95)) {
                //printf("number:%f\n", number);
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
// номер первой значащей цифры в decimal
int first_number_position(s21_decimal decimal) {
    int i;
    for (i = 95; i >= 0; i--) {
        if (check_bit(i, decimal)) {
            break;
        }
    }
    return i;
}
// сдвиг децимал основной части step > 0 - влево, step < 0 - вправо 
int shift(s21_decimal *decimal, int step) {
    if (step > 0) {
        for (int i = 0; i < step; i++) {
            int zero = check_bit(31, *decimal);
            int one = check_bit(63, *decimal);
            decimal->bits[0] <<= 1;
            decimal->bits[1] <<= 1;
            decimal->bits[2] <<= 1;
            if (zero) 
                set_bit(32, decimal);
            if (one)
                set_bit(64, decimal);
        }
    } else {
        for (int i = 0; i < (-1) * step; i++) {
            int zero = check_bit(32, *decimal);
            int one = check_bit(64, *decimal);
            decimal->bits[0] >>= 1;
            decimal->bits[1] >>= 1;
            decimal->bits[2] >>= 1;
            if (zero) 
                set_bit(31, decimal);
            if (one)
                set_bit(63, decimal);
        }
    }
    return 1;
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
// проверка на граничные условия перед mod
int check_before_mod(s21_decimal first, s21_decimal second, s21_decimal *result) {
    int done = 1;
    s21_decimal zero;
    s21_from_int_to_decimal(0, &zero);
    if (first.value_type != s21_NORMAL_VALUE || second.value_type == s21_NAN ||
        (second.value_type == s21_NORMAL_VALUE && !s21_is_equal(zero, second))) {
        result->value_type = s21_NAN;
        done = 0;
    } else if ((second.value_type == s21_INFINITY || second.value_type == s21_NEGATIVE_INFINITY) &&
                first.value_type == s21_NORMAL_VALUE) {
        result->value_type = s21_NORMAL_VALUE;
        rewrite_decimal(first, result);
        done = 0;
    }
    return done;
}
// проверка на граничные условия перед делением
int check_before_div(s21_decimal first, s21_decimal second, s21_decimal *result) {
    int done = 1;
    s21_decimal zero;
    s21_from_int_to_decimal(0, &zero);
    if (first.value_type == s21_NAN || second.value_type == s21_NAN) {
        result->value_type = s21_NAN;
        done = 0;
    } else if (first.value_type == s21_NORMAL_VALUE && second.value_type == s21_NORMAL_VALUE &&
               !s21_is_not_equal(zero, first) && !s21_is_equal(zero, second)) {
        if (check_bit(127, first))
            result->value_type = s21_NEGATIVE_INFINITY;
        else
            result->value_type = s21_INFINITY;
        done = 0;
    } else if ((first.value_type == s21_INFINITY || second.value_type == s21_NEGATIVE_INFINITY) &&
               (first.value_type == s21_NEGATIVE_INFINITY || second.value_type == s21_INFINITY)) {
        result->value_type = s21_NAN;
        done = 0;
    } else if (first.value_type == s21_NORMAL_VALUE && second.value_type == s21_NORMAL_VALUE &&
               !s21_is_equal(zero, first) && !s21_is_equal(zero, second)) {
        result->value_type = s21_NAN;
        done = 0;
    } else if (first.value_type == s21_NORMAL_VALUE &&
              (second.value_type == s21_INFINITY || second.value_type == s21_NEGATIVE_INFINITY)) {
        init_decimal(result);
        result->value_type = s21_NORMAL_VALUE;
        done = 0;
    } else if ((first.value_type == s21_INFINITY || first.value_type == s21_NEGATIVE_INFINITY) &&
                second.value_type == s21_NORMAL_VALUE) {
        if (!check_bit(127, second)) {
            result->value_type = first.value_type;
        } else {
            if (first.value_type == s21_INFINITY)
                result->value_type = s21_NEGATIVE_INFINITY;
            else
                result->value_type = s21_INFINITY;
        }
        done = 0;
    }
    return done;
}
// проверка на граничные условия перед умножением
int check_before_mul(s21_decimal first, s21_decimal second, s21_decimal *result) {
    int done = 1;
    s21_decimal zero;
    s21_from_int_to_decimal(0, &zero);
    if (first.value_type == s21_NAN || second.value_type == s21_NAN) {
        result->value_type = s21_NAN;
        done = 0;
    } else if (first.value_type != s21_NORMAL_VALUE || second.value_type != s21_NORMAL_VALUE) {
        if (first.value_type == s21_NORMAL_VALUE && !s21_is_equal(zero, first) &&
           (second.value_type == s21_INFINITY ||
            second.value_type == s21_NEGATIVE_INFINITY)) {
            result->value_type = s21_NAN;
        } else if (second.value_type == s21_NORMAL_VALUE && !s21_is_equal(zero, second) &&
                  (first.value_type == s21_INFINITY ||
                   first.value_type == s21_NEGATIVE_INFINITY)) {
            result->value_type = s21_NAN;
        } else if (first.value_type == second.value_type) {
            result->value_type = s21_INFINITY;
        } else if (first.value_type != second.value_type) {
            result->value_type = s21_NEGATIVE_INFINITY;
        }
        done = 0;            
    }
    return done;
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
    // printf("result:%d\n", result);
    if (result == -1) {
        if (signFirst > signSecond) {
            result = 0;
        } else if (signSecond > signFirst) {
            result = 1;
        } else {
            //printf("tut\n");
            convert_equal_scale(&decimalFirst, &decimalSecond);

    //             printf("second\n");
    // for (int i = 127; i >= 0; i--)
    // printf("%d", check_bit(i, decimalSecond));
    // printf("\n");  

    // printf("buffer\n");
    // for (int i = 127; i >= 0; i--)
    // printf("%d", check_bit(i, decimalFirst));
    // printf("\n");  

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
    if (s21_is_less_or_equal(decimalFirst, decimalSecond)) 
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
// функция negate 
s21_decimal s21_negate(s21_decimal decimal) {
    s21_decimal decimalResult;
    int sign = check_bit(127, decimal);
    init_decimal(&decimalResult);
    decimalResult.value_type = s21_NORMAL_VALUE;
    if (decimal.value_type == s21_NAN) {
        decimalResult.value_type = s21_NAN;
    } else if (decimal.value_type != s21_NORMAL_VALUE) {
        if (decimal.value_type == s21_INFINITY)
            decimalResult.value_type = s21_NEGATIVE_INFINITY;
        else 
            decimalResult.value_type = s21_INFINITY;
    } else {
        decimalResult = decimal;
        delete_bit(127, &decimalResult);
        if (!sign)
            set_bit(127, &decimalResult);
    }
    return decimalResult;
}
// функция truncate
s21_decimal s21_truncate(s21_decimal decimal) {
    s21_decimal decimalResult, decimalOne;
    init_decimal(&decimalResult);
    init_decimal(&decimalOne);
    decimalResult.value_type = s21_NORMAL_VALUE;
    decimalOne.value_type = s21_NORMAL_VALUE;
    if (decimal.value_type != s21_NORMAL_VALUE) {
        decimalResult.value_type = decimal.value_type;
    } else {
        s21_from_float_to_decimal(1.0, &decimalOne);
        convert_equal_scale(&decimal, &decimalOne);
      get_ten_power(decimal);
        divide_int(decimal, decimalOne, &decimalResult);
        if (check_bit(127, decimal))
            set_bit(127, &decimalResult);
    }
    return decimalResult;
}
// функция floor
s21_decimal s21_floor(s21_decimal decimal) {
    s21_decimal decimalResult, decimalOne;
    init_decimal(&decimalResult);
    init_decimal(&decimalOne);
    decimalResult.value_type = s21_NORMAL_VALUE;
    decimalOne.value_type = s21_NORMAL_VALUE;
    if (decimal.value_type != s21_NORMAL_VALUE) {
        decimalResult.value_type = decimal.value_type;
    } else {
        s21_from_int_to_decimal(1, &decimalOne);
        decimalResult = s21_truncate(decimal);
        if (check_bit(127, decimalResult) && !s21_is_not_equal(decimalResult, decimal))
                decimalResult = s21_sub(decimalResult, decimalOne);
    }
    return decimalResult;
}
// функция round
s21_decimal s21_round(s21_decimal decimal) {
    s21_decimal decimalResult, decimalHalf, decimalBuffer, decimalOne;
    init_decimal(&decimalResult);
    init_decimal(&decimalHalf);
    init_decimal(&decimalBuffer);
    init_decimal(&decimalOne);
    decimalResult.value_type = s21_NORMAL_VALUE;
    decimalOne.value_type = s21_NORMAL_VALUE;
    decimalHalf.value_type = s21_NORMAL_VALUE;
    decimalBuffer.value_type = s21_NORMAL_VALUE;
    
    if (decimal.value_type != s21_NORMAL_VALUE) {
        decimalResult.value_type = decimal.value_type;
    } else {
        s21_from_float_to_decimal(0.5, &decimalHalf);
        s21_from_int_to_decimal(1, &decimalOne);
        decimalResult = s21_truncate(decimal);
        if (check_bit(127, decimalResult)) {
            decimalBuffer = s21_sub(decimalResult, decimalHalf);
            if (!s21_is_less_or_equal(decimal, decimalBuffer))
                decimalResult = s21_sub(decimalResult, decimalOne);
        } else {
            decimalBuffer = s21_add(decimalResult, decimalHalf);
            if (!s21_is_greater_or_equal(decimal, decimalBuffer))
                decimalResult = s21_add(decimalResult, decimalOne);
        }
    }
    return decimalResult;
}
