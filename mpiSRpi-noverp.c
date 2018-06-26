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
	MPI_Status status;


	MPI_Init(&argc, &argv);						//Start MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);				//get rank of node's process
	MPI_Comm_size(MPI_COMM_WORLD, &numnodes);

	int counts[numnodes];						// contains all processes circle point counts
	int temp;							// temp buffer to store incoming count messages on node 0

	int myiters =  XXXXX; 
	int totaliters = 0;					// required since niter might not be divisible by numnodes
	/* Everyone needs a different seed or they'll get the same "random" sequence */
	srand(SEED+myid);							

	/* Have everyone do the work, then have one node coordinate results */
	for(i = 0; i < XXXXX  ; i++)
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
		/* This send needs to be different than the one for count somehow. Tag? */
		MPI_Send( XXXXX );
	}

	else /* Node 0 needs to receive a message from everyone else */
	{
		/* Put root's count in place */
		totaliters = XXXXX /* add node 0's iterations */
		counts[0] = count;
		for(i = 0; i < numnodes-1; i++)
		{
			/* We don't know who will be done first, so we need to post an MPI_ANY_SOURCE receieve */
			MPI_Recv(&temp, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
			/* Find out who this MPI_Recv() message came from */
			counts[status.MPI_SOURCE] = temp;

			/* For this program, we could have just done final += temp; We'll do that with iters. */
			/* But this way there was an example of using MPI_Status fields */
			MPI_Recv( XXXXX ) /* don't forget to differentiate this receive from the previous one somehow */
			totaliters += XXXXX
		}
	}

	/* Ok, root has everyone's contributions; add them up and calculate Pi */
	if (myid == 0)	
	{      
		int final = 0;
		for(i = 0; i<numnodes; ++i)
		{
			final += counts[i];
		}

		pi = ((double)final/(double) totaliters )*4.0;	//p = 4(m/n)
		printf("%d nodes over %d iterations calculated Pi as: %f\n", numnodes, totaliters, pi);	//Print the calculated value of pi
	}

	MPI_Finalize();	//Close the MPI instance
	return 0;
}
