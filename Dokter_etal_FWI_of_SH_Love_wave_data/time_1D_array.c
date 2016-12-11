#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int main(void){
     clock_t start, end;
     double cpu_time_used;
     int i, j, k, h, h1;
     int NSHOTS, NT, NX, NZ, N;
     float * store_sxy, * store_syz, * store_vy;

     NSHOTS=10; NT = 2000; NX = 512; NZ = 512;
     N = NT * NX * NZ;

     /* allocate memory */
     store_sxy = malloc(N * sizeof(float));
     store_syz = malloc(N * sizeof(float));
     store_vy = malloc(N * sizeof(float));
	
     start = clock();
     
     /* Do some intensive memory accessing stuff */
     for (h = 1; h <= NSHOTS; h++){

	 printf("Shot no. %d \n",h);
	 h1 = 0;
         for (k = 1; k <= NT; k++){
	     for (j = 1; j <= NZ; j++){
                for (i = 1; i <= NX; i++){

		    store_sxy[h1] = (float) M_PI;
		    store_syz[h1] = (float) M_PI;
		    store_vy[h1] = (float) M_PI;
		    h1++;   

                }
	     }
         }
     }	

     end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
     printf("CPU time used (per clock(): %.2f s\n", cpu_time_used);
}
