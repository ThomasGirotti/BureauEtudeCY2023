set term png
set output "electric_field_vectors.png"

# Définition des constantes et paramètres
q1 = 1.0  # Charge électrique 1
q2 = -1.0  # Charge électrique 2

# Configuration du graphique
set xrange [-5:5]
set yrange [-5:5]
set size square

# Chargement des données du champ électrique
set table 'electric_field_data.txt'
plot "< ./electric_field" with vectors notitle
unset table

# Tracé du champ de vecteurs
plot 'electric_field_data.txt' using 1:2:($3/q1):($4/q1) with vectors head filled lc "blue" lw 1 notitle, \
     'electric_field_data.txt' using 1:2:($3/q2):($4/q2) with vectors head filled lc "red" lw 1 notitle
