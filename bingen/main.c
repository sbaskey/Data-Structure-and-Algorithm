#include <stdio.h>
#include <stdlib.h>
#include<time.h>
int main()
{
    int count;
    int num, n, x;
    FILE *p, *q;
    srand(time(NULL));
    printf("enter the file size\n");
    scanf("%d", &n);
    p = fopen("input2.bin", "wb");
    q = fopen("input.txt", "w");
    printf("actual binary file contents before sorting\n");
    for (count = 0; count < n; count++) {
        x = random() % 10000;
        fwrite((char *) &x, sizeof(int), 1, p);
        fprintf(q, "%d\n", x);
        printf(" %d ", x);
    }
    fclose(p);
    fclose(q);
    return 0;
}