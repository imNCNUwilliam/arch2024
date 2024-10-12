#include <stdio.h>

typedef unsigned int uint32_t;

void *fp32_convert(uint32_t i) {
    uint32_t tmp;
    int step;

    printf("\n%u ", i >> 31);
    tmp = i >> 23;
    for (step = 7; step >= 0; step--)
        printf("%u", (tmp & (1 << step)) >> step);

    printf(" ");

    tmp = i & 0x7fffff;
    for (step = 22; step >= 0; step--)
        printf("%u", (tmp & (1 << step)) >> step);

    printf("\n%x ==> %u %u %u\n", i, i >> 31, (i >> 23), i & 0x7fffff);
}

int main(void) {
    float f = 1;
    union {
        float f;
        uint32_t i;
    } u = {.f = f};

    printf("%ld\n", sizeof(float));
    while (scanf("%f", &f)) {
        u.f = f;
        fp32_convert(u.i);
    }

    return 0;
}

