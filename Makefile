serial: submit.pbs
	cc serialpi.c -o $(MEMBERWORK)/<PROJID>/pi.out
	cd $(MEMBERWORK)/<PROJID>
	qsub submit.pbs

mpi: mpisubmit.pbs
	cc mpireducepi.c -o $(MEMBERWORK)/<PROJID>/mpi.out
	cd $(MEMBERWORK)/<PROJID>
	qsub mpisubmit.pbs

mpisr: mpisubmit.pbs
	cc mpiSRpi.c -o $(MEMBERWORK)/<PROJID>/mpi.out
	cd $(MEMBERWORK)/<PROJID>
	qsub mpisubmit.pbs

omp: submit.pbs
	cc -mp omppi.c -o $(MEMBERWORK)/<PROJID>/pi.out
	cd $(MEMBERWORK)/<PROJID>
	qsub submit.pbs

mpiomp: mpisubmit.pbs
	cc -mp mpiomp.c -o $(MEMBERWORK)/<PROJID>)/mpi.out
	cd $(MEMBERWORK)/<PROJID>
	qsub mpisubmit.pbs
