#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define NR_END 1

float ***f3tensor(int nrl, int nrh, int ncl, int nch,int ndl, int ndh){
	
  /* allocate a float 3tensor with subscript range m[nrl..nrh][ncl..nch][ndl..ndh]
		   and intializing the matrix, e.g. m[nrl..nrh][ncl..nch][ndl..ndh]=0.0 */
  int i,j,d, nrow=nrh-nrl+1,ncol=nch-ncl+1,ndep=ndh-ndl+1;
  float ***t;

  /* allocate pointers to pointers to rows */
  t=(float ***) malloc((size_t) ((nrow+NR_END)*sizeof(float**)));
  if (!t) err("allocation failure 1 in function f3tensor() ");
  t += NR_END;
  t -= nrl;

  /* allocate pointers to rows and set pointers to them */
  t[nrl]=(float **) malloc((size_t)((nrow*ncol+NR_END)*sizeof(float*)));
  if (!t[nrl]) err("allocation failure 2 in function f3tensor() ");
  t[nrl] += NR_END;
  t[nrl] -= ncl;

  /* allocate rows and set pointers to them */
  t[nrl][ncl]=(float *) malloc((size_t)((nrow*ncol*ndep+NR_END)*sizeof(float)));
  if (!t[nrl][ncl]) err("allocation failure 3 in function f3tensor() ");
  t[nrl][ncl] += NR_END;
  t[nrl][ncl] -= ndl;

  for (j=ncl+1;j<=nch;j++) t[nrl][j]=t[nrl][j-1]+ndep;
	for (i=nrl+1;i<=nrh;i++){
		t[i]=t[i-1]+ncol;
		t[i][ncl]=t[i-1][ncl]+ncol*ndep;
		for (j=ncl+1;j<=nch;j++) t[i][j]=t[i][j-1]+ndep;
	}

  /* initializing 3tensor */
  for (i=nrl;i<=nrh;i++)
		for (j=ncl;j<=nch;j++)
			for (d=ndl;d<=ndh;d++) t[i][j][d]=0.0;

	/* return pointer to array of pointer to rows */
	return t;
}

int main(void)
{

     clock_t start, end;
     double cpu_time_used;
     int i, j, k, h, h1;
     int NSHOTS, NT, NX, NZ, N;
     float *** store_sxy, *** store_syz, *** store_vy;

     NSHOTS=10; NT = 2000; NX = 512; NZ = 512;
     N = NT * NX * NZ;

     /* allocate memory */
     store_sxy = f3tensor(1,NT,1,NZ,1,NX);
     store_syz = f3tensor(1,NT,1,NZ,1,NX);
     store_vy = f3tensor(1,NT,1,NZ,1,NX);
	
     start = clock();
     
     /* Do some intensive memory accessing stuff */
     for (h = 1; h <= NSHOTS; h++){

	 printf("Shot no. %d \n",h);

	 h1 = 0;
         for (k = 1; k <= NT; k++){
	     for (j = 1; j <= NZ; j++){
                for (i = 1; i <= NX; i++){

		    store_sxy[k][j][i] = (float) M_PI;
		    store_syz[k][j][i] = (float) M_PI;
		    store_vy[k][j][i] = (float) M_PI;
		    h1++;   

                }
	     }
         }
     }	

     end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
 
     printf("CPU time used (per clock(): %.2f s\n", cpu_time_used);

}
