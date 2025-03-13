#include <stdio.h>
#include <stdlib.h>
typedef unsigned int uint32_t;

int bias_eval_2(int num) {
    int sum = 0;
    int remaining;
    int bias = 0;
    char pos;

    for (int i = 0; i < num; i++) {
        sum += i + 1;
        /* ------------------_
         * | pos  | 32 - pos | 
         * -------------------
         * | 0..0 | 1........| 
         * ------------------- */
        pos = __builtin_clz(sum);

        /* Only int value greater than 2 ^ 24 may cause rounding issue, 
         * and the most significant 23 bits needs to be preserved. 
         * That is, the least significant (32 - pos - 24) bits will be 
         * the rounding errors. I use its MSB as rounding determination. */
        remaining = pos > 7 ? 0 : sum & ((1 << (8 - pos)) - 1);
        remaining = remaining & (1 << (7 - pos)) ? remaining - (1 << (8 - pos)) : remaining; 
        bias += remaining;
//        printf("Sum: %d | pos: %d | remaining: %d\n", sum, pos, remaining);
    }
//    printf("Sum: %d | bias: %d\n", sum, bias);
    return bias;
}

int bias_eval(int num) {
    float fsum = 0.0f;
    union {
        float f;
        uint32_t i;
    } u;
    int isum = 0;
    int bias = 0;
    int exponent;
    int mantissa;

    for (int i = 0; i < num; i++) {
        fsum += i + 1;
        isum += i + 1;

        u.f = fsum;
        exponent = (u.i >> 23) - 127;
        mantissa = exponent <= 23 ? (1 << exponent) | ((u.i & 0x007fffff) >> (23 - exponent)) \
                                  : (1 << exponent) | ((u.i & 0x007fffff) << (exponent -23));
        bias = (mantissa - isum);
//        printf("fSum: %f Exponent: %d, Mantissa: %d | iSum: %d | bias: %d\n", fsum, exponent, mantissa, isum, bias);
    }
//    printf("fSum: %f | iSum: %d | bias: %d\n", fsum, isum, bias);
    return bias;
}

float kahan_sum(int num) {
    float sum = 0.0f, corr = 0.0f;    /* corrective value for rounding error */
    for (int i = 0; i < num; i++) {
        float y = (i + 1) - corr;    /* add the correction to specific item */
        float t = sum + y;    /* bits might be lost */
        corr = (t - sum) - y;    /* recover lost bits */
        sum = t;
    }
    return sum;
}

float sum(int num) {
    float sum = 0.0f;
    for (int i = 0; i < num; i++)
        sum += i + 1;
    return sum;
}

int main(int argc, char *argv[]) {
    int num = atoi(argv[1]);
//    for (int i = 1; i <= 10; i++)
//        printf("%d: clz(): %d\n", i, __builtin_clz(i));

    printf("Sum: %f | Kahan Sum: %f | Bias Evaluation: %d | Bias Evaluation 2: %d\n", \
            sum(num), \
            kahan_sum(num), \
            bias_eval(num), \
            bias_eval_2(num));
    return 0;
}

