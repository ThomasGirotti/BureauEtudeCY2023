set term png
set output "electric_potential_heatmap.png"

# Définition des constantes et paramètres
set contour base
set cntrparam levels incremental -1,0.1,1
unset surface
set view map

# Configuration du graphique
set xrange [-5:5]
set yrange [-5:5]
set size square

# Tracé de la carte de chaleur

set palette defined (-1 "blue", 0 "white", 1 "red")

# Tracé de la carte de chaleur
splot "electric_potential_data.txt" using 1:2:3 with pm3d title "Carte de chaleur du potentiel électrique"

# Tracé des équipotentielles
unset surface
unset pm3d
set contour
splot "electric_potential_data.txt" using 1:2:3 with lines lc "black" lw 1 title "Équipotentielles"
