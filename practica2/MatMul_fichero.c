/****************************************************************/
/* Nombre:                                                      */
/* Práctica:                                                    */
/* Fecha: 							*/
/*								*/
/* Usage: ./MatMul [<num threads>] [block_size] [<input file>]  */
/*                                                              */
/****************************************************************/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include "omp.h"

typedef float *matrix;

/************************************************************/
void Lee_Datos ();
void Multiplicar_Matrices ();
void Multiplicar_Matrices_sec ();
void Escribir_Resultados ();
/************************************************************/

void main (int argc, char **argv)
{
	int dimM, dimN, dimK;
	char source[32]="matrix.ejem";
	matrix A, B, C, D;
	int ntask;
        int nthreads = 1, block_size = 1;
	FILE *fd;

/* Lectura de parámetros de entrada */
/* Usage: ./MatMul [<num threads>] [block_size] [<input file>]*/

   	if (argc > 1) nthreads = atoi (argv[1]);
   	if (argc > 2) block_size = atoi (argv[2]);
	if (argc > 3) strcpy (source, argv[3]);

	Lee_Datos (&dimM, &dimN, &dimK, &A, &B, source);

	//--------parte paralela----------
	C = (matrix) malloc (dimM * dimK * sizeof (float));
	Multiplicar_Matrices (A, B, C, dimM, dimN, dimK);
	Escribir_Resultados (C, dimM, dimK,1);
	
	//--------parte secuencial--------
	D = (matrix) malloc (dimM * dimK * sizeof (float));
	Multiplicar_Matrices_sec (A, B, D, dimM, dimN, dimK);
	Escribir_Resultados (D, dimM, dimK,0);

	exit (0);
}

void Lee_Datos (int *dimM, int *dimN, int *dimK, matrix *A, matrix *B, char *source)
{
	FILE *file;
	int i,j,m,n,k;
	float a;

	if (( file = fopen (source, "r")) == NULL)
	{
		printf ("Error en Solver: No puedo abrir el fichero %s\n", source);
		exit (1);
	}

	fscanf (file, "%d %d", &m, &n);
	*dimM = m;
	*dimN = n;

	(*A) = (matrix) malloc (m * n * sizeof (float));

	for (i=0; i < m; i++)
		for (j=0; j < n; j++)
		{
			fscanf (file,"%f", &a);
			(*A)[i*n+j] = a;
		}

	
	fscanf (file, "%d %d", &n, &k);
	*dimK = k;
	(*B) = (matrix) malloc (n * k * sizeof (float));
	for (i=0; i < n; i++)
		for (j=0; j < k; j++)
		{
			fscanf (file,"%f,",&a);
			(*B)[i*k+j] = a;
		}
	fclose (file);
}

void Multiplicar_Matrices (matrix A, matrix B, matrix C, int dimM, int dimN, int dimK)
{
	omp_set_num_threads(omp_get_max_threads());
	int i, j, k;
	#pragma omp parallel shared(C, A, B) private (i,j,k)
	{
	#pragma omp for 
	for (i=0; i < dimM; i++)
		for (j=0; j < dimK; j++)
			C[i*dimM+j] = 0.0;
	#pragma omp for
	for (i=0; i < dimM; i++)
		for (j=0; j < dimN; j++)
			for (k=i; k < dimK; k++)
				C[i*dimM+j] += A[i*dimN+k] * B[j+k*dimK];
	}
}

void Multiplicar_Matrices_sec (matrix A, matrix B, matrix C, int dimM, int dimN, int dimK)
{
	
	int i, j, k;
	
	
	for (i=0; i < dimM; i++)
		for (j=0; j < dimK; j++)
			C[i*dimM+j] = 0.0;
	
	for (i=0; i < dimM; i++)
		for (j=0; j < dimN; j++)
			for (k=i; k < dimK; k++)
				C[i*dimM+j] += A[i*dimN+k] * B[j+k*dimK];
	
}

void Escribir_Resultados (matrix C, int dimM, int dimK, int tipoEjecucion)
{
	int i, j;
	FILE *fd;
	if(tipoEjecucion==1){
		if ((fd = fopen("matrix.out", "w")) == NULL)
		{
			printf ("Error: No puedo abrir el fichero: matrix.out\n");
			exit (1);
		}
	} else{
		if ((fd = fopen("matrixSEC.out", "w")) == NULL)
		{
			printf ("Error: No puedo abrir el fichero: matrix.out\n");
			exit (1);
		}
	}
	for (i=0; i < dimM; i++)
	{
		for (j=0; j < dimK; j++)
			fprintf (fd, "%.1f ", C[i*dimK+j]);
		fprintf (fd,"\n");
	}
	fclose (fd);
}
