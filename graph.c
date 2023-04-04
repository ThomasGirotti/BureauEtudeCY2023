void Graphe() {

    FILE* info_graph=NULL;  // Creation des variables locales
    FILE* gnuplot=NULL; //png
    char** exeCommandes;
    exeCommandes=malloc(50*sizeof(char*));  /* On alloue de l'espace pour notre tableau de char */
    for (int i=0; i<50; i++){
    exeCommandes=malloc(50*sizeof(char*));
    }
     exeCommandes[0]="set title \"Histogramme de luminance\"";   /* On vient stocker des lignes de commandes dans notre tableau de char */
     exeCommandes[1]="set ylabel \"Nb occurences\"";             /* Ces commandes permettront de créer notre image 'histo.png' */
     exeCommandes[2]="set xlabel \"Valeur de luminance\"";       /* On met le titre du graphique et de chaques axes*/
     exeCommandes[3]="set terminal png";                          /* On configure la sortie en fichier .png */
     exeCommandes[4]="set output 'histo.png'";                     /* Qu'on appellera 'histo.png' */
     exeCommandes[5]="unset key";                    /* On configure le style de représentation donnée en bar*/
     exeCommandes[6]="set style histogram cluster gap 1";           /* Toujours configuration du style de représentation (cluster=collée, gap=espacée de ) */
     exeCommandes[7]="set xrange [0:300]";                           /* On met la rangée d'affichage des X */
     exeCommandes[8]="set yrange [0:4000]";                           /* De même pour les Y*/
     exeCommandes[9]="set xtic 50";                                /* On met un pas pour les X de 50 */
     exeCommandes[10]="plot 'donneeGraph.dat' using 2:xtic(50)";   /* Creation du graphique en prenant les valeurs de du fichier 'donneeGraph' */
     exeCommandes[11]="q"; /* On quitte le gnuplot */

     info_graph=fopen("donneeGraph.dat","w"); /* On ouvre notre fichier en écriture*/

     gnuplot=popen("gnuplot","w"); /* On ouvre notre "executeur de commandes" */

     for (int i=0; i<256; i++){
    fprintf(info_graph,"%d %d\n",i,tab_Histo[i]); /* On remplit notre fichier info_graph */
     }

     for (int i=0; i<12; i++){
       fprintf(gnuplot,"%s\n",exeCommandes[i]);  /* On execute les commandes */
     }
     fclose(info_graph); /* On ferme les fichiers qu'on a utilisé */
     pclose(gnuplot);
}
