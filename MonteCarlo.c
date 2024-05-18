#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv){
	MPI_Init(&argc, &argv);
	int world_rank;
	int world_size;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	const int  n = 100000;
	double x[n];
	double y[n];
	double pi;
	double z;
	int count = 0;
	int final_count = 0;
	const int  a = 10000;
	double b[a];
	const int  c = 10000;
	double d[c];	

	srand(time(NULL));
		
	if (world_rank == 0){
		for(int i=0; i<n; i++){
			x[i] = (double)random()/RAND_MAX;
			y[i] = (double)random()/RAND_MAX;
			}
	final_count += count;	
	}//end of world_rank ==0

	MPI_Scatter(x, n/world_size, MPI_DOUBLE, b, n/world_size, MPI_DOUBLE,0,MPI_COMM_WORLD);
	MPI_Scatter(y, n/world_size, MPI_DOUBLE, d, n/world_size, MPI_DOUBLE,0,MPI_COMM_WORLD);

	for(int i = 0; i < n/world_size; i++){
		z = sqrt(((b[i] * b[i])+(d[i]*d[i]))); //checking if x^2 + y^2 <= 1
		if (z <=1){
			count++;
		}//end of if statement
	}//end of for loop
	
	MPI_Reduce(&count, &final_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(world_rank ==0){
		pi = (((double)final_count/(double)n)*4);
		printf("Pi is: %f\n",pi);
		//printf("count is: %f\n", count);
		//printf("final_count is %f\n", final_count);
		//printf("Pi is: %c\n",pi);
	}//end of if statement
	
	MPI_Finalize();
}//end of main







