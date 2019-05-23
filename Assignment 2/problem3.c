#include <stdio.h>
#include <math.h>


int main() {
    double x = pow(10,20);
    
    printf("Normal computation %.21f \n", pow(x+(double)1, 0.75)-pow(x,0.75));
    printf("Approximated result: %.21f \n", ((double) 1/pow(x, 0.25))*((double)3/(double)4));
	return 0;
}