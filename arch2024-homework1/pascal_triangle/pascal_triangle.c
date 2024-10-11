#include <stdio.h>
#include <stdlib.h>

unsigned char my_popcount(unsigned int val) {
    unsigned int count = 0;

    while (val) {
        if (val & 0x80000000)
            count++;
        val <<= 1;
    }

    return count;
}

void pascal_triangle(int n) {
    unsigned int outcome = 0;
    unsigned int max = (1 << n) - 1;
    unsigned int *counter;
    int i;

    if (n == 0) {
        printf("1\n");
        return;
    }
    if (n > 31) {
        printf("Support up to 31 only!\n");
        exit(-1);
    }
    printf("iterate from %x(%d) to %x(%d)\n", outcome, outcome, max, max);

    counter = (unsigned int *)malloc(sizeof(unsigned int) * (n + 1));
    if (counter == NULL) {
        fprintf(stderr, "No memory!\n");
        exit(-2);
    }
    for (i = 0; i <= n; i++)
        counter[i] = 0;

    while (outcome <= max) {
        counter[my_popcount(outcome)]++;
        outcome++;
//        printf("DEBUG: %d %d %d\n", \
			outcome - 1, \
			my_popcount(outcome - 1), \
			counter[my_popcount(outcome - 1)]);
    }
    for (i = 0; i <= n; i++)
        printf("%d ", counter[i]);

    free(counter);
    printf("\n");
}

int main(void) {
    int i;

    for (i = 0; i < 15; i++)
        pascal_triangle(i);

    return 0;
}

