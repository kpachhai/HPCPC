#!/usr/bin/python

from pylab import *

#hak5.txt

size = [895, 2351, 12234, 394748, 4347667, 14344391]

totaltime1 = [0.01548, 0.05984, 0.22622, 6.90231, 76.488, 228.34]
totaltime2 = [0.01506, 0.03931, 0.20339, 6.63216, 73.2859, 234.92]
totaltime3 = [0.018626, 0.048791, 0.2569, 8.1812, 90.128, 301.36]

speedup1, = plot(size, totaltime1, 'b', label='MD5')
speedup2, = plot(size, totaltime2, 'g', label='SHA1')
speedup3, = plot(size, totaltime3, 'r', label='SHA256')
plot(size, totaltime1)
plot(size, totaltime2)
plot(size, totaltime3)

xlabel('Total number of hashes')
ylabel('Conversion time in seconds')
title('Comparison of MD5, SHA1, and SHA256 hashes creation time\non Intel Xeon CPU X5660 @ 2.80GHz 12288 KB Cache')
legend1 = legend([speedup1], ["MD5"], loc= 1)
legend2 = legend([speedup2], ["SHA-1"], loc=3)
legend3 = legend([speedup3], ["SHA-256"], loc=4)
gca().add_artist(legend1)
gca().add_artist(legend2)
gca().add_artist(legend3)
grid(True)
savefig("dictionary_creation.png")
show()

