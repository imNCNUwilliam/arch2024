#include <stdio.h>
typedef unsigned int uint32_t;

int main(void) {
    float sum = 0.0f, bias;
    union {
        float f;
        uint32_t i;
    } u1, u2, u3;
    int m1, m2, m3;
    unsigned char e1, e2;
    int preorder = 0, order;
    int tmp = 0;

    for (int i = 0; i < 10000; i++) {
        u1.f = sum;
        m1 = u1.i & 0x007fffff;
        e1 = (u1.i & 0x7f800000) >> 23;

        u2.f = i + 1;
        m2 = u2.i & 0x007fffff;
        e2 = (u2.i & 0x7f800000) >> 23;
        m3 = m2 >> (e1 - e2);
        printf("e1 / e2 / e1 - e2: %d / %d / %d\n", e1, e2, e1 - e2);
        printf("m1 / m2 / m3 / m1 + m3 / bias: %d / %d / %d / %d / %d\n", m1, m2, m3, m1 + m3, m2 - m3 << (e1 - e2));
        if (m3 << (e1 - e2) != m2) {
//            printf("Bias\n");
            order = e1 - e2;
            if (preorder != order) {
                u3.f = 0.0f;
                u3.i = tmp << preorder;
                u3.i |= preorder << 23;
                bias += u3.f;
                printf("Bias %f\n", u3.f);
                preorder = order;
            }
            tmp += m2 - m3 << (e1 - e2);
/*
            u3.f = 0.0f;
            u3.i = (m2 - m3 << (e1 - e2)) << (e1 - e2);
            u3.i |= (e1 - e2) << 23;
            bias += u3.f;
 */
        }

        sum += i + 1;
    }
    printf("sum / bias: %f / %f\n", sum, bias);
    return 0;
}

