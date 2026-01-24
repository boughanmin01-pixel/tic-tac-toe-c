#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variables globales
int score = 0;
int meilleur_score = 0;

// Fonctions de base
void afficher_regles() {
    printf("\n--- RÈGLES DU JEU ---\n");
    printf("1. Répondez correctement aux questions\n");
    printf("2. Chaque bonne réponse rapporte 100 000 $\n");
    printf("3. Objectif : Atteindre 1 million de dollars\n");
}

void afficher_score() {
    printf("\nVotre score actuel : %d $\n", score);
    printf("Meilleur score : %d $\n", meilleur_score);
}

// Fonction pour poser une question
int poser_question(char *question, char *option1, char *option2, char *option3, char *option4, int reponse_correcte) {
    printf("\n%s\n", question);
    printf("1. %s\n", option1);
    printf("2. %s\n", option2);
    printf("3. %s\n", option3);
    printf("4. %s\n", option4);

    int reponse_utilisateur;
    printf("Votre réponse (1-4) : ");
    scanf("%d", &reponse_utilisateur);

    if (reponse_utilisateur == reponse_correcte) {
        printf("Correct ! Vous gagnez 100 000 $\n");
        score += 100000;
        return 1;
    } else {
        printf("Incorrect. La bonne réponse était %d.\n", reponse_correcte);
        return 0;
    }
}

// Tour d'échauffement
int tour_echauffement() {
    printf("\n--- TOUR D'ÉCHAUFFEMENT ---\n");

    int bonnes_reponses = 0;

    // Question 1 : Géographie tunisienne
    if (poser_question(
        "Quelle est la capitale de la Tunisie ?",
        "Sfax", "Sousse", "Tunis", "Bizerte",
        3)) {
        bonnes_reponses++;
    }

    // Question 2 : Histoire tunisienne
    if (poser_question(
        "En quelle année la Tunisie a-t-elle obtenu son indépendance ?",
        "1952", "1956", "1960", "1963",
        2)) {
        bonnes_reponses++;
    }

    // Question 3 : Culture tunisienne
    if (poser_question(
        "Quel plat traditionnel tunisien est à base de pâtes ?",
        "Tajine", "Couscous", "Makroudh", "Vermicelle",
        3)) {
        bonnes_reponses++;
    }

    return (bonnes_reponses >= 2);
}

// Tour principal
int tour_principal() {
    printf("\n--- TOUR PRINCIPAL ---\n");

    while (score < 1000000) {
        // Question 1 : Politique tunisienne
        if (!poser_question(
            "Qui est considéré comme le premier président de la Tunisie moderne ?",
            "Zine El Abidine Ben Ali", "Habib Bourguiba", "Kais Saied", "Mohamed Moncef Marzouki",
            2)) {
            return 0;
        }

        // Question 2 : Économie
        if (!poser_question(
            "Quelle est la principale ressource économique de la Tunisie ?",
            "Pétrole", "Gaz naturel", "Tourisme", "Agriculture",
            3)) {
            return 0;
        }

        // Question 3 : Patrimoine
        if (!poser_question(
            "Quel site archéologique important se trouve près de Tunis ?",
            "Petra", "Carthage", "Thugga", "Dougga",
            2)) {
            return 0;
        }

        // Question 4 : Culture
        if (!poser_question(
            "Quel instrument de musique traditionnel est originaire de Tunisie ?",
            "Oud", "Piano", "Guitare", "Violon",
            1)) {
            return 0;
        }

        // Mettre à jour le meilleur score
        if (score > meilleur_score) {
            meilleur_score = score;
        }
    }

    return 1;
}

// Fonction principale
int main() {
    char rejouer;

    do {
        // Réinitialiser le score
        score = 0;

        // Afficher les règles
        afficher_regles();

        // Tour d'échauffement
        if (tour_echauffement()) {
            printf("Bravo ! Vous passez au tour principal.\n");

            // Tour principal
            if (tour_principal()) {
                printf("\nFÉLICITATIONS ! Vous avez gagné 1 million de dollars !\n");
            } else {
                printf("\nDésolé, vous avez perdu. Votre score final : %d $\n", score);
            }
        } else {
            printf("\nVous n'avez pas réussi le tour d'échauffement.\n");
        }

        // Afficher le score final
        afficher_score();

        // Demander de rejouer
        printf("\nVoulez-vous rejouer ? (O/N) : ");
        scanf(" %c", &rejouer);
    } while (rejouer == 'O' || rejouer == 'o');

    printf("Merci d'avoir joué !\n");
    return 0;
}
