//
//  finalrachchaos.c
//  
//
//  Created by Nicole O'Brien on 1/19/15.
//
//

/*
 * Chaos.c
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Complex.h>
#include <math.h>

typedef struct complex_t {
    double real, imag;
} Complex;

int getN(char N_M [256]) {
    char *N;
    char *search = " ";
    N = strtok(N_M, search);
    //turns N into an integer
    int Nint = atoi(N);
    return Nint;
}

int getM(char N_M [256]) {
    char *M;
    char *search = " ";
    M = strtok(NULL, search);
    //turns M into an integer
    int Mint = atoi(M);
    return Mint;
}

Complex add(Complex n1, Complex n2){
    Complex sum;
    sum.real = n1.real + n2.real;
    sum.imag = n1.imag + n2.imag;
    return sum;
}

Complex multiply(Complex n1, Complex n2){
    Complex product;
    product.real = (n1.real * n2.real) - (n1.imag * n2.imag);
    product.imag = (n1.real * n2.imag) + (n2.real * n1.imag);
    return product;
}

Complex calculateC(double N, double M, double a, double b) {
    Complex c;
    c.real = (((3.5*a)/N) - 2.5)*1.0;
    c.imag = ((b/M - .5) * 2.0)*1.0;
    return c;
}

Complex calculateZ(int N, Complex c) {
    if (N == 0) {
        Complex z_0;
        z_0.real = 0.0;
        z_0.imag = 0.0;
        return z_0;
    }
    else {
        Complex prev_z;
        prev_z=calculateZ(N-1,c);
        Complex z_squared = multiply(prev_z,prev_z);
        //printf("z_squared = %.1f%s%.1f%s\n", c.real, " + ", c.imag, "i" );
        Complex z_N;
        z_N = add(z_squared, c);
        return z_N;
    }
    
}

double findMagZ(Complex z) {
    double magZ = z.real*z.real + z.imag*z.imag;
    return magZ;
}

int main(void) {
    int a, b, Nint, Mint;
    
    char N_M [256];
    fgets(N_M, 256, stdin);
    // printf("N_M = %s\n", N_M);
    Nint = getN(N_M);
    double N = Nint/1.0;
    // printf("%f\n", N);
    Mint = getM(N_M);
    double M = Mint/1.0;
    // printf("%f\n", M);
    
    
    
    for (b = 0; b < M; b++) {
        for (a = 0; a < N; a++) {
            double a_dub = (double) a;
            double b_dub = (double) b;
            Complex c = calculateC(N, M, a_dub, b_dub);
            // printf("c = %.1f%s%.1f%s\n", c.real, " + ", c.imag, "i" );
            Complex Z_500 = calculateZ(500, c);
            // printf("Z_500 = %.1f%s%.1f%s\n", Z_500.real, " + ", Z_500.imag, "i" );
            double magz500 = findMagZ(Z_500);
            // printf("magz500 = %f\n", magz500);
            if (magz500 <= 4.0) {
                printf("%c", '*');
            } else {
                printf("%c", ' ');
            }
        }
        printf("\n");
    }
    return 0;                                                                                                                               
}