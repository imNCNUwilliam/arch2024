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
    float f[3] = {1, 1.25, 4};
    int i;

    for (i = 0; i < 3; i++) {
        union {
            float f;
            uint32_t i;
        } u = {.f = f[i]};
        printf("%x %x\n", u.i, fp32_to_bf16(f[i]).bits);
    }

    return 0;
}

