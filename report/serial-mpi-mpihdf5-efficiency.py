#!/usr/bin/python

from pylab import *

#hak5.txt

size = [1, 2, 4, 6, 8]

totaltime2 = [1, 1.97/2, 4/4, 7.84/6, 10.52/8]
totaltime3 = [1, 1.57/2, 3.17/4, 4.18/6, 5.41/8]

speedup2, = plot(size, totaltime2, 'g', label='MPI')
speedup3, = plot(size, totaltime3, 'r', label='MPI WITH HDF5')
plot(size, totaltime2, 'g--')
plot(size, totaltime3, 'r--')

xlabel('Total number of processors used')
ylabel('Efficiency')
title('Comparison of efficiency for dictionary attack between MPI and MPI HD5\non Intel Xeon CPU X5660 @ 2.80GHz 12288 KB Cache')
legend2 = legend([speedup2], ["MPI"], loc=3)
legend3 = legend([speedup3], ["MPI w/ HDF5"], loc=4)
gca().add_artist(legend2)
gca().add_artist(legend3)
grid(True)
savefig("serial_mpi_mpihdf5_efficiency.png")
show()

