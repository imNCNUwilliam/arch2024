#include <stdio.h>
typedef unsigned int uint32_t;

int main() {
    float fsum = 0.0f;
    union {
        float f;
        uint32_t i;
    } u;
    uint32_t isum = 0;
    uint32_t bias = 0;
    uint32_t exponent;
    uint32_t mantissa;

    for (int i = 0; i < 10000; i++) {
        fsum += i + 1;
        isum += i + 1;

        u.f = fsum;
        exponent = (u.i >> 23) - 127;
        mantissa = exponent <= 23 ? (1 << exponent) | ((u.i & 0x007fffff) >> (23 - exponent)) \
                                  : (1 << exponent) | ((u.i & 0x007fffff) << (exponent -23));
        bias = (mantissa - isum);
//        printf("fSum: %f Exponent: %d, Mantissa: %d | iSum: %d | bias: %d\n", fsum, exponent, mantissa, isum, bias);
    }
    printf("fSum: %f | iSum: %d | bias: %d\n", fsum, isum, bias);
    return 0;
}

