#include <stdio.h>
#include <math.h>

#define k 9e9 // Constante électrostatique
#define e0 8.854e-12 // Permittivité du vide

struct Point {
    double x;
    double y;
};

struct Charge {
    double q;
    struct Point position;
};

struct Vector {
    double x;
    double y;
};

// Fonction pour calculer la somme des forces électrostatiques exercées sur une charge
struct Vector calculate_electrostatic_force(struct Charge charge, struct Charge* charges, int num_charges) {
    struct Vector force = {0.0, 0.0};

    for (int i = 0; i < num_charges; i++) {
        if (charge.position.x != charges[i].position.x || charge.position.y != charges[i].position.y) {
            double dx = charges[i].position.x - charge.position.x;
            double dy = charges[i].position.y - charge.position.y;
            double r = sqrt(dx * dx + dy * dy);
            double f = (k * charge.q * charges[i].q) / (r * r * r);

            force.x += f * dx;
            force.y += f * dy;
        }
    }

    return force;
}

// Fonction pour calculer l'équilibre électrostatique sans jacobienne
void calculate_electrostatic_equilibrium(struct Charge* charges, int num_charges) {
    double tolerance = 1e-6; // Tolérance pour la condition d'équilibre
    int max_iterations = 1000; // Nombre maximum d'itérations
    int iterations = 0;
    double max_force = 0.0;

    do {
        max_force = 0.0;

        // Calculer les forces électrostatiques sur chaque charge
        for (int i = 0; i < num_charges; i++) {
            struct Vector force = calculate_electrostatic_force(charges[i], charges, num_charges);
            double magnitude = sqrt(force.x * force.x + force.y * force.y);

            // Mettre à jour la force maximale
            if (magnitude > max_force) {
                max_force = magnitude;
            }

            // Mettre à jour la position de la charge en fonction de la force
            charges[i].position.x += force.x;
            charges[i].position.y += force.y;
        }

        iterations++;
    } while (max_force > tolerance && iterations < max_iterations);

    if (iterations == max_iterations) {
        printf("L'équilibre électrostatique n'a pas été atteint dans le nombre maximum d'itérations.\n");
    } else {
        printf("L'équilibre électrostatique a été atteint en %d itérations.\n", iterations);
    }
}

int main() {
    struct Charge charges[2] = {
        {1.0, {0.0, 0.0}}, // Charge 1 : q = 1.0, position (0.0, 0.0)
        {-1.0, {1.0, 0.0}} // Charge 2 : q = -1.0, position (1.0, 0.0)
    };

    int num_charges = 2;

    // Calculer l'équilibre électrostatique
    calculate_electrostatic_equilibrium(charges, num_charges);

// Afficher les positions finales des charges
    for (int i = 0; i < num_charges; i++) {
        printf("Position de la charge %d : (%lf, %lf)\n", i+1, charges[i].position.x, charges[i].position.y);
    }

    return 0;
}
