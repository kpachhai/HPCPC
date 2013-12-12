#!/bin/bash

# Set the name of the job
#PBS -N MPIBruteForceMD53Len4Core

# Set a walltime for the job. The time format is HH:MM:SS
#PBS -l walltime=00:30:00

# Set number of nodes
#PBS -l nodes=1:ppn=4

# Join the output and error files
#PBS -j oe

# The following commands will be executed when this script is run.
cd /home/campbetb/projects/HPCPC
make mpi_brute_force
make run_mpi_brute P=4 H=passlist/myspace_MD5.txt M=3 T=MD5 O=MPIBruteForceMD53Len4Core.txt
