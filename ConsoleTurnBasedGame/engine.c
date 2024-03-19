#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "data.h"

void clrscr()
{
    #if _WIN64 
        system("cls");
    #elif _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int Setup(struct Player player1, struct Player player2, struct Class classes[4])
{
    char scan1[8]; char scan2[8];

    clrscr();

    printf("Classes:\n");
    for (int i = 1; i < 5; i++) {
        printf("%d. %s\n", i, classes[i-1].name);
    } printf("\n");

    printf("Enter P1 Class: "); scanf("%1s", scan1);
    printf("Enter P2 Class: "); scanf("%1s", scan2);

    player1.playerClass = classes[atoi(scan1)-1];
    player1.health = 100 * player1.playerClass.healthModifier;
    player1.identifier = 1;
    player1.isTurn = 1;
    player1.type = 'H';

    player2.playerClass = classes[atoi(scan2)-1];
    player2.health = 100 * player2.playerClass.healthModifier;
    player2.identifier = 2;
    player2.isTurn = 0;
    player2.type = 'H';

    printf(
        "\nPlayer 1\nClass: %s\nHealth: %d\nID: %d\nTurn?: %d\nType: %c\n",
        player1.playerClass.name,
        player1.health,
        player1.identifier,
        player1.isTurn,
        player1.type
    );
    printf(
        "\nPlayer 2\nClass: %s\nHealth: %d\nID: %d\nTurn?: %d\nType: %c\n",
        player2.playerClass.name,
        player2.health,
        player2.identifier,
        player2.isTurn,
        player2.type
    );

    return 0;
}

int Engine() 
{
    // Todo
    return 0;
}