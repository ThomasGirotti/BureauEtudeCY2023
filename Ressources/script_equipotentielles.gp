set datafile separator
set xrange [-0.0005:0.0005]
set yrange [-0.0005:0.0005]
set xlabel "x (en mètres)"
set ylabel "y (en mètres)"
set palette define
set title "Carte de chaleur du potentiel électrique dans l'approximation dipolaire"
set terminal pdf
set output "carte_de_chaleur.pdf"
plot 'Ressources/equipotentielle.dat' using 1:2:3 with image