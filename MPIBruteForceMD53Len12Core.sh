#!/bin/bash

# Set the name of the job
#PBS -N MPIBruteForceMD53Len12Core

# Set a walltime for the job. The time format is HH:MM:SS
#PBS -l walltime=00:05:00

# Set number of nodes
#PBS -l nodes=1:ppn=12

# Join the output and error files
#PBS -j oe

# The following commands will be executed when this script is run.

module load torque/torque-4.2.3
module load moab/moab-7.2.2
module load openmpi/openmpi-1.6.4_gcc-4.7.2_torque-4.2.3_ib

cd $PBS_O_WORKDIR
make mpi_brute_force
make run_mpi_brute P=12 H=passlist/myspace_MD5.txt M=3 T=MD5 O=MPIBruteForceMD53Len12Core.txt
