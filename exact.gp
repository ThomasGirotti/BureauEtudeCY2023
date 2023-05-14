set term png
set output "electric_field_vectors.png"

# Définition des constantes et paramètres
k = 9e9  # Constante électrostatique
e0 = 8.854e-12  # Permittivité du vide

# Fonction pour calculer le champ électrique d'une charge ponctuelle
electric_field(charge_q, charge_x, charge_y, x, y) = (k * charge_q / (4 * pi * e0)) * \
                                                    ((x - charge_x) / ((x - charge_x)**2 + (y - charge_y)**2)**(3/2)) + \
                                                    ((y - charge_y) / ((x - charge_x)**2 + (y - charge_y)**2)**(3/2))

# Configuration du graphique
set xrange [-5:5]
set yrange [-5:5]
set size square

# Tracé du champ de vecteurs
dx = 0.5
dy = 0.5
do for [x=-5:5:dx] {
    do for [y=-5:5:dy] {
        ex = electric_field(1, 0, 0, x, y)
        ey = electric_field(-1, 1, 0, x, y)
        set arrow from x, y to x + dx * ex, y + dy * ey filled lc "blue" size 0.2
    }
}

plot NaN notitle
