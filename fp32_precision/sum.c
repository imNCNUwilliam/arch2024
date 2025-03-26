#include <stdio.h>
#include <stdlib.h>
typedef unsigned int uint32_t;

int round_half_even(int val) {
    int remaining;
    char pos;
    int guard_bit, round_bit, sticky_bit;

    /* -------------------
     * | pos  | 32 - pos |
     * -------------------
     * | 0..0 | 1........|
     * ------------------- */
    pos = __builtin_clz(val);

    if (pos > 7)
        return 0;

    /* Only int value greater than 2 ^ 24 may cause rounding issue, 
     * and the most significant 24 bits needs to be preserved. 
     * That is, the least significant (32 - pos - 24) bits will be 
     * the rounding errors. Perform `round nearest half` implementation. */
    guard_bit = (val >> (8 - pos)) & 1;
    round_bit = (val >> (7 - pos)) & 1;
    sticky_bit = pos == 7 ? -1 : (val & ((1 << (7 - pos)) - 1));
    sticky_bit = sticky_bit > 0 ? 1 : sticky_bit;

    remaining = val & ((1 << (8 - pos)) - 1);
    if (round_bit & sticky_bit > 0)
        remaining = remaining - (1 << (8 - pos));
    if (guard_bit & round_bit & sticky_bit <= 0)
        remaining = remaining - (1 << (8 - pos));
//    printf("Value: %x | remaining: %d | pos: %d | %d | %d | %d\n", val, remaining, pos, guard_bit, round_bit, sticky_bit);

    return remaining;
}

int myround(int val) {
    int remaining;
    char pos;

    /* -------------------
     * | pos  | 32 - pos |
     * -------------------
     * | 0..0 | 1........|
     * ------------------- */
    pos = __builtin_clz(val);

    if (pos > 7)
        return 0;

    /* Only int value greater than 2 ^ 24 may cause rounding issue, 
     * and the most significant 24 bits needs to be preserved. 
     * That is, the least significant (32 - pos - 24) bits will be 
     * the rounding errors. I use its MSB as rounding determination. */
    remaining = val & ((1 << (8 - pos)) - 1);
    remaining = remaining & (1 << (7 - pos)) ? remaining - (1 << (8 - pos)) : remaining;
//    printf("Value: %d | pos: %d | remaining: %d\n", val, pos, remaining);

    return remaining;
}

int err_evaluation(int num) {
    int sum = 0;

    for (int i = 0; i < num; i++) {
        sum += i + 1;
//        sum -= myround(sum);
        sum -= round_half_even(sum);
    }
//    printf("Sum: %d | Error: %d\n", sum, sum - ((1 + num) * num / 2));
    return sum - ((1 + num) * num / 2);
}

int err_observation(int num) {
    float fsum = 0.0f;
    union {
        float f;
        uint32_t i;
    } u;
    int isum = 0;
    int err = 0;
    int exponent;
    int mantissa;

    for (int i = 0; i < num; i++) {
        fsum += i + 1;
        isum += i + 1;

        u.f = fsum;
        exponent = (u.i >> 23) - 127;
        mantissa = exponent <= 23 ? (1 << exponent) | ((u.i & 0x007fffff) >> (23 - exponent)) \
                                  : (1 << exponent) | ((u.i & 0x007fffff) << (exponent -23));
        err = (mantissa - isum);
//        printf("fSum: %f Exponent: %d, Mantissa: %d | iSum: %d | Error: %d\n", fsum, exponent, mantissa, isum, err);
    }
//    printf("fSum: %f | iSum: %d | Error: %d\n", fsum, isum, err);
    return err;
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

    printf("Sum: %f | Kahan Sum: %f | Error Observation (GT): %d | Error Evaluation: %d\n", \
            sum(num), \
            kahan_sum(num), \
            err_observation(num), \
            err_evaluation(num));

    return 0;
}

