set term pngcairo
set output "finalplot.png"
set logscale x 2
set logscale y 10
set xtic auto
set ytic auto
set title "Energy vs distance"
set ylabel "Energy"
set xlabel "distance"
plot "data.txt" usi 1:2 w lines title "vegas","data.txt" usi 1:3 w lines title "dipole","data.txt" usi 1:4 w lines title "Home made"




set output
