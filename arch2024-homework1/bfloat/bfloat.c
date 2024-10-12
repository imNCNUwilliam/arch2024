#include <stdio.h>

typedef unsigned int uint32_t;
typedef struct bfloat16 {
    unsigned short bits;
} bf16_t;

static inline float bf16_to_fp32(bf16_t h)
{
    union {
        float f;
        uint32_t i;
    } u = {.i = (uint32_t)h.bits << 16};
    return u.f;
}

static inline bf16_t fp32_to_bf16(float s)
{
    bf16_t h;
    union {
        float f;
        uint32_t i;
    } u = {.f = s};
    if ((u.i & 0x7fffffff) > 0x7f800000) { /* NaN */
        h.bits = (u.i >> 16) | 64;         /* force to quiet */
        return h;
    }
    h.bits = (u.i + (0x7fff + ((u.i >> 0x10) & 1))) >> 0x10;
    return h;
}

int main(void) {
    float f[3] = {-0.5, -0.25, -0.125};
    bf16_t bf[3];
    int j;

    printf("Conversion Test ... \n");
    printf("float to bfloat16 ... \n");
    for (j = 0; j < 3; j++) {
        union {
            float f;
            uint32_t i;
        } u = {.f = f[j]};
        bf[j] = fp32_to_bf16(f[j]);
        printf("%x %x\n", u.i, bf[j].bits);
    }
    printf("bfloat16 to float ... \n");
    for (j = 0; j < 3; j++) {
        union {
            float f;
            uint32_t i;
        } u = {.f = bf16_to_fp32(bf[j])};
        printf("%x %x\n", bf[j].bits, u.i);
    }

    return 0;
}

