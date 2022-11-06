#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include "omp.h"

#define RAND rand() % 100
typedef float *matrix;


void Escribir_Matrizes (float *M, int dim, float *S);
void Init_Mat_Sup (int dim, float *M);
void Init_Mat_Inf (int dim, float *M);


void main (int argc, char **argv)
{
    float *A, *B, *C;
    int dim=5;
    dim = atoi (argv[1]);
    
    A = (float *) malloc (dim * dim * sizeof (float));
    B = (float *) malloc (dim * dim * sizeof (float));

    Init_Mat_Sup (dim, A);
    Init_Mat_Sup (dim, B);
	Escribir_Matrizes(A,dim,B);
	
    exit(0);
}

void Escribir_Matrizes (float *M, int dim, float *S)
{
	int i, j;
    FILE *fd;
	if ((fd = fopen("MatrizEjemplo.ejem", "w")) == NULL)
		{
			printf ("Error: No puedo abrir el fichero: matrix.out\n");
			exit (1);
		}
	fprintf(fd,"%d %d\n",dim, dim);
	for (i=0; i < dim; i++)
	{
		for (j=0; j < dim; j++)
			fprintf (fd, "%.1f ", M[i*dim+j]);
		fprintf (fd,"\n");
	}
	fprintf(fd,"%d %d\n",dim, dim);
	for (i=0; i < dim; i++)
	{
		for (j=0; j < dim; j++)
			fprintf (fd, "%.1f ", S[i*dim+j]);
		fprintf (fd,"\n");
	}

   printf ("\n");
   fclose(fd);
}

void Init_Mat_Sup (int dim, float *M)
{
	int i,j,m,n,k;

	for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++) {
			if (j <= i)
				M[i*dim+j] = 0.0;
			else
//				M[i*dim+j] = j+1;
				M[i*dim+j] = rand() % 100;
		}
	}
}

void Init_Mat_Inf (int dim, float *M)
{
	int i,j,m,n,k;

	for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++) {
			if (j >= i)
				M[i*dim+j] = 0.0;
			else
//				M[i*dim+j] = j+1;
				M[i*dim+j] = rand() % 100;
		}
	}
}