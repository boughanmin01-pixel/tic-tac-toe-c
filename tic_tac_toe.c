#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h> // Pour les fonctions de manipulation de la console

// Structure pour représenter les coordonnées dans la console
COORD coord = {0, 0};

// Fonction pour positionner le curseur à des coordonnées spécifiques dans la console
void gotoxy(int x, int y);

// Fonction pour changer la couleur du texte dans la console
void set_color(int color);

// Définitions de quelques couleurs
#define COULEUR_BLANC         7
#define COULEUR_BLEU          1
#define COULEUR_VERT          2
#define COULEUR_ROUGE         4
#define COULEUR_JAUNE         6

// Tableau pour représenter les 9 cases du plateau de jeu
char plateau[10];

// Variables pour stocker les scores des joueurs X et O
int score_X = 0;
int score_O = 0;

// Nom du fichier pour stocker les scores
const char *nom_fichier_scores = "scores.txt";

// Fonction pour charger les scores depuis un fichier avec gestion d'erreurs
void charger_scores();

// Fonction pour sauvegarder les scores dans le fichier avec gestion d'erreurs
void sauvegarder_scores();

// Fonction pour initialiser le plateau de jeu
void initialiser_plateau();

// Fonction pour afficher le plateau de jeu avec des couleurs
void afficher_plateau();

// Fonction pour vérifier si un joueur a gagné
int verifier_gagnant(char joueur);

// Fonction qui gère le déroulement d'une partie
void jouer_partie();
int main();
// Fonction pour positionner le curseur à des coordonnées spécifiques dans la console
void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Fonction pour changer la couleur du texte dans la console
void set_color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Fonction pour charger les scores depuis un fichier avec gestion d'erreurs
void charger_scores() {
    FILE *fichier = fopen(nom_fichier_scores, "r");
    if (fichier != NULL) {
        if (fscanf(fichier, "%d %d", &score_X, &score_O) != 2) {
            printf("Erreur lors de la lecture des scores depuis le fichier. Les scores seront initialisés à 0.\n");
            score_X = 0;
            score_O = 0;
        }
        fclose(fichier);
    } else {
        printf("Fichier de scores '%s' introuvable. Les scores seront initialisés à 0.\n", nom_fichier_scores);
        score_X = 0;
        score_O = 0;
    }
}

// Fonction pour sauvegarder les scores dans le fichier avec gestion d'erreurs
void sauvegarder_scores() {
    FILE *fichier = fopen(nom_fichier_scores, "w");
    if (fichier != NULL) {
        if (fprintf(fichier, "%d %d", score_X, score_O) < 0) {
            printf("Erreur lors de l'écriture des scores dans le fichier '%s'.\n", nom_fichier_scores);
        }
        fclose(fichier);
    } else {
        printf("Erreur lors de l'ouverture du fichier '%s' pour la sauvegarde des scores.\n", nom_fichier_scores);
    }
}

// Fonction pour initialiser le plateau de jeu
void initialiser_plateau() {
    for (int i = 1; i <= 9; i++) {
        plateau[i] = '0' + i;
    }
}

// Fonction pour afficher le plateau de jeu avec des couleurs
void afficher_plateau() {
    system("cls");
    gotoxy(10, 2);
    set_color(COULEUR_JAUNE); // Titre en jaune
    printf("MORPION - Tic Tac Toe");
    set_color(COULEUR_BLANC); // Réinitialiser la couleur

    gotoxy(10, 4);
    printf("  ");
    set_color(plateau[1] == 'X' ? COULEUR_BLEU : (plateau[1] == 'O' ? COULEUR_VERT : COULEUR_BLANC));
    printf("%c", plateau[1]);
    set_color(COULEUR_BLANC);
    printf(" | ");
    set_color(plateau[2] == 'X' ? COULEUR_BLEU : (plateau[2] == 'O' ? COULEUR_VERT : COULEUR_BLANC));
    printf("%c", plateau[2]);
    set_color(COULEUR_BLANC);
    printf(" | ");
    set_color(plateau[3] == 'X' ? COULEUR_BLEU : (plateau[3] == 'O' ? COULEUR_VERT : COULEUR_BLANC));
    printf("%c", plateau[3]);
    printf("  ");

    gotoxy(10, 5);
    printf(" ---|---|---");

    gotoxy(10, 6);
    printf("  ");
    set_color(plateau[4] == 'X' ? COULEUR_BLEU : (plateau[4] == 'O' ? COULEUR_VERT : COULEUR_BLANC));
    printf("%c", plateau[4]);
    set_color(COULEUR_BLANC);
    printf(" | ");
    set_color(plateau[5] == 'X' ? COULEUR_BLEU : (plateau[5] == 'O' ? COULEUR_VERT : COULEUR_BLANC));
    printf("%c", plateau[5]);
    set_color(COULEUR_BLANC);
    printf(" | ");
    set_color(plateau[6] == 'X' ? COULEUR_BLEU : (plateau[6] == 'O' ? COULEUR_VERT : COULEUR_BLANC));
    printf("%c", plateau[6]);
    printf("  ");

    gotoxy(10, 7);
    printf(" ---|---|---");

    gotoxy(10, 8);
    printf("  ");
    set_color(plateau[7] == 'X' ? COULEUR_BLEU : (plateau[7] == 'O' ? COULEUR_VERT : COULEUR_BLANC));
    printf("%c", plateau[7]);
    set_color(COULEUR_BLANC);
    printf(" | ");
    set_color(plateau[8] == 'X' ? COULEUR_BLEU : (plateau[8] == 'O' ? COULEUR_VERT : COULEUR_BLANC));
    printf("%c", plateau[8]);
    set_color(COULEUR_BLANC);
    printf(" | ");
    set_color(plateau[9] == 'X' ? COULEUR_BLEU : (plateau[9] == 'O' ? COULEUR_VERT : COULEUR_BLANC));
    printf("%c", plateau[9]);
    printf("  ");
}

