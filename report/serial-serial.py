#!/usr/bin/python

from pylab import *

size = [895, 2351, 12234, 394748, 4347667, 14344391]

nCracked = [774, 558, 0.0009, 85732, 714583, 14319807]

#Basic dictionary attack using linear search
readtime1 = [12.397420, 13.553340, 12.626770, 12.345234, 13.721334, 12.342356]
exectime1 = [237.86730, 623.1140, 3415.370, 110212.71, 1213726.6, 4004472]
writetime1 = [0.0646690, 0.0008280, 0.0003809, 0.1129453, 0.913456, 18.34539]
totaltime1 = [237.86730, 623.1140, 3415.370, 110212.71, 1213726.6, 4004472]

#Basic dictionary attack using LevelDB
readtime2 = [0.000538, 0.001298, 0.003753, 0.095628, 0.941362, 2.855360]
exectime2 = [0.029511, 0.055223, 0.249778, 7.143320, 19.722, 42.57110]
writetime2 = [0.001044, 0.000787, 0.0000003, 0.102938, 0.837695, 17.16380]
totaltime2 = [0.031094, 0.057309, 0.253571, 7.341880, 21.501, 62.59020]

totaltime3 = [151, 396, 2064, 66599, 733517, 2420115]

time1, = semilogx(size, totaltime1, 'b', label='Basic Dictionary Attack w/ Linear Search')
time2, = semilogx(size, totaltime2, 'g', label='Dictionary Attack w/ LevelDB')
time3, = semilogx(size, totaltime3, 'k', label='OpenACC')
semilogy(size, nCracked, 'ro')
semilogy(size, totaltime1, 'bo')
semilogy(size, totaltime2, 'go')
semilogy(size, totaltime3, 'ko')

#Linear serial search
text(394748, 50000,'1 day', fontsize=15)
text(4347667, 413726, '14 days', fontsize=15)
text(14344391, 3004472, '46 days', fontsize=15)

#LevelDB B-tree search
text(394748, 1,'7 s', fontsize=15)
text(4347667, 5, '21 s', fontsize=15)
text(14344391, 20, '62 s', fontsize=15)

xlabel('Total number of hashes to crack')
ylabel('Time taken in seconds')
title('Comparison of dictionary lookup attack between two different serial versions\non Intel Xeon CPU X5660 @ 2.80GHz 12288 KB Cache')
legend1 = legend([time1], ["Basic Linear Search"], loc=1)
legend2 = legend([time2], ["LevelDB"], loc=3)
legend3 = legend([time3], ["OpenAcc"], loc=4)
gca().add_artist(legend1)
gca().add_artist(legend2)
gca().add_artist(legend3)
grid(True)
savefig("serial_comparison.png")
show()

