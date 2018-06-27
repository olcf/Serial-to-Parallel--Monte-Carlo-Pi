all: serial mpi mpisr mpinbsr mpinbreduce omp mpiomp mpiSRnoverp mpireducenoverp
serial: serialpi.c
	cc serialpi.c -o serialpi.out

mpi: mpireducepi.c
	cc mpireducepi.c -o mpi-reducepi.out

mpisr: mpiSRpi.c
	cc mpiSRpi.c -o mpi-SRpi.out

mpinbsr: mpiSRnbpi.c
	cc mpiSRnbpi.c -o mpi-SRnbpi.out

mpinbreduce: mpiNBreducepi.c
	cc mpiNBreducepi.c -o mpi-nbreducepi.out

mpiSRnoverp: mpiSRpi-noverp.c
	cc mpiSRpi-noverp.c -o mpi-SR-noverp.out
mpireducenoverp: mpireduce-noverp.c
	cc mpireduce-noverp.c -o mpi-reduce-noverp.out

omp: submit.pbs
	cc -mp omppi.c -o omp-pi.out

mpiomp: mpisubmit.pbs
	cc -mp mpiomp.c -o omp-mpi-pi.out

clean:
	rm -f *.out
