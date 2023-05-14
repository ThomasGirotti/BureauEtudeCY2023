#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define EPSIL0 8.845187 * pow(10,-12)

/* CALCUL DES VARIABLES */
/* Champ en fonction de l'axe Er */
double champEr(double theta,double r,double moment){
    double Er;
    Er = (2*moment*cos(theta))/(4*PI*r*r*r*EPSIL0);
    return Er;
}

/* Champ en fonction de l'axe Et */
double champEt(double theta,double r,double moment){
    double Et;
    Et = (moment*sin(theta))/(4*PI*r*r*r*EPSIL0);
    return Et;
}

/* Equipotentielle */
double equipotentielle(double theta,double r,double moment) {
    double V;
    V = (moment * cos(theta))/(4 * PI * r * r * EPSIL0);
    return V;
}
/* FIN CALCUL DES VARIABLES */

/* CREATION DES FICHIERS .DAT POUR GNUPLOT */
/* Pour le champ */
void champpointdat(double x0,double y0,double moment) {
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
            milieu = max/2; //Initialisation des variables en fonction de i et j
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
                FichierDATrintf(FichierDAT,"0 0 INF INF \n");
            }else{ //Sinon
                FichierDATrintf(FichierDAT, "%g %g %g %g\n",x,y,Ex,Ey);
            }
        }
    }
    fclose(FichierDAT);
}

/* Pour les équipotentielles */
void equippointdat(double x0,double y0,double moment) {
    FILE *FichierDAT;
    FichierDAT = fopen("Ressources/equipotentielle.dat", "w");
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
                FichierDATrintf(FichierDAT,"0 0 INF\n");
            }else{ //Sinon
                FichierDATrintf(FichierDAT, "%g %g %g \n",x,y,V);
            }
        }
    }
    fclose(FichierDAT);
}
/* FIN CREATION DES FICHIERS .DAT POUR GNUPLOT */

/* La fonction main affichera la représentation en utilisant gnuplot */
int main(int argc, char *argv[]){
    /* Création des variables */
    FILE * gnuplotPipe;
    int mode;
    
    /* On demande à l'utilisateur quel mode il veut */
    printf("\nBienvenue dans le programme de modelisation de champ electrique !\n");
    printf("Ce programme vous permettra de modeliser le champ electrique d'un dipole ou d'un ensemble de charges ponctuelles.\n");
    printf("Dans quel cas souhaitez vous vous situez ?\n\n");
    printf("1 : Approximation Dipolaire\n");
    printf("2 : Cas Général\n");
    printf("Entrez le mode voulu : ");

    scanf("%d",&mode); //Récuperation du mode voulu
    champpointdat(0,0,1); //Initialisation des fichiers 'dat' pour gnuplot
    equippointdat(0,0,1);
    /* Selon le mode choisi par l'utilisateur */
    switch (mode){
    case 1: //Affichage selon l'approximation dipolaire
        gnuplotPipe = popen ("gnuplot -persistent", "w");
        FichierDATrintf(gnuplotPipe,"load 'Ressources/script_champ.gp'\n");
        FichierDATrintf(gnuplotPipe,"load 'Ressources/script_equipotentielles.gp'\n");
        FichierDATrintf(gnuplotPipe,"load 'Ressources/script_modelisation.gp'\n");
        FichierDATrintf(gnuplotPipe,"exit\n");
        printf("\nLes graphes ont été fabriqués\n");
        break;
    case 2:
        gnuplotPipe = popen ("gnuplot -persistent", "w");
        FichierDATrintf(gnuplotPipe,"exit\n");
        printf("\nLes graphes ont été fabriqués\n");
        break; 
    default:
        printf("ERREUR MODE: CE MODE N'EXISTE PAS (VEUILLEZ CHOISIR ENTRE 1 ET 2)\n");
        return 1;
        break;
    }
    return 0;
}
