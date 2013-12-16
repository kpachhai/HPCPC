#!/usr/bin/python

from pylab import *

#hak5.txt

size = [1, 2, 5, 12]

totaltime1 = [1432.426, 852.303, 303.665, 140.389]
totaltime2 = [1613.82, 972.237, 341.157, 157.54]
totaltime3 = [2182.501, 1134.809, 441.792, 208.611]

speedup1, = plot(size, totaltime1, 'b', label='MD5')
speedup2, = plot(size, totaltime2, 'g', label='SHA1')
speedup3, = plot(size, totaltime3, 'r', label='SHA256')
plot(size, totaltime1)
plot(size, totaltime2)
plot(size, totaltime3)

xlabel('Total number of processors used')
ylabel('Time taken in seconds')
title('Comparison of MD5, SHA1, and SHA256 brute force cracking OpenMP\non Intel Xeon CPU X5660 @ 2.80GHz 12288 KB Cache')
legend1 = legend([speedup1], ["MD5"], loc= 1)
legend2 = legend([speedup2], ["SHA-1"], loc=3)
legend3 = legend([speedup3], ["SHA-256"], loc=4)
gca().add_artist(legend1)
gca().add_artist(legend2)
gca().add_artist(legend3)
grid(True)
savefig("brute_force_3_charOPENMP.png")
show()

