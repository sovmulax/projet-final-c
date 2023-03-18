#include "./sql/sqlite3.h"
// #include "./functions/header/header.c"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char choix[100];
    char nom[100];
    char prenom[100];
    char livre[100];
    char auteur[100];
    int boo = 1;

    while (boo == 1)
    {
        printf("\e[1;1H\e[2J");
        printf("📖 Menu : \n");
        printf("1️⃣ - Ajout d'adherent : \n");
        printf("2️⃣ - Liste des adherents : \n");
        printf("3️⃣ - Ajout de livre : \n");
        printf("4️⃣ - Liste des livres : \n");
        printf("5️⃣ - Emprunté un livre : \n");
        printf("6️⃣ - Retourné un livre : \n");
        printf("7️⃣ - Les emprunts en cour: \n");
        printf("➡️ ");
        scanf("%s", choix);

        switch (atoi(choix))
        {
        case 1:
            printf("\e[1;1H\e[2J");
            printf("Le nom de l'adhérent\n");
            printf("➡️ ");
            scanf("%s", nom);
            printf("Le prenom de l'adhérent\n");
            printf("➡️ ");
            scanf("%s", prenom);

            
            break;
        }
        printf("\e[1;1H\e[2J");
        printf(" ⏳ Voulez-vous continuer ? (0 ou 1) \n");
        printf("➡️ ");
        scanf("%d", &boo);

        if (boo == 0)
        {
            return 0;
        }
    }
    return (0);
}