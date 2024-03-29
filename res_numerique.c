#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define EPSIL0 8.845187 * pow(10,-12)

/* CALCUL DES VARIABLES */
/* Equipotentielle */
double equipotentielle(double theta,double r,double moment) {
    double V;
    V = (moment * cos(theta)) / (4 * PI * r * r * EPSIL0);
    return V;
}

/* Champ en fonction de l'axe Er */
double champEr(double theta,double r,double moment){
    double Er;
    Er = (2 * moment * cos(theta)) / (4 * PI * r * r * r * EPSIL0);
    return Er;
}

/* Champ en fonction de l'axe Et */
double champEt(double theta,double r,double moment){
    double Et;
    Et = (moment * sin(theta)) / (4 * PI * r * r * r * EPSIL0);
    return Et;
}

/* FIN CALCUL DES VARIABLES */

/* CREATION DES FICHIERS .DAT POUR GNUPLOT */
/* Pour les équipotentielles */
void equipotentielleDAT(double x0,double y0,double moment) {
    FILE *FichierDAT; //Création des variables
    FichierDAT = fopen("Ressources/potentiel.dat", "w");
    double theta;
    double r;
    double x,y;
    double milieu,max;
    double V;

    max = 0.001;
    milieu = max/2;

    for (double i = -milieu; i <  milieu;i += 0.00001){
        for(double j= -milieu;j <  milieu;j += 0.00001){
            //Initialisation des variables en fonction de i et j
            x = i;
            y = j;
            if((x<0.000000001)&&(x>0)){ //On arrondit si x trop petit
                x=0;
            }
            if((y<0.000000001)&&(y>0)){ //De même pour y
                y=0;
            }

            r = sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0));
            theta = atan2(y - y0, x - x0);
            V = equipotentielle(theta,r,moment);
            
            //On écrit les valeurs dans le .dat selon la position (i,j)
            if((i==milieu)&&(j==milieu)){ //Si on est au milieu
                fprintf(FichierDAT,"0 0 INF\n");
            }else{ //Sinon
                fprintf(FichierDAT, "%g %g %g \n",x,y,V);
            }
        }
    }
    fclose(FichierDAT);
}

/* Pour le champ */
void champDAT(double x0,double y0,double moment) {
    FILE *FichierDAT; //Création des variables
    FichierDAT = fopen("Ressources/champ.dat", "w");
    double theta;
    double r;
    double x,y;
    double milieu,max;
    double stock;
    double Ex,Ey;

    max = 30;

    for (int i = 0; i < max; i++) {
        for(int j=0;j < max;j++){
            milieu = max/2; //Initialisation des variables en fonction de i et j et passage en coordonnées cartésiennes
            x = i-milieu; 
            y = j-milieu;

            r = sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0));

            theta = atan2(y - y0, x - x0);

            Ex = champEr(theta,r,moment) * cos(theta) - champEt(theta,r,moment) * sin(theta);
            Ey = champEr(theta,r,moment) * sin(theta) + champEt(theta,r,moment) * cos(theta);
            stock = Ex;
            Ex = (Ex)/(sqrt(Ex*Ex + Ey*Ey));
            Ey = (Ey)/(sqrt(stock*stock + Ey*Ey));
            
            //On écrit les valeurs dans le .dat selon la position (i,j)
            if((i==milieu)&&(j==milieu)){ //Si on est au milieu
                fprintf(FichierDAT,"0 0 INF INF \n");
            }else{ //Sinon
                fprintf(FichierDAT, "%g %g %g %g\n",x,y,Ex,Ey);
            }
        }
    }
    fclose(FichierDAT);
}
/* FIN CREATION DES FICHIERS .DAT POUR GNUPLOT */

/* La fonction main affichera la représentation du champ electrique en utilisant gnuplot */
int main(int argc, char *argv[]){
    /* Création des variables */
    FILE * gnuplotPipe; //fichier qui executera les commandes gnuplot
    int mode;
    
    //INTERFACE GRAPHIQUE
    printf("\n-- PROGRAMME DE MODELISATION --\n\n");
    printf("1 : Avec l'Approximation Dipolaire\n");
    printf("2 : Avec l'Expression exacte\n");
    printf("Veuillez choisir un mode (1 ou 2):\n"); 
    scanf("%d",&mode); //Récuperation du mode voulu dans la variable 'mode'
    champDAT(0,0,1); //Initialisation des fichiers 'dat' pour gnuplot
    equipotentielleDAT(0,0,1);
    /* Selon le mode choisi par l'utilisateur */
    switch (mode){
    case 1: //Affichage selon l'approximation dipolaire
        gnuplotPipe = popen ("gnuplot -persistent", "w");
        fprintf(gnuplotPipe,"load 'Ressources/script_champ.gp'\n");
        fprintf(gnuplotPipe,"load 'Ressources/script_potentiel.gp'\n");
        fprintf(gnuplotPipe,"load 'Ressources/script_modelisation.gp'\n");
        fprintf(gnuplotPipe,"exit\n");
        printf("\nLes graphes ont été fabriqués\n");
        break;
    case 2:
        gnuplotPipe = popen ("gnuplot -persistent", "w");
        fprintf(gnuplotPipe,"exit\n");
        printf("\nLes graphes ont été fabriqués\n");
        break; 
    default:
        printf("ERREUR MODE: CE MODE N'EXISTE PAS\n");
        printf("\n-- FERMETURE DU PROGRAMME SUITE A UNE ERREUR --\n")
        return 1;
        break;
    }
    printf("\n-- FIN DU PROGRAMME --\n")
    return 0;
}
