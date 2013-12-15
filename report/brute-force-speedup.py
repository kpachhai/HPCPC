#!/usr/bin/python

from pylab import *

#hak5.txt

size = [1, 2, 4, 6, 12]

totaltime1 = [1, 1475.306/750.168, 1475.306/378.41, 1475.306/258.975, 1475.306/142.029]
totaltime2 = [1, 1683.945/848.522, 1683.945/425.848, 1683.945/296.982, 1683.945/160.988]
totaltime3 = [1, 2259.829/1134, 2259.829/565, 2259.829/391.759, 2259.829/215.33]

speedup1, = plot(size, totaltime1, 'b', label='MD5')
speedup2, = plot(size, totaltime2, 'g', label='SHA1')
speedup3, = plot(size, totaltime3, 'r', label='SHA256')
plot(size, totaltime1, 'b--')
plot(size, totaltime2, 'g--')
plot(size, totaltime3, 'r--')

xlabel('Total number of processors used')
ylabel('Speedup')
title('Comparison of MD5, SHA1, and SHA256 brute force speedup\non Intel Xeon CPU X5660 @ 2.80GHz 12288 KB Cache')
legend1 = legend([speedup1], ["MD5"], loc= 1)
legend2 = legend([speedup2], ["SHA-1"], loc=3)
legend3 = legend([speedup3], ["SHA-256"], loc=4)
gca().add_artist(legend1)
gca().add_artist(legend2)
gca().add_artist(legend3)
grid(True)
savefig("brute_force_3_char_speedup.png")
show()

