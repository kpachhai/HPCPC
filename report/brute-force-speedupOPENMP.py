#!/usr/bin/python

from pylab import *

#hak5.txt

size = [1, 2, 5, 12]

totaltime1 = [1, 1432.426/852.303, 1432.426/303.665, 1432.426/140.389]
totaltime2 = [1, 1613.82/972.237, 1613.82/341.157, 1613.82/157.54]
totaltime3 = [1, 2182.501/1134.809, 2182.501/441.792, 2182.501/208.611]

speedup1, = plot(size, totaltime1, 'b', label='MD5')
speedup2, = plot(size, totaltime2, 'g', label='SHA1')
speedup3, = plot(size, totaltime3, 'r', label='SHA256')
plot(size, totaltime1, 'b--')
plot(size, totaltime2, 'g--')
plot(size, totaltime3, 'r--')

xlabel('Total number of processors used')
ylabel('Speedup')
title('Comparison of MD5, SHA1, and SHA256 brute force speedup OpenMP\non Intel Xeon CPU X5660 @ 2.80GHz 12288 KB Cache')
legend1 = legend([speedup1], ["MD5"], loc= 1)
legend2 = legend([speedup2], ["SHA-1"], loc=3)
legend3 = legend([speedup3], ["SHA-256"], loc=4)
gca().add_artist(legend1)
gca().add_artist(legend2)
gca().add_artist(legend3)
grid(True)
savefig("brute_force_3_char_speedupOPENMP.png")
show()

