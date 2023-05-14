set term png
set output "electric_potential_heatmap.png"

# Définition des constantes et paramètres
q1 = 1.0  # Charge électrique 1
q2 = -1.0  # Charge électrique 2
d = 1.0  # Distance entre les charges
e0 = 8.85418782e-12  # Permittivité du vide

# Fonction du potentiel électrique
potential(x, y) = (q1 / (4 * pi * e0 * sqrt(x**2 + y**2))) + (q2 / (4 * pi * e0 * sqrt((x-d)**2 + y**2)))

# Configuration du graphique
set contour base
set cntrparam levels incremental -1,0.1,1
unset surface

# Plage des axes
set xrange [-5:5]
set yrange [-5:5]

# Tracé de la carte de chaleur
unset key
set palette defined (-1 "blue", 0 "white", 1 "red")
set pm3d interpolate 20,20
splot potential(x, y) with pm3d notitle

# Tracé des équipotentielles
unset pm3d
set contour
set cntrparam levels incremental -1,0.1,1
splot potential(x, y) with lines lc "black" lw 1 notitle
