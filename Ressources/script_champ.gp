set xrange [-15:15]
set yrange [-15:15]
set xlabel "x (en mètres)"
set xlabel "y (en mètres)"
set title "Carte vectorielle du champ électrique dans l'approximation dipolaire"
set size ratio -1
set terminal pdf
set output"champ_electrique_vecteur.pdf"
set nokey
plot 'Ressources/champ.dat' using ($1):($2):($3):($4) with vectors