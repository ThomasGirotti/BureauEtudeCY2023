#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846
#define k 9e9
#define e0 8.854e-12

// Structure pour représenter une charge ponctuelle
typedef struct {
    double q;    // Charge électrique
    double x;    // Position en x
    double y;    // Position en y
} Charge;

// Fonction pour calculer le champ électrique d'une charge ponctuelle en un point donné
void calculate_electric_field(double charge_q, double charge_x, double charge_y, double x, double y, double *Ex, double *Ey) {
    double r = sqrt((x - charge_x) * (x - charge_x) + (y - charge_y) * (y - charge_y));
    *Ex = (k * charge_q * (x - charge_x)) / (4 * PI * e0 * r * r * r);
    *Ey = (k * charge_q * (y - charge_y)) / (4 * PI * e0 * r * r * r);
}

int main() {
    // Déclaration des charges ponctuelles
    Charge charges[2];
    charges[0].q = 1.0;
    charges[0].x = 1.0;
    charges[0].y = 0.0;
    charges[1].q = -1.0;
    charges[1].x = -1.0;
    charges[1].y = 0.0;

    // Paramètres du maillage
    double xmin = -5.0;
    double xmax = 5.0;
    double ymin = -5.0;
    double ymax = 5.0;
    int num_points_x = 50;
    int num_points_y = 50;

    // Calcul et enregistrement des données du champ électrique dans un fichier texte
    FILE *file = fopen("electric_field_data.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    double dx = (xmax - xmin) / (num_points_x - 1);
    double dy = (ymax - ymin) / (num_points_y - 1);

    for (int i = 0; i < num_points_x; i++) {
        double x = xmin + i * dx;
        for (int j = 0; j < num_points_y; j++) {
            double y = ymin + j * dy;
            double Ex_total = 0.0;
            double Ey_total = 0.0;

            for (int k = 0; k < 2; k++) {
                double Ex, Ey;
                calculate_electric_field(charges[k].q, charges[k].x, charges[k].y, x, y, &Ex, &Ey);
                Ex_total += Ex;
                Ey_total += Ey;
            }

            fprintf(file, "%lf %lf %lf %lf\n", x, y, Ex_total, Ey_total);
        }
    }

    fclose(file);
    printf("Les données du champ électrique ont été enregistrées dans 'electric_field_data.txt'.\n");

    return 0;
}
