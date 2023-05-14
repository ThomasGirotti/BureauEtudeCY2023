set terminal pdf
set palette define
set datafile separator
set xrange [-0.0001:0.0001]
set yrange [-0.0001:0.0001]
set xlabel "x (en mètres)"
set ylabel "y (en mètres)"
set title "Carte de chaleur du potentiel électrique avec équipotentielles dans l'approximation dipolaire" font ",10"
set output "carte_de_chaleur.pdf"

f1(t) = sqrt((abs(cos(t)))/(4 * 3.1415))*0.0003
f2(t) = sqrt((abs(cos(t)))/(4 * 3.1415))*0.0003 * 2
f3(t) = sqrt((abs(cos(t)))/(4 * 3.1415))*0.0003 * 3

x1(t) = f1(t)*cos(t)
y1(t) = f1(t)*sin(t)
x2(t) = f2(t)*cos(t)
y2(t) = f2(t)*sin(t)
x3(t) = f3(t)*cos(t)
y3(t) = f3(t)*sin(t)

set parametric
set trange [-pi:pi]
plot 'Ressources/potentiel.dat' using 1:2:3 with image, x1(t),y1(t) title "Equipotentielles"  linecolor rgb 'blue', x2(t),y2(t) notitle linecolor rgb 'blue', x3(t),y3(t) notitle linecolor rgb 'blue'
unset parametric