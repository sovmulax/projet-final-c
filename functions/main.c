#include "./sql/sqlite3.h"
#include "./header/header.c"
#include <stdio.h>
#include <stdlib.h>

/// @brief
/// @param argc
/// @param argv
/// @return
int main(int argc, char *argv[])
{
    char choix[100];
    int boo = 1;
    sqlite3 *db;
    sqlite3 *db2;

    char v1[100];
    char v2[100];
    char v3[100];
    char v4[100];
    char v5[100];
    int v6 = 1;
    int v7 = 1;

    while (boo == 1)
    {
        //printf("\e[1;1H\e[2J");
        printf("📖 Menu : \n");
        printf("1️⃣ - Création d'evenement : \n");
        printf("2️⃣ - Liste des evenements : \n");
        printf("3️⃣ - Achat de billets: \n");
        printf("4️⃣ - Création de Seances (Cinéma) : \n");
        printf("5️⃣ - Liste de Séances du jour: \n");
        printf("6️⃣ - Les statistiques : \n");
        
        // printf("6️⃣ - Retourné un livre : \n");
        // printf("7️⃣ - Les emprunts en cour: \n");
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
            printf("🧾 Création du Menu\n");
            printf("Liste des éléments (element;element;element)\n");
            printf("➡️ ");
            scanf("%s", v5);
            add_event(db, v1, v2, v3, v4, v5);

            break;

        case 2:
            printf("\e[1;1H\e[2J");
            event_list(db, "*");
            break;

        case 3:
            printf("\e[1;1H\e[2J");
            printf("Le type d'evenement (1 ou 2 ou 3)\n");
            printf("1- Anniversaire\n");
            printf("2- Mariage\n");
            printf("3- Cinéma\n");
            printf("➡️ ");
            scanf("%d", &v6);
            printf("\e[1;1H\e[2J");

            if (v6 != 3)
            {
                event_list(db, "*");
                printf("L'Id de l'evenement\n");
                printf("➡️ ");
                scanf("%d", &v7);
                achat_billet(db2, v7, 0);
                break;
            }
            else
            {
                liste_seance(db2);
                printf("L'Id de l'evenement\n");
                printf("➡️ ");
                scanf("%d", &v7);
                achat_billet(db2, 0, v7);
                break;
            }
        case 4:
            printf("\e[1;1H\e[2J");
            printf("Le nom du film\n");
            printf("➡️ ");
            scanf("%s", v1);
            printf("Le nombre de place\n");
            printf("➡️ ");
            scanf("%d", &v7);
            ajout_seance(db, v1, v7);
            break;

        case 5:
            printf("\e[1;1H\e[2J");
            liste_seance(db);
            break;
        case 6:
            stats();
            break;
        }

        // printf("\e[1;1H\e[2J");
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