set polar
set key
set size ratio -1
set xrange [-5:5]
set yrange [-5:5]
set xlabel "x (en mètres)"
set xlabel "y (en mètres)"
set title "Modélisation des lignes de champ et des équipotentielles dans l'approximation dipolaire" font ",10"
set terminal pdf
set output "ldc_equipotentielle.pdf"

f1(t) = sqrt((abs(cos(t)))/(4 * 3.1415))*3.55
f2(t) = sqrt((abs(cos(t)))/(4 * 3.1415))*3.55 * 2
f3(t) = sqrt((abs(cos(t)))/(4 * 3.1415))*3.55 * 3
f4(t) = sqrt((abs(cos(t)))/(4 * 3.1415))*3.55 * 4

r1(t) = sin(t)**2
r2(t) = sin(t)**2 * 2
r3(t) = sin(t)**2 * 3
r4(t) = sin(t)**2 * 4

plot r1(t) title "Ligne de champ" linecolor rgb 'red', \
r2(t) notitle linecolor rgb 'red', \
r3(t) notitle linecolor rgb 'red', \
r4(t) notitle linecolor rgb 'red', \
f1(t) title "Equipotentielles" linecolor rgb 'blue', \
f2(t) notitle linecolor rgb 'blue', \
f3(t) notitle linecolor rgb 'blue', \
f4(t) notitle linecolor rgb 'blue'
