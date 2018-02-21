#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#define SIZE 8

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

void storeVals(int m[SIZE][SIZE])
{
	static int n=0;
	int i, j;
	for (i=0; i<SIZE; i++)
		for (j=0; j<SIZE; j++)
			m[i][j] = n++;
}

void print(int m[SIZE][SIZE])
{
	int i, j = 0;
	for (i=0; i<SIZE; i++)
	{
		printf("\n\t| ");
		for (j=0; j<SIZE; j++)
			printf("%5d ", m[i][j]);
		printf("|");
	}
}


int main(int argc, char *argv[])
{
	int process_number, num_of_procs, from, to;

	MPI_Init (&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &process_number);
	MPI_Comm_size(MPI_COMM_WORLD, &num_of_procs); 

	if (SIZE%num_of_procs !=0)
	{
		if (process_number==0)
			printf("Matrix size not divisible by number of processors\n");
		MPI_Finalize();
		exit(-1);
	}

	from = process_number * SIZE/num_of_procs;
	to = (process_number+1) * SIZE/num_of_procs;


	if (process_number==0)
	{
		storeVals(A);
		storeVals(B);
	}

	MPI_Bcast (B, SIZE*SIZE, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter (A, SIZE*SIZE/num_of_procs, MPI_INT, A[from], SIZE*SIZE/num_of_procs, MPI_INT, 0, MPI_COMM_WORLD);

	printf("process_number=%d multiplyng B with A(from row %d to %d)\n", process_number, from, to-1);
	wait(NULL);
	int i,j,k;
	for (i=from; i<to; i++)
	{
		for (j=0; j<SIZE; j++)
		{
			C[i][j]=0;
			for (k=0; k<SIZE; k++)
				C[i][j] += A[i][k]*B[k][j];
		}
	}


	MPI_Gather (C[from], SIZE*SIZE/num_of_procs, MPI_INT, C, SIZE*SIZE/num_of_procs, MPI_INT, 0, MPI_COMM_WORLD);

	if (process_number==0)
	{
		wait(NULL);
		printf("\n\n");
		print(A);
		printf("\n\n* \n");
		print(B);
		printf("\n\n= \n");
		print(C);
	}

	MPI_Finalize();
	return 0;
}

