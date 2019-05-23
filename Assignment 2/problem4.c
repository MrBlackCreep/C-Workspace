#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//return value of runge function at x
double runge(double x) {
    return 1/(1 + (x*x));
}

//calculate n supports for the runge function and save to result
double * calcSupports(double limit, int n, double result[][2]) {
    for(int j=0; j < n+1; j++) {
        result[j][0] = -limit + (double) j*(limit*2)/(double) n;
        result[j][1] = runge(result[j][0]);
    }
}

//obtain lagrange interpolted value at x with given supports and n
double lagrange(double x, double supports[][2], int n) {
    double result = 0;
    for(int j=0; j<n+1; j++) {
        double p2 = -1;
        for(int k=0; k<n+1; k++) {
            if(j != k) {
                if(p2 == -1) {
                    p2 = ((x-supports[k][0])/(supports[j][0]-supports[k][0]));
                } else {
                    p2 = p2*((x-supports[k][0])/(supports[j][0]-supports[k][0]));
                }
            }
        }
        result += p2*supports[j][1];
    }
    return result;
}

//calculation for 4a (iv) and c
void errorSequence(double x, double x_c, char name[]) {
    FILE * fp2;
    fp2 = fopen(name, "w+");
    for(int l=2; l<=100; l++) {
        double support[l+1][2];
        calcSupports(x_c, l, support);
        double in = lagrange(x, support, l) - runge(x);
        if(in < 0) {
            in = in*(-1);
        }
        fprintf(fp2, "%f\n", in);
    }
    fclose(fp2);
}

void main() {

    //calculation for Problem 4b
    int n = 9;
    double sup[n+1][2];
    calcSupports(4, n, sup);
    FILE * fp1;
    fp1 = fopen("n9.dat", "w+");
    for (double i=-4; i<=4.1;i=i+0.1) {
        fprintf(fp1, "%f %f\n", i, lagrange(i, sup, n));
    }
    fclose(fp1);

    //calculation for Problem 4c
    errorSequence(0.75,4,"err1.dat");
    errorSequence(3,4,"err2.dat");
    errorSequence(0.75,8,"err3.dat");
    errorSequence(3,8,"err4.dat");
    
}