#!/usr/bin/python

from pylab import *

#hak5.txt

size = [1, 2, 4, 8, 12]

totaltime2 = [11.87, 13.553340, 12.626770, 12.345234, 13.721334]
totaltime3 = [11.87, 6.123, 3.1, 1.72, 1.3]

speedup2, = plot(size, totaltime2, 'g', label='MPI')
speedup3, = plot(size, totaltime3, 'r', label='MPI WITH HDF5')
plot(size, totaltime2)
plot(size, totaltime3)

xlabel('Total number of processors used')
ylabel('Read time in seconds')
title('Comparison of serial and parallel HDF5 read\non Intel Xeon CPU X5660 @ 2.80GHz 12288 KB Cache')
legend2 = legend([speedup2], ["Serial Read"], loc=3)
legend3 = legend([speedup3], ["Parallel Read w/ HDF5"], loc=4)
gca().add_artist(legend2)
gca().add_artist(legend3)
grid(True)
savefig("serial_hdf5_read.png")
show()

