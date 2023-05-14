#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

// Fonction pour calculer le champ électrique pour 2 charges ponctuelles
struct Vector calculate_electric_field(struct Point point, struct Charge charge1, struct Charge charge2) {
    double r1 = sqrt(pow((point.x - charge1.position.x), 2) + pow((point.y - charge1.position.y), 2));
    double r2 = sqrt(pow((point.x - charge2.position.x), 2) + pow((point.y - charge2.position.y), 2));

    double ex = (k / (4 * M_PI * e0)) * ((charge1.q * (point.x - charge1.position.x) / pow(r1, 3)) + (charge2.q * (point.x - charge2.position.x) / pow(r2, 3)));
    double ey = (k / (4 * M_PI * e0)) * ((charge1.q * (point.y - charge1.position.y) / pow(r1, 3)) + (charge2.q * (point.y - charge2.position.y) / pow(r2, 3)));

    struct Vector field = {ex, ey};
    return field;
}

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
  
    struct Point point = {2.0, 2.0}; // Point pour lequel le champ électrique est calculé

    struct Vector field = calculate_electric_field(point, charges[1], charges[2]);

    printf("Champ électrique au point (%lf, %lf): Ex = %lf, Ey = %lf\n", point.x, point.y, field.x, field.y);
    
    
    // Calculer l'équilibre électrostatique
    calculate_electrostatic_equilibrium(charges, num_charges);
    
    for (int i = 0; i < num_charges; i++) {
        printf("Position de la charge %d : (%lf, %lf)\n", i+1, charges[i].position.x, charges[i].position.y);
    }
  
    return 0;
}
