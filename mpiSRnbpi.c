#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"
/* totally arbitrary seed for srand */
#define SEED 314159

int main(int argc, char* argv[])
{
	long niter = 1000000;			
	int myid;							//hold's process's rank id
	int numnodes;
	double x,y;							//x,y value for the random coordinate
	int i, count=0;							//Count holds all the number of how many good coordinates
	double z;							//Used to check if x^2+y^2<=1
	double pi;							//holds approx value of pi


	MPI_Init(&argc, &argv);						//Start MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);				//get rank of node's process
	MPI_Comm_size(MPI_COMM_WORLD, &numnodes);

	int counts[numnodes];						// contains all processes circle point counts
	MPI_Status statuses[numnodes-1];					// node 0 doesn't receive from himself
	MPI_Request requests[numnodes-1];
	int temp;							// temp buffer to store incoming count messages on node 0

	/* Everyone needs a different seed or they'll get the same "random" sequence */
	srand(SEED+myid);							

	/* Have everyone do the work, then have one node coordinate results */
	for(i = 0; i < niter; i++)
	{
		x= ((double)rand())/RAND_MAX;			//gets a random x coordinate
		y =((double)rand())/RAND_MAX;			//gets a random y coordinate
		z = x*x+y*y;					//Checks to see if number in inside unit circle
		if (z<=1)
		{
			count++;				//if it is, consider it a valid random point
		}
	
	}
//	printf("I am node %d, my count was %d\n", myid, count);

	if(myid != 0) /* Everyone sends their contribution to node 0 */
	{
		MPI_Send(&count, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}

	else /* Node 0 needs to receive a message from everyone else */
	{
		/* Set node 0's contribution in the counts[] array */
		counts[0] = count;

		/* Since we aren't blocking, we can just post all of the receives at once */
		for(i = 1; i < numnodes; i++) // start receiving from node 1, in location 1
		{
			/* Note: requests array is 0 based, so we need to subtract 1 on the index */
			MPI_Irecv(&counts[i], 1, MPI_INT, i, 1, MPI_COMM_WORLD, &requests[i-1]);
		}

		/* Now we can just wait until all numnodes-1 messages come in */
		/* We aren't doing anything with statuses this time, so this could be MPI_STATUS_IGNORE */
		MPI_Waitall(numnodes-1, requests, statuses);
	}

	/* Ok, root has everyone's contributions; add them up and calculate Pi */
	if (myid == 0)	
	{      
		int final = 0;
		for(i = 0; i<numnodes; ++i)
		{
			final += counts[i];
		}

		long final_iters = numnodes*niter;

		pi = ((double)final/(double)final_iters)*4.0;	//p = 4(m/n)
		printf("%d nodes over %d iterations calculated Pi as: %f\n", numnodes, final_iters, pi);	//Print the calculated value of pi
	}

	MPI_Finalize();	//Close the MPI instance
	return 0;
}
