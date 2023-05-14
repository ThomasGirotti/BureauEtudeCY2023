#include <stdio.h>
#include <math.h>

#define e0 8.854187817e-12 // Constante électrique

// Fonction calculant le potentiel électrique
double electricPotential(double x, double y, double q1, double q2, double d) {
    double r1 = sqrt(x*x + y*y);
    double r2 = sqrt((x-d)*(x-d) + y*y);

    double potential1 = q1 / (4 * M_PI * e0 * r1);
    double potential2 = q2 / (4 * M_PI * e0 * r2);

    return potential1 + potential2;
}

int main() {
    // Paramètres des charges
    double q1 = 1.0; // Charge 1
    double q2 = -1.0; // Charge 2
    double d = 1.0; // Distance entre les charges

    // Dimensions de la grille
    int nx = 100; // Nombre de points en x
    int ny = 100; // Nombre de points en y

    // Limites de la grille
    double xmin = -5.0;
    double xmax = 5.0;
    double ymin = -5.0;
    double ymax = 5.0;

    // Pas de discrétisation
    double dx = (xmax - xmin) / (nx - 1);
    double dy = (ymax - ymin) / (ny - 1);

    // Calcul du potentiel électrique pour chaque point de la grille
    FILE *fp = fopen("electric_potential_data.txt", "w");
    if (fp == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    for (int i = 0; i < nx; i++) {
        double x = xmin + i * dx;

        for (int j = 0; j < ny; j++) {
            double y = ymin + j * dy;

            double potential = electricPotential(x, y, q1, q2, d);
            fprintf(fp, "%lf\t%lf\t%lf\n", x, y, potential);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("Les données du potentiel électrique ont été enregistrées dans le fichier 'electric_potential_data.txt'.\n");

    return 0;
}
