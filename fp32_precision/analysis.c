#include <stdio.h>
#include <limits.h>

int main(void) {
    int inum;
    float fnum = 0.0f;
    unsigned int inconsistence = 0;
    // observing bits for round nearest half implementation
    char pos;
    unsigned char guard_bit, round_bit;
    int sticky_bit;

    for (int i = 0; i < INT_MAX; i++) {
        inum = i + 1;
        fnum = i + 1;

        if ((int)fnum != inum) {
            printf("%f, %d, %d, %s\n", fnum, (int)fnum, inum, "NOT_MATCH");
            inconsistence++;
        }
        if (inconsistence >= 10)
            break;

        pos = __builtin_clz(inum);
        guard_bit = pos > 7 ? 0 : (inum >> (8 - pos)) & 1;
        round_bit = pos > 7 ? 0 : (inum >> (7 - pos)) & 1;
        sticky_bit = pos >= 7 ? -1 : (inum & ((1 << (7 - pos)) - 1));
        sticky_bit = sticky_bit > 0 ? 1 : sticky_bit;
        if (pos <= 7)
            printf("inum: %d | pos: %d | %d | %d | %d\n", inum, pos, guard_bit, round_bit, sticky_bit);
    }
    printf("INT_MAX: %d\n", INT_MAX);

    return 0;
}

