#!/usr/bin/python

from pylab import *

#hak5.txt

size = [1, 2, 4, 6, 8]

totaltime2 = [400, 203, 100, 51, 38]
totaltime3 = [623, 395, 196, 149, 115]

time2, = plot(size, totaltime2, 'g', label='Dictionary Attack MPI')
time3, = plot(size, totaltime3, 'r', label='Dictionary Attack MPI WITH HDF5')
semilogy(size, totaltime2)
semilogy(size, totaltime3)

xlabel('Total number of hashes to crack')
ylabel('Time taken in seconds')
title('Comparison of dictionary lookup attack between MPI and MPI HD5\non Intel Xeon CPU X5660 @ 2.80GHz 12288 KB Cache')
legend2 = legend([time2], ["MPI"], loc=3)
legend3 = legend([time3], ["MPI w/ HDF5"], loc=4)
gca().add_artist(legend1)
gca().add_artist(legend2)
gca().add_artist(legend3)
grid(True)
savefig("serial_openmp_mpi_bruteforce_comparison.png")
show()

