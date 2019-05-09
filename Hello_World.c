#include <stdio.h>
#include <math.h>
#include <time.h>   	// for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h> 	// for sleep()


int main() {
    long double x = pow(10L,20L);
    
    printf("%lf \n", x);
    printf("%lf \n", x);
    printf("%lf \n", pow(x,0.75));
    printf("%lf \n", pow(x+1, 0.75)-pow(x,0.75));
	return 0;
}