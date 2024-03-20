#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "data.h"

void clrscr()
{
    // #if _WIN64 
    //     system("cls");
    // #elif _WIN32
    //     system("cls");
    // #else
    //     system("clear");
    // #endif
    
    printf("\e[1;1H\e[2J");
}

Response Setup(Player *player1, Player *player2, Class classes[])
{
    Response res;
    memset(res.message, '\0', sizeof(res.message));
    res.ret = 0;

    char *scan1 = malloc( 8 * sizeof(char) ); 
    char *scan2 = malloc( 8 * sizeof(char) );
    
    clrscr();

    printf("Classes:\n");
    for (int i = 1; i < 5; i++) 
    {
        printf("%d. %s\n", i, classes[i-1].name);
    }
    printf("\n");

    printf("Enter P1 Class: "); fgets(scan1, sizeof(scan1), stdin);
    printf("Enter P2 Class: "); fgets(scan2, sizeof(scan2), stdin);

    if (atoi(scan1) <= 0 || atoi(scan1) > 4 || 
        atoi(scan2) <= 0 || atoi(scan2) > 4 ) 
    {
        free(scan1); free(scan2);

        strcpy(res.message, "Error: Class selection unsuccessful;\nError: A proper class number is required.");
        res.ret = -1;
        return res;
    }

    player1->playerClass = classes[atoi(scan1)-1];
    player1->health = 100 * player1->playerClass.healthModifier;
    player1->identifier = 1;
    player1->isTurn = 1;
    player1->type = 'H';

    player2->playerClass = classes[atoi(scan2)-1];
    player2->health = 100 * player2->playerClass.healthModifier;
    player2->identifier = 2;
    player2->isTurn = 0;
    player2->type = 'H';

    free(scan1); free(scan2);

    printf(
        "\nPlayer 1\nClass: %s\nHealth: %d\nID: %d\nTurn?: %d\nType: %c\n",
        player1->playerClass.name,
        player1->health,
        player1->identifier,
        player1->isTurn,
        player1->type
    );
    printf(
        "\nPlayer 2\nClass: %s\nHealth: %d\nID: %d\nTurn?: %d\nType: %c\n",
        player2->playerClass.name,
        player2->health,
        player2->identifier,
        player2->isTurn,
        player2->type
    );

    printf("\nPress Enter to continue. ");
    for (int ch; ( ch = getchar() ); ) 
    {
        if (ch) { break; }
    }

    clrscr();

    // free(player1); free(player2);

    return res;
}

int turnCheck(Player p1) 
{
    switch (p1.isTurn)
    {
    case 1:
        return 1;

    default:
        return 2;
    }
}

// Command Line User Interface
void CLUI(Player p1, Player p2) 
{
    if (p1.isTurn) 
    {
        printf("----- Player 1 ------ \n");
        printf("Health: %d\n", p1.health);
        printf("--------------------\n");
    } else {
        printf("----- Player 2 ----- \n");
        printf("Health: %d\n", p2.health);
        printf("--------------------\n");
    }
}

int Engine(int running, Player player1, Player player2, Class classes[]) 
{
    int option;

    // Main loop
    while (running)
    {
        clrscr();
        CLUI(player1, player2);
        option = fgetc(stdin);
    }

    return 0;
}