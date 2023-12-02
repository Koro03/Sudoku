/**
* \file sudoku.c
* \brief Programme de résolution de sudoku.
* \author Benjamin Fauchet
* \date 29/11/2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
*
* \def TAILLE 
*
* \brief constante pour la Taille d'une ligne ou d'une colonne.
*
*/

#define TAILLE 9

/**
*
* \typedef t_grille
*
* \brief type tableau de TAILLE ligne et colonne
*
* Le type t_grille sert de tableaux à double dimension qui stocke 
* les chiffres du sudoku
*
*/

typedef int t_grille[TAILLE][TAILLE];

/*****************************************************
*             déclaration des prototypes             *
******************************************************/

/**
* \fn void affichageGrille(t_grille grille)
* 
* \brief Affiche la grille du sudoku.
* \details Affiche la grille du sudoku avec une mise en forme.
* 
* \param grille La grille du sudoku.
*/
void affichageGrille(t_grille grille);

/**
* \fn void saisir(int *nb_A_Rentrer)
* 
* \brief Saisit une valeur entière.
* \details Demande à l'utilisateur de saisir une valeur entière.
* 
* \param nb_A_Rentrer Pointeur vers la variable où stocker la valeur.
*/
void saisir(int *nb_A_Rentrer);

/**
* \fn void chargerGrille(t_grille grille)
* 
* \brief Charge une grille de sudoku depuis un fichier binaire.
* \details Demande le nom du fichier à charger et lit la grille depuis ce fichier.
* 
* \param grille La grille du sudoku.
*/
void chargerGrille(t_grille grille);

/**
* \fn bool possible(t_grille grille, int numLignes, int numColonne, int valeur)
* 
* \brief Vérifie si une valeur peut être placée dans une case donnée.
* \details Vérifie si la valeur peut être placée dans la ligne, la colonne 
* et le carré 3x3 correspondant à la case spécifiée.
* 
* \param grille La grille du sudoku.
* \param numLignes L'indice de la ligne.
* \param numColonne L'indice de la colonne.
* \param valeur La valeur à placer.
* \return true si la valeur peut être placée, false sinon.
*/
bool possible(t_grille grille, int numLignes, int numColonne, int valeur);

/**
* \fn bool finPart(t_grille grille)
* 
* \brief Vérifie si la grille est complète.
* \details Parcourt la grille pour déterminer si elle est complète, c'est-à-dire
* s'il n'y a plus de cases vides (contenant 0).
* 
* \param grille La grille du sudoku.
* \return true si la grille est complète, false sinon.
*/
bool finPart(t_grille grille);

/*****************************************************
*             Programme principal                    *
******************************************************/

/**
* 
* \brief Programme principal pour jouer au sudoku.
* \details Charge une grille de sudoku, permet à l'utilisateur de la compléter
* en respectant les règles, et affiche un message lorsque la partie est gagnée.
* 
* \return 0 en cas de succès.
*/

int main() {
    bool valPossible, fin = false;
    t_grille grille;
    int numLignes, numColonne, valeur;

    chargerGrille(grille);
    while (fin == false) {
        affichageGrille(grille);
        printf("Quelle indices ? (Rentrer d'abord la ligne, puis la colonne)\n");
        saisir(&numLignes);
        numLignes = numLignes - 1;
        saisir(&numColonne);
        numColonne = numColonne - 1;

        if (grille[numLignes][numColonne] != 0) {
            printf("La case n'est pas vide !!!!\n");
        } else {
            printf("Valeur à insérer\n");
            saisir(&valeur);
            valPossible = possible(grille, numLignes, numColonne, valeur);
            if (valPossible == true) {
                grille[numLignes][numColonne] = valeur;
            }
            fin = finPart(grille);
        }
    }
    printf("Partie gagnée !\n");

    return 0;
}

/*****************************************************
*             Procédures et fonctions                 *
******************************************************/

