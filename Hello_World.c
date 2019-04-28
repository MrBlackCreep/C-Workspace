#include <stdio.h>
#include <math.h>



int main() {
    double x0 = 0.8;
    double y0 = 0.6;
    double vx = -0.28;
    double vy = -0.96;
    double C = (pow(vy, 2)*pow(x0, 2)) - (pow(vx, 2)*(1-pow(y0, 2))) - (2*vx*vy*x0*y0);
    printf("%f \n", C);
}