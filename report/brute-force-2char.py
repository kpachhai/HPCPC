#!/usr/bin/python

from pylab import *

#hak5.txt

size = [1, 2, 4, 5, 12]

totaltime1 = [23.595, 11.99, 6.121, 4.204, 2.899]
totaltime2 = [26.492, 13.563, 6.795, 4.7, 2.558]
totaltime3 = [35.754, 18.497, 9.16, 6.305, 3.471]

speedup1, = plot(size, totaltime1, 'b', label='MD5')
speedup2, = plot(size, totaltime2, 'g', label='SHA1')
speedup3, = plot(size, totaltime3, 'r', label='SHA256')
plot(size, totaltime1)
plot(size, totaltime2)
plot(size, totaltime3)

xlabel('Total number of processors used')
ylabel('Time taken in seconds')
title('Comparison of MD5, SHA1, and SHA256 brute force cracking\non Intel Xeon CPU X5660 @ 2.80GHz 12288 KB Cache')
legend1 = legend([speedup1], ["MD5"], loc= 1)
legend2 = legend([speedup2], ["SHA-1"], loc=3)
legend3 = legend([speedup3], ["SHA-256"], loc=4)
gca().add_artist(legend1)
gca().add_artist(legend2)
gca().add_artist(legend3)
grid(True)
savefig("brute_force_2_char.png")
show()

