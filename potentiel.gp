set term png
set output "electric_potential_heatmap.png"

# Définition des constantes et paramètres
set contour base
set cntrparam levels incremental -1,0.1,1
unset surface
set view map

# Données du potentiel électrique
q1 = 1.0  # Charge électrique 1
q2 = -1.0  # Charge électrique 2
d = 1.0  # Distance entre les charges

# Fonction du potentiel électrique
potential(x, y) = (q1 / (4 * pi * e0 * sqrt(x2 + y2))) + (q2 / (4 * pi * e0 * sqrt((x-d)2 + y2)))

# Configuration du graphique
set xrange [-5:5]
set yrange [-5:5]
set size square

# Tracé de la carte de chaleur
set palette defined (-1 "blue", 0 "white", 1 "red")
splot potential(x, y) with pm3d, NaN notitle

# Tracé des équipotentielles
unset surface
unset pm3d
set contour
splot potential(x, y) with lines lc "black" lw 1 notitle
