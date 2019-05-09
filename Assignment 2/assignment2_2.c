#include <stdio.h>
#include <stdlib.h>
#include <math.h>



double runge(double x) {
    return 1/(1 + (x*x));
}

double * calcSupports(double limit, int n, double result[][2]) {
    for(int j=0; j < n+1; j++) {
        result[j][0] = -limit + (double) j*(limit*2)/(double) n;
        result[j][1] = runge(result[j][0]);
    }
}

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

void main() {
    int n = 9;
    double sup[n+1][2];
    calcSupports(4, n, sup);
    FILE * fp1;
    fp1 = fopen("a3.dat", "w+");
    for (double i=-4; i<=4.1;i=i+0.1) {
        fprintf(fp1, "%f %f\n", i, lagrange(i, sup, n));
    }
    fclose(fp1);

    double x_test = 1.5;
    FILE * fp2;
    fp2 = fopen("a4.dat", "w+");
    for(int l=2; l<=100; l++) {
        double support[l+1][2];
        calcSupports(4, l, support);
        double in = lagrange(x_test, support, l) - runge(x_test);
        if(in < 0) {
            in = in*(-1);
        }
        fprintf(fp2, "%f\n", in);
    }
    fclose(fp2);

    for(x_test=0.1; x_test < 3; x_test+=0.1) {


        double sum = 0;
        for(int l=2; l<=1000; l++) {
        double support[l+1][2];
        calcSupports(4, l, support);
        double in = lagrange(x_test, support, l) - runge(x_test);
        if(in < 0) {
            in = in*(-1);
        }
        sum += in;
        }
        if(sum < 1000) {
        char str[50]="";
        snprintf(str, 50, "%f", x_test);
        printf(str);

        FILE * fp3;
        fp3 = fopen(str, "w+");
        for(int l=2; l<=500; l++) {
        double support[l+1][2];
        calcSupports(4, l, support);
        double in = lagrange(x_test, support, l) - runge(x_test);
        if(in < 0) {
            in = in*(-1);
        }
        fprintf(fp3, "%f\n", in);
        sum += in;
        }
        fclose(fp3);
    }
    }


}