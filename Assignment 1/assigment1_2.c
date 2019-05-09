#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//Calculate x-coordinate of impact
double calcx1(double x0, double y0, double vx, double vy) {
    double B = 2*vy*(vx*y0 - vy*x0);
    double C = (pow(vy, 2)*pow(x0, 2)) - (pow(vx, 2)*(1-pow(y0, 2))) - (2*vx*vy*x0*y0);
    double sgn = 1;
    if(vx < 0) {
        sgn = -1;
    } else if (vx == 0) {
        sgn = 0;
    }
    double x1 = -0.5*(B - (sgn)*sqrt(pow(B, 2)-4*C));
    return x1;
}

//Calculate y-coordinate of impact
double calcy1(double x0, double y0, double vx0, double vy0, double x1) {
    double sgn = 1;
    if((y0 + (vy0/vx0)*(x1-x0)) < 0) {
        sgn = -1;
    }
    return sgn*sqrt(1-pow(x1, 2));
}

//Calculate x-velocity after impact
double calcvx1(double x1, double y1, double vx0, double vy0) {
    return (pow(y1, 2)-pow(x1, 2))*vx0 - 2*x1*y1*vy0;
}

//Calculate y-velocity after impact
double calcvy1(double x1, double y1, double vx0, double vy0) {
    return (pow(x1, 2)-pow(y1, 2))*vy0 - 2*x1*y1*vx0;
}

//Calculate distance between two points on the plane
double dist(double x0, double y0, double x1, double y1) {
    return sqrt(pow((x1 - x0) ,2)+pow((y1 - y0) ,2));
}

double simulate(double y_start, int max_j) {
    //FILE * fp;
    //fp = fopen("points.dat", "w+");

    //starting conditions
    double x = 0;
    double y = y_start;
    double vx = 1;
    double vy = sqrt(1-pow(vx, 2));
    //fprintf(fp, "%f %f\n", x,y);

    //calculate impacts
    double limit[3];
    double C_dist;
    int j;
    for(j = 1; j < max_j; j++) {
        double x_old = x;
        double y_old = y;
        double vx_old = vx;
        x = calcx1(x, y, vx, vy);
        y = calcy1(x_old, y, vx, vy, x);
        vx = calcvx1(x, y, vx, vy);
        vy = calcvy1(x, y, vx_old, vy);
        C_dist = C_dist + dist(x, y, x_old, y_old);
        if(j == 2) {
            limit[2] = dist(x, y, x_old, y_old);
        } else if(j == 1) {
            limit[0] = x;
            limit[1] = y;
            C_dist = dist(x, y, x_old, y_old);
        }
        //printf("Impact at: %f // %f with velocity %f // %f \n", x, y, vx, vy);
        //fprintf(fp, "%f %f\n", x,y);
        if(dist(x, y, limit[0], limit[1]) < limit[2] && j != 1) {
            //printf("Limit reached after %d reflections. Total distance: %f\n", j, C_dist);
            //fclose(fp);
            return C_dist;
        }
    }
}

int main() {

    //file for starting point/distance plot
    FILE * fp2;
    fp2 = fopen("points2.dat", "w+");

    double i;
    for (i=0.001; i<1;i=i+0.001) {
        fprintf(fp2, "%f %f\n", i, simulate(i, 500));
    }
    fclose(fp2);
    printf("Curve length for y_0 = 0.9: %f\n", simulate(0.9,500));
    printf("Curve length for y_0 = 0.999: %f", simulate(0.999,500));
    return 0;
}
