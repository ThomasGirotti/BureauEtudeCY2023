# Définition des constantes et paramètres
q1 = 1.0  # Charge électrique 1
q2 = -1.0  # Charge électrique 2

# Configuration du graphique
set autoscale x
set autoscale y

set title "Carte vectorielle du champ électrique exacte"

set size ratio -1
# Chargement des données du champ électrique
set terminal pdf
set output"champ_electrique_vecteur.pdf"
set nokey

# Tracé du champ de vecteurs
plot 'electric_field_data.txt' using ($1):($2):($3/q1):($4/q1) with vectors head filled lc "blue" lw 1, \
     'electric_field_data.txt' using ($1):($2):($3/q2):($4/q2) with vectors head filled lc "red" lw 1
