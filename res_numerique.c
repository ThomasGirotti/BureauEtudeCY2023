#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define EPSIL0 8.845187 * pow(10,-12)

double champEr(double theta,double r,double moment){
    double Er;
    Er = (2*moment*cos(theta))/(4*PI*r*r*r*EPSIL0);
    return Er;
}

double champEt(double theta,double r,double moment){
    double Et;
    Et = (moment*sin(theta))/(4*PI*r*r*r*EPSIL0);
    return Et;
}

double equipotentielle(double theta,double r,double moment) {
    double V;
    V = (moment * cos(theta))/(4 * PI * r * r * EPSIL0);
    return V;
}

void champpointdat(double x0,double y0,double moment) {
    FILE *fp;
    fp = fopen("Ressources/champ.dat", "w");
    double theta;
    double r;
    double x,y;
    double mid,max;
    double stock;
    double Ex,Ey;

    max = 30;

    for (int i = 0; i < max; i++) {
        for(int j=0;j < max;j++){
            mid = max/2;
            x = i-mid;
            y = j-mid;

            r = sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0));

            theta = atan2(y - y0, x - x0);

            Ex = champEr(theta,r,moment) * cos(theta) - champEt(theta,r,moment) * sin(theta);
            Ey = champEr(theta,r,moment) * sin(theta) + champEt(theta,r,moment) * cos(theta);
            stock = Ex;
            Ex = (Ex)/(sqrt(Ex*Ex + Ey*Ey));
            Ey = (Ey)/(sqrt(stock*stock + Ey*Ey));

            if((i==mid)&&(j==mid)){
                fprintf(fp,"0 0 INF INF \n");
            }else{
                fprintf(fp, "%g %g %g %g\n",x,y,Ex,Ey);
            }
        }
    }
    fclose(fp);
}

void equippointdat(double x0,double y0,double moment) {
    FILE *fp;
    fp = fopen("Ressources/equipotentielle.dat", "w");
    double theta;
    double r;
    double x,y;
    double mid,max;
    double V;

    max = 0.001;
    mid = max/2;

    for (double i = -mid; i <  mid;i += 0.00001){
        for(double j= -mid;j <  mid;j += 0.00001){
        
            x = i;
            y = j;
            if((x<0.000000001)&&(x>0)){
                x=0;
            }
            if((y<0.000000001)&&(y>0)){
                y=0;
            }

            r = sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0));
            theta = atan2(y - y0, x - x0);
            V = equipotentielle(theta,r,moment);

            if((i==mid)&&(j==mid)){
                fprintf(fp,"0 0 INF\n");
            }else{
                fprintf(fp, "%g %g %g \n",x,y,V);
            }
        }
    }
    fclose(fp);
}

int main(int argc, char *argv[]){
    FILE * gnuplotPipe;
    // Vérifier s'il y a au moins une charge (le nom du programme compte comme un argument)
    /*if (argc < 2) {
        printf("Usage: %s <charge1> [<charge2> ...]\n", argv[0]);
        return 1;
    }

    int nbcharge = argc - 1;

    // Parcourir les arguments pour récupérer les informations des charges
    for (int i = 0; i < nbcharge; i++) {
        // Récupérer les informations de charge à partir de la chaîne de caractères
        sscanf(argv[i + 1], "%d,%d,%d", &(charges[i].x), &(charges[i].y), &(charges[i].q));
    }

    // Afficher les informations des charges
    for (int i = 0; i < nbcharge; i++) {
        printf("Charge %d:\n", i + 1);
        printf("  Coordonnée x : %d\n", charges[i].x);
        printf("  Coordonnée y : %d\n", charges[i].y);
        printf("  Valeur : %d\n", charges[i].q);
        printf("\n");
    }*/
    printf("\nBienvenue dans le programme de modelisation de champ electrique !\n");
    printf("Ce programme vous permettra de modeliser le champ electrique d'un dipole ou d'un ensemble de charges ponctuelles.\n");
    printf("Dans quel cas souhaitez vous vous situez ?\n\n");
    printf("1 : Approximation Dipolaire\n");
    printf("2 : Cas Général\n");
    printf("Entrez le mode voulu : ");
    int cle;
    scanf("%d",&cle);
    champpointdat(0,0,1);
    equippointdat(0,0,1);
    switch (cle){
    case 1:
        gnuplotPipe = popen ("gnuplot -persistent", "w");
        fprintf(gnuplotPipe,"load 'Ressources/script_champ.gp'\n");
        fprintf(gnuplotPipe,"load 'Ressources/script_equipotentielles.gp'\n");
        fprintf(gnuplotPipe,"load 'Ressources/script_modelisation.gp'\n");
        fprintf(gnuplotPipe,"exit\n");
        printf("\nLes graphes de l'approximation dipolaire ont été correctement générés !\n");
        break;
    case 2:
        printf("ERREUR : MODE 2 NON FINALISE\n");
        return 2;
        break; 
    default:
        printf("ERREUR : MODE DE SELECTION INVALIDE\n");
        return 1;
        break;
    }
    return 0;
}