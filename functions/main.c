#include "./sql/sqlite3.h"
#include "./header/header.c"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char choix[100];
    int boo = 1;
    sqlite3 *db;

    char v1[100];
    char v2[100];
    char v3[100];
    char v4[100];

    while (boo == 1)
    {
        printf("\e[1;1H\e[2J");
        printf("📖 Menu : \n");
        printf("1️⃣ - Création d'evenement : \n");
        printf("2️⃣ - Liste des evenements : \n");
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
            printf("Le nom de l'evenement\n");
            printf("➡️ ");
            scanf("%s", v1);
            printf("La date de l'evenement (JJ/MM/AAAA)\n");
            printf("➡️ ");
            scanf("%s", v2);
            printf("Le nombre de place\n");
            printf("➡️ ");
            scanf("%s", v3);
            printf("Le type d'evenement (1 ou 2)\n");
            printf("1- Anniversaire\n");
            printf("2- Mariage\n");
            printf("➡️ ");
            scanf("%s", v4);
            printf("\e[1;1H\e[2J");
            add_event(v1, v2, v3, v4);
            printf("🧾 Création du Menu\n");
            printf("Liste des éléments (element;element;element)\n");
            printf("➡️ ");

            break;

        case 2:
            printf("\e[1;1H\e[2J");
            retrieve_data_from_event_table(db);
            break;
        }

        //printf("\e[1;1H\e[2J");
        printf(" 📌 Voulez-vous continuer ? (0 ou 1) \n");
        printf("➡️ ");
        scanf("%d", &boo);

        if (boo == 0)
        {
            return 0;
        }
    }
    return (0);
}