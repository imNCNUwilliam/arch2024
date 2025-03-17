#include <stdio.h>
#include <limits.h>

int main(void) {
    int inum;
    float fnum = 0.0f;
    unsigned int inconsistence = 0;

    for (int i = 0; i < INT_MAX; i++) {
        inum = i + 1;
        fnum = i + 1;
        if ((int)fnum != inum) {
            printf("%f, %d, %d, %s\n", fnum, (int)fnum, inum, "NOT_MATCH");
	    inconsistence++;
        }
        if (inconsistence >= 10)
            break;
    }
    printf("INT_MAX: %d\n", INT_MAX);

    return 0;
}