/**
* \brief Affiche la grille du sudoku.
* \details Affiche la grille du sudoku avec une mise en forme.
* 
* \param grille La grille du sudoku.
*/
void affichageGrille(t_grille grille) {
    int i, j, compteur1, compteur2 = 1;
    printf("  ");
    for (compteur1 = 1; compteur1 < TAILLE + 1; compteur1++) {
        printf("%3d", compteur1);
        if (compteur1 == 6 || compteur1 == 3) {
            printf(" ");
        }
    }
    printf("\n  +---------+---------+---------+\n");
    for (i = 0; i < TAILLE; i++) {
        printf("%d |", compteur2);
        for (j = 0; j < TAILLE; j++) {
            if (grille[i][j] == 0) {
                printf(" . ");
            } else {
                printf("%2d ", grille[i][j]);
            }
            if (j == 2 || j == 5) {
                printf("|");
            }
        }
        printf("|\n");
        compteur2++;
        if (compteur2 == 4 || compteur2 == 7) {
            printf("  +---------+---------+---------+\n");
        }
    }
    printf("  +---------+---------+---------+\n");
}

/**
* \brief Charge une grille de sudoku depuis un fichier binaire.
* \details Demande le nom du fichier à charger et lit la grille depuis ce fichier.
* 
* \param grille La grille du sudoku.
*/
void chargerGrille(t_grille g) {
    char nomFichier[30];
    FILE *f;
    printf("Nom du fichier ?\n");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");

    if (f == NULL) {
        printf("\nERREUR sur le fichier %s\n", nomFichier);
    } else {
        fread(g, sizeof(int), TAILLE * TAILLE, f);
    }
    fclose(f);
}

/**
* \brief Vérifie si la grille est complète.
* \details Parcourt la grille pour déterminer si elle est complète, c'est-à-dire
* s'il n'y a plus de cases vides (contenant 0).
* 
* \param grille La grille du sudoku.
* \return true si la grille est complète, false sinon.
*/
bool finPart(t_grille grille) {
    int i = 0, j = 0;
    bool pasPresent = true;
    while (i < TAILLE && j < TAILLE && pasPresent == true) {
        if (grille[i][j] == 0) {
            pasPresent = false;
        }

        j++;

        if (j == TAILLE) {
            i++;
            j = 0;
        }
    }
    return pasPresent;
}

/**
* \brief Saisit une valeur entière.
* \details Demande à l'utilisateur de saisir une valeur entière.
* 
* \param nb_A_Rentrer Pointeur vers la variable où stocker la valeur.
*/
void saisir(int *nb_A_Rentrer) {
    char ch[30];
    bool conversion = false;
    do {
        printf("Quelle valeur à rentrer?\n");
        scanf("%s", ch);
        if (sscanf(ch, "%d", nb_A_Rentrer) != 0) {
            if (*nb_A_Rentrer <= 9 && *nb_A_Rentrer >= 1) {
                printf("La conversion a réussi, x contient la %d\n", *nb_A_Rentrer);
                conversion = true;
            }
        } else {
            printf("La conversion en entier a échoué\n");
        }
    } while (conversion == false);
}

/**
* \brief Vérifie si une valeur peut être placée dans une case donnée.
* \details Vérifie si la valeur peut être placée dans la ligne, la colonne 
* et le carré 3x3 correspondant à la case spécifiée.
* 
* \param grille La grille du sudoku.
* \param numLignes L'indice de la ligne.
* \param numColonne L'indice de la colonne.
* \param valeur La valeur à placer.
* \return true si la valeur peut être placée, false sinon.
*/
bool possible(t_grille grille, int numLignes, int numColonne, int valeur) {
    int i, j, coinLigne, coinColonne;
    bool possible = true;
    for (j = 0; j < TAILLE; j++) {
        if (grille[numLignes][j] == valeur && j != numColonne) {
            printf("Valeur impossible à placer, elle est déjà présente sur la ligne.\n");
            possible = false;
        }
    }
    j = numColonne;
    i = 0;
    for (i = 0; i < TAILLE; i++) {
        if (grille[i][numColonne] == valeur && i != numLignes) {
            printf("Valeur impossible à placer, elle est déjà présente sur la colonne.\n");
            possible = false;
        }
    }
    coinLigne = (numLignes / 3) * 3;
    coinColonne = (numColonne / 3) * 3;

    for (int i = coinLigne; i < coinLigne + 3; i++) {
        for (int j = coinColonne; j < coinColonne + 3; j++) {
            if (grille[i][j] == valeur && (i != numLignes || j != numColonne)) {
                printf("Valeur impossible à placer, elle est déjà présente dans le carré 3x3.\n");
                possible = false;
            }
        }
    }

    return possible;
}
