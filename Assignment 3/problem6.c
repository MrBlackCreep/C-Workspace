#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//returns value of function in which contains zero point that is to be determined
double calcZero(double yd, double vd, double t0, double v0, double theta) {
    return v0*sin(theta)*vd*t0/(vd-v0*cos(theta)) + 0.5*9.81*pow(vd*t0/(vd-v0*cos(theta)),2) + yd;
}

//Newton-Rhapson formula for calculating a better guess without a derivative
double calcNewX(double x, double x_old, double fx, double fx_old) {
    return x - fx*(x- x_old)/(fx-fx_old);
}

int main() {

    double yd = 8;
    double vd = 40/3.6;
    double t0 = 2;
    double v0 = 100/3.6;
    double x = 0.1;
    double x_old = 1.571;

    //part b of the problem
    printf("%.21f // %.21f \n", x, calcZero(yd,vd,t0,v0,x));
    for(int j=0; j<100;j++) {
        double temp = x;
        x = calcNewX(x,x_old,calcZero(yd,vd,t0,v0,x),calcZero(yd,vd,t0,v0,x_old));
        x_old = temp;
        printf("%.21f // %.21f \n", x*180/3.14, calcZero(yd,vd,t0,v0,x));
        if(sqrt(pow(calcZero(yd,vd,t0,v0,x),2))<1e-12) {
            printf("Needed angle: %f degrees", x*180/3.14);
            break;
        }
    }

    //part c of the problem
    FILE * fp1;
    fp1 = fopen("6c.dat", "w+");
    //loop over different points of time that Bob can start throwing
    for (double i=0; i<=5;i=i+0.01) {
        x = 0.1;
        x_old = 1.571;
        for(int j=0; j<100;j++) {
            double temp = x;
            x = calcNewX(x,x_old,calcZero(yd,vd,i,v0,x),calcZero(yd,vd,i,v0,x_old));
            x_old = temp;
            if(sqrt(pow(calcZero(yd,vd,i,v0,x),2))<1e-12 && 0<(x*180/3.14) && (x*180/3.14)<90) {
                fprintf(fp1, "%f %f \n", i, x*180/3.14);
                break;
            } else if (j == 99) {
                fprintf(fp1, "%f %f \n", i, 0);
            }
        }
    }
    fclose(fp1);
}