serial: submit.pbs
	cc serialpi.c -o /tmp/work/$(USER)/pi.out
	cd /tmp/work/$(USER)
	qsub submit.pbs

mpi: mpisubmit.pbs
	cc mpireducepi.c -o /tmp/work/$(USER)/mpi.out
	cd /tmp/work/$(USER)
	qsub mpisubmit.pbs

mpisr: mpisubmit.pbs
	cc mpiSRpi.c -o /tmp/work/$(USER)/mpi.out
	cd /tmp/work/$(USER)
	qsub mpisubmit.pbs

omp: submit.pbs
	cc -mp omppi.c -o /tmp/work/$(USER)/pi.out
	cd /tmp/work/$(USER)
	qsub submit.pbs

mpiomp: mpisubmit.pbs
	cc -mp mpiomp.c -o /tmp/work/$(USER)/mpi.out
	cd /tmp/work/$(USER)
	qsub mpisubmit.pbs
