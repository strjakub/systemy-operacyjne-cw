#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    char x[50];
    char point[50];
    double result = strtod(argv[2], NULL) * 4.0 / ((strtod(argv[1], NULL)) * (strtod(argv[1], NULL)) + 1);
    snprintf(point, 50, "%f", result);

    strcpy(x, "echo ");
    strcat(x, point);
    strcat(x, " >> w");
    strcat(x, argv[3]);
    strcat(x, ".txt");

    system(x);

    return 0;
}
