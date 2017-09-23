/*
 * Calculate PI
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

double circlesy(double r, double x) {
    return sqrt(r*r - x*x); // Frome r^2 = x^2 + y^2
}

// differentiation from circlesy
double circlesm(double r, double x) {
    return (1.0f/sqrt(r*r - x*x)) * (-x);
}

double indextox(double r, double part, unsigned long index) {
    return part * index * r;
}

int main(int lenargs, char** args) {
    if (lenargs != 2) {
        printf("%s [integer]\n", args[0]);
        return EXIT_FAILURE;
    }

    clock_t start_time = clock();

    unsigned long accuracy = atol(args[1]);
    printf("Using accuracy = %lu\n", accuracy);

    double part = (double) 1 / (double) accuracy;
    const double r = 0.5f * 16;
    double result0 = 0.0f; // Inner pi
    double result1 = 0.0f; // Outer pi
    for (size_t i = 1; i < accuracy; i++) {
        double x0 = indextox(r, part, i);
        double x1 = indextox(r,part, i-1);
        double y0 = circlesy(r, x0);
        double y1 = circlesy(r, x1);
        double x = x0 - x1;
        double y = y0 - y1;
        result0 += sqrt(x*x + y*y);

        float hx = (x0 + x1) / 2.0f;
        // Tangent: y = mx + t
        float m = circlesm(r, hx);
        float t = circlesy(r, hx) - m * hx;
        y0 = m * x0 + t;
        y1 = m * x1 + t;
        y = y0 - y1;
        result1 += sqrt(x*x + y*y);
    }

    result0 *= (1.0f/r) * 2.0f;
    result1 *= (1.0f/r) * 2.0f;
    double result = (result0+result1) / 2.0f;
    printf("Calculated PI = %lf\n", result);

    start_time = clock() - start_time;
    float secs = start_time / (float) CLOCKS_PER_SEC;
    printf("Needed %.3f seconds\n", secs);
    return EXIT_SUCCESS;
}
