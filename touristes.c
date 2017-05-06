#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/* Fonction permettant de calculer la consomation de carburant
 * accX et accY accélérations actuelles
 * velX et velY vitesses actuelles
 * dansSable indique si la formule1 est sur une case de sable
 * retourne la variation de carburant
 *
 * Attention, même si le mouvement est illégal (donc pas de déplacement), il y a consomation de carburant
 * il faut donc éviter à tout prix de produire des mouvements illégaux
 */

int deltaCarburantAcceleration(int accX, int accY, int velX, int velY, int dansSable) {
    int valeur = accX * accX + accY*accY;
    valeur += (int) (sqrt(velX * velX + velY * velY)*3.0 / 2.0);
    if (dansSable) valeur += 1;
    return -valeur;
}

int** create_matrix(File* circuit) {
    int** circuit;
    circuit = malloc(sizeof (int*)*tx);
    for (int i; i < ty; i++) {
        circuit[i] = calloc(ty, sizeof (int));
    }
}

/**
 * Adds 1 to every neighbour of a point.
 */
void plus_one(int x, int y, int tx, int ty, int** mat, int** circuit) {
    if (mat[x - 1][y - 1] == 0 && circuit[x - 1][y - 1] != '=') { // --
        if (circuit[x - 1][y - 1] == '~') {
            mat[x - 1][y - 1] = mat[x][y] + 2;
        } else {
            mat[x - 1][y - 1] = mat[x][y] + 1;
        }
    }
    if (mat[x][y - 1] != 0 && circuit[x][y - 1] != '=') { // =-
        if (circuit[x][y - 1] == '~') {
            mat[x][y - 1] = mat[x][y] + 2;
        } else {
            mat[x][y - 1] = mat[x][y] + 1;
        }
    }
    if (mat[x + 1][y - 1] != 0 && circuit[x + 1][y - 1] != '=') { // +-
        if (circuit[x + 1][y - 1] == '~') {
            mat[x + 1][y - 1] = mat[x][y] + 2;
        } else {
            mat[x + 1][y - 1] = mat[x][y] + 1;
        }
    }
    if (mat[x - 1][y + 1] != 0 && circuit[x - 1][y + 1] != '=') { // -+
        if (circuit[x - 1][y + 1] == '~') {
            mat[x - 1][y + 1] = mat[x][y] + 2;
        } else {
            mat[x - 1][y + 1] = mat[x][y] + 1;
        }
    }
    if (mat[x][y + 1] != 0 && circuit[x][y + 1] != '=') { // =+
        if (circuit[x][y + 1] == '~') {
            mat[x][y + 1] = mat[x][y] + 2;
        } else {
            mat[x][y + 1] = mat[x][y] + 1;
        }
    }
    if (mat[x + 1][y + 1] != 0 && circuit[x + 1][y + 1] != '=') { // ++
        if (circuit[x + 1][y + 1] == '~') {
            mat[x + 1][y + 1] = mat[x][y] + 2;
        } else {
            mat[x + 1][y + 1] = mat[x][y] + 1;
        }
    }
    if (mat[x - 1][y] != 0 && circuit[x - 1][y] != '=') { //-=
        if (circuit[x - 1][y] == '~') {
            mat[x - 1][y] = mat[x][y] + 2;
        } else {
            mat[x - 1][y] = mat[x][y] + 1;
        }
    }

    if (mat[+-1][y] != 0 && circuit[x + 1][y] != '=') { // +=
        if (circuit[x + 1][y] == '~') {
            mat[x + 1][y] = mat[x][y] + 2;
        } else {
            mat[x + 1][y] = mat[x][y] + 1;
        }
    }
}

/**
 * Calculates the shorter path to the (x,y) point (actually an arrival point).
 */
void path(int x, int y, int tx, int ty) { // TIPE.
    int x1 = x;
    int y1 = y;
    int** path_matrix;
    path_matrix = malloc(sizeof (int*)*tx);
    for (int i; i < ty; i++) {
        path_matrix[i] = calloc(ty, sizeof (int));
    }
    path_matrix[x1][y1] = '=';
    if () {

    }
}

/* Pilote de base avec lecture carburant */
int main(int argn, char** argv) {
    char c;
    int i;
    FILE* info = fopen("GPdroitAuBut.log", "w"); // Pour le débuggage
    fprintf(info, " === >Carte< === \n");
    //Lecture de la carte droit au but.
    int tx, ty;
    int carburant; // carburant dans le réservoir
    int nbrBoosts = 5; // Nombre de boosts au départ
    // nbrBoosts = nbrBoosts;          // Warning "unused variable" (LIGNE A SUPPRIMER !)
    fscanf(stdin, "%d %d %d", &tx, &ty, &carburant); // Lecture taille et carburant au départ
    fprintf(info, "taille %d x %d\n", tx, ty);
    fprintf(info, "Carburant de départ %d \n\n", carburant);
    while (fread(&c, sizeof (char), 1, stdin) == 1 && c != '\n');
    for (i = 0; i < ty; i++) { // Lecture de la carte ligne par ligne
        while (fread(&c, sizeof (char), 1, stdin) == 1 && c != '\n') fprintf(info, "%c", c);
        fprintf(info, "\n");
    }
    fflush(info);
    fprintf(info, "\n === Debut Course === \n");
    int tour = 0;
    int accX = 1, accY = 0;
    int velX = 0, velY = 0;
    char action[100];
    while (!feof(stdin)) {
        tour++;
        fprintf(info, "\n === Tour %d === \n", tour);
        //Lecture des positions.
        while (fread(&c, sizeof (char), 1, stdin) == 1 && c != '\n') fprintf(info, "%c", c);
        fprintf(info, "\n === Action === \n");
        // Pas de prise en compte du sable (pas de mémorisation de la carte)
        carburant += deltaCarburantAcceleration(accX, accY, velX, velY, 0);
        velX += accX;
        velY += accY;
        //Écriture de l'accélération.
        sprintf(action, "%d %d", accX, accY);
        fprintf(stdout, "%s\n", action);
        fprintf(info, "%s (carburant restant %d)\n", action, carburant);
        fflush(stdout); // Vidage du buffer nécessaire.
        fflush(info);
    }


    return EXIT_SUCCESS;
}
