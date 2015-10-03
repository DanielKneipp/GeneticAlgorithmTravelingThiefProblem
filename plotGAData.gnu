if (!exists("filename")) filename='default.dat'
if (!exists("datatitle")) datatitle='default.dat'

set grid
set key bottom box

set style line 1 lc rgb '#0060ad' lt 1 lw 1.9 pt 7 ps 0.4

set title "GA Performance" 
set xlabel "Generation" 
set ylabel "Best Individual Fitness" 

plot filename using 1:2 title datatitle with linespoints ls 1

set terminal pdf
set output filename.'.pdf'
replot

pause -1  "Press ENTER to continue"