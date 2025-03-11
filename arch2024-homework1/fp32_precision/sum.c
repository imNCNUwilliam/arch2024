#include <stdio.h>
typedef unsigned int uint32_t;

int eval_bias(int num) {
    float fsum = 0.0f;
    union {
        float f;
        uint32_t i;
    } u;
    uint32_t isum = 0;
    uint32_t bias = 0;
    uint32_t exponent;
    uint32_t mantissa;

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
        sum += i;
    return sum;
}

int main() {
    int num = 10000;

    printf("Sum: %f | Kahan Sum: %f | Bias Evaluation: %d\n", \
            sum(num), \
            kahan_sum(num), \
            eval_bias(num));
    return 0;
}