// Fonction pour vérifier si un joueur a gagné
int verifier_gagnant(char joueur) {
    if ((plateau[1] == joueur && plateau[2] == joueur && plateau[3] == joueur) ||
        (plateau[4] == joueur && plateau[5] == joueur && plateau[6] == joueur) ||
        (plateau[7] == joueur && plateau[8] == joueur && plateau[9] == joueur) ||
        (plateau[1] == joueur && plateau[4] == joueur && plateau[7] == joueur) ||
        (plateau[2] == joueur && plateau[5] == joueur && plateau[8] == joueur) ||
        (plateau[3] == joueur && plateau[6] == joueur && plateau[9] == joueur) ||
        (plateau[1] == joueur && plateau[5] == joueur && plateau[9] == joueur) ||
        (plateau[3] == joueur && plateau[5] == joueur && plateau[7] == joueur)) {

        if (joueur == 'X') {
            score_X++;
        } else {
            score_O++;
        }
        return 1;
    }
    return 0;
}

// Fonction qui gère le déroulement d'une partie
void jouer_partie() {
    int tour = 1;
    int choix;
    char joueur = 'X';

    initialiser_plateau();

    while (tour <= 9) {
        afficher_plateau();
        gotoxy(5, 10);
        printf("Tour %d - Joueur ", tour);
        set_color(joueur == 'X' ? COULEUR_BLEU : COULEUR_VERT);
        printf("%c", joueur);
        set_color(COULEUR_BLANC);
        printf(", entrez un numero de case (1-9) : ");

        if (scanf("%d", &choix) != 1) {
            // Erreur de saisie (l'utilisateur n'a pas entré un nombre entier)
            gotoxy(5, 12);
            set_color(COULEUR_ROUGE);
            printf("Erreur : Entrée invalide. Veuillez entrer un nombre entre 1 et 9.");
            set_color(COULEUR_BLANC);
            // Nettoyer le tampon d'entrée pour éviter une boucle infinie
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            gotoxy(5, 13);
            printf("Appuyez sur une touche pour réessayer...");
            getch();
            gotoxy(5, 12);
            printf("                                                                 ");
            gotoxy(5, 13);
            printf("                                    ");
            continue;
        }

        if (choix < 1 || choix > 9 || plateau[choix] == 'X' || plateau[choix] == 'O') {
            gotoxy(5, 12);
            set_color(COULEUR_ROUGE);
            printf("Case invalide. Veuillez entrer un numéro de case libre entre 1 et 9.");
            set_color(COULEUR_BLANC);
            gotoxy(5, 13);
            printf("Appuyez sur une touche pour réessayer...");
            getch();
            gotoxy(5, 12);
            printf("                                                                        ");
            gotoxy(5, 13);
            printf("                                    ");
            continue;
        }

        plateau[choix] = joueur;

        if (verifier_gagnant(joueur)) {
            afficher_plateau();
            gotoxy(5, 12);
            set_color(joueur == 'X' ? COULEUR_BLEU : COULEUR_VERT);
            printf("==> Le joueur %c a gagné cette partie !", joueur);
            set_color(COULEUR_BLANC);
            break;
        }

        joueur = (joueur == 'X') ? 'O' : 'X';
        tour++;
    }

    if (tour > 9) {
        afficher_plateau();
        gotoxy(5, 12);
        set_color(COULEUR_JAUNE);
        printf("==> Match nul !");
        set_color(COULEUR_BLANC);
    }

    gotoxy(5, 14);
    printf("Score actuel :");
    gotoxy(5, 15);
    set_color(COULEUR_BLEU);
    printf("Joueur X : %d", score_X);
    gotoxy(5, 16);
    set_color(COULEUR_VERT);
    printf("Joueur O : %d", score_O);
    set_color(COULEUR_BLANC);

    sauvegarder_scores();
    gotoxy(0, 18);
}

// Fonction principale du programme
int main() {
    char choix;

    charger_scores();

    system("cls");
    gotoxy(5, 2);
    set_color(COULEUR_JAUNE);
    printf("=== Bienvenue dans le jeu du Morpion ===");
    set_color(COULEUR_BLANC);
    gotoxy(5, 4);
    printf("Scores précédents :");
    gotoxy(5, 5);
    set_color(COULEUR_BLEU);
    printf("Joueur X : %d", score_X);
    gotoxy(5, 6);
    set_color(COULEUR_VERT);
    printf("Joueur O : %d", score_O);
    set_color(COULEUR_BLANC);
    gotoxy(0, 8);

    do {
        jouer_partie();

        gotoxy(5, 20);
        printf("Voulez-vous rejouer ? (O/N) : ");
        choix = getch();
        printf("%c", choix);
        printf("\n");
        gotoxy(0, 22);
    } while (choix == 'O' || choix == 'o');

    gotoxy(5, 24);
    printf("Merci d'avoir joué !");
    gotoxy(0, 25);
    return 0;
}
