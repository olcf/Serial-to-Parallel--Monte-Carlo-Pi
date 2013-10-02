Serial-to-Parallel--Monte-Carlo-Pi
==================================

This tutorial covers how to write a parallel program to calculate π using the Monte Carlo method with MPI and OpenMP. 

####Compiling and Running
Before you start, you will need to edit the submit scripts (submit.pbs and mpisubmit.pbs) and replace AAA123 with the correct project ID. Once done, you need to load the PGI programming environment

```
module load PrgEnv-pgi
```

To compile and submit the serial version, you need to run: ```make serial```

* For the MPI_Reduce verion: `make mpi`
* For the MPI Send/Recv verion: `make mpisr`
* For the OpenMP version: `make omp`
* For the hybrid OpenMP/MPI version: `make mpiomp`

The output should look something like:

```
Wed Sep 18 11:02:27 EDT 2013
Pi: 3.140800
Application 3587838 resources: utime ~0s, stime ~0s, Rss ~3444, inblocks ~4534, outblocks ~11970
```

The tutorial from which this code is from can be found on the OLCF website at: https://www.olcf.ornl.gov/tutorials/monte-carlo-pi/
