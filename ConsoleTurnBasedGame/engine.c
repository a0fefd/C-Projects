#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "data.h"
#include "_err.h"
#include "../conio/conio.h"
#include "../utils_lib/utils.h"

Item VOID;
Item *VOIDptr = &VOID;

void initializeInv(Item inv[8])
{
    for (int i = 0; i < 8; i++)
    {
        inv[i] = *VOIDptr;
    }
}

int findItemIndex(Item inv[8], Item target)
{
    char **itemNames = malloc( 8 * sizeof( char* ) );
    for (int i = 0; i < 8; i++) { itemNames[i] = inv[i].name; }
    
    int index = findIndexString(itemNames, target.name);
    
    free(itemNames);
    return index;
}

void getInv(Item inv[8], Player p1, Player p2, int turn)
{
    initializeInv(inv);
    for (int i = 0; i < 8; i++)
    {
        inv[i] = (turn) ? (p1.playerClass->inv[i]) : (p2.playerClass->inv[i]);
    }
}

// void sortInv(Item inv[8])
// {
//     Item tmpItem;
//     for (int i = 0; i < 7; i++)
//     {
//         if ((inv[i].type == 'W' && inv[i+1].type == 'S') || 
//             (inv[i].type == 'W' && inv[i+1].type == 'V') ||
//             (inv[i].type == 'S' && inv[i+1].type == 'V')  ) 
//         {
//             tmpItem = inv[i];
//             inv[i] = inv[i + 1];
//             inv[i + 1] = tmpItem;
//         }
//     }
// }

void copyInv(Item dest[8], Item src[8])
{
    initializeInv(dest);
    memcpy(dest, src, 8 * sizeof(Item) );
}

void removeItemInv(Item inv[8], int index)
{
    int voidIndex = findItemIndex(inv, *VOIDptr);
    if (voidIndex == -1) { voidIndex = 8; }
    for (int i = index; i < voidIndex-1; i++)
    {
        inv[i] = inv[i + 1];
    }
    inv[voidIndex-1] = *VOIDptr;
}

Response Setup(Player *player1, Player *player2, Class *classes[CLASSCOUNT])
{
    Response res;
    memset(res.message, '\0', sizeof(res.message));
    res.ret = 0;

    _err_init();
    Error *errors = getErrors();
    Error _err_ClassNum = errors[0];

    strcpy( VOIDptr->name, " ");
    VOIDptr->type = 'V';
    VOIDptr->healthDiff = 0;
    VOIDptr->consumable = 0;

    char *scan1 = malloc( 8 * sizeof(char) );
    char *scan2 = malloc( 8 * sizeof(char) );

    clrscr();

    printf("Classes:\n");
    for (int i = 1; i < 5; i++)
    {
        printf("%d. %s\n", i, classes[i-1]->name);
    }
    printf("\n");

    printf("Enter P1 Class: "); fgets(scan1, sizeof(scan1), stdin);
    printf("Enter P2 Class: "); fgets(scan2, sizeof(scan2), stdin);

    if (atoi(scan1) <= 0 || atoi(scan1) > 4 ||
        atoi(scan2) <= 0 || atoi(scan2) > 4 )
    {
        free(scan1); free(scan2);

        strcpy(res.message, "Error: ");
        strcat(res.message, _err_ClassNum.cause);
        strcat(res.message, "\n");
        strcat(res.message, _err_ClassNum.message);

        res.ret = _err_ClassNum._return;
        return res;
    }

    player1->playerClass = classes[atoi(scan1)-1];
    player1->health = 100 * player1->playerClass->healthModifier;
    player1->maxHealth = player1->health;
    player1->identifier = 1;
    player1->isTurn = 1;
    player1->type = 'H';

    player2->playerClass = classes[atoi(scan2)-1];
    player2->health = 100 * player2->playerClass->healthModifier;
    player2->maxHealth = player2->health;
    player2->identifier = 2;
    player2->isTurn = 0;
    player2->type = 'H';

    free(scan1); free(scan2);

    printf(
        "\nPlayer 1\nClass: %s\nHealth: %d\nID: %d\nTurn?: %d\nType: %c\n",
        player1->playerClass->name,
        player1->health,
        player1->identifier,
        player1->isTurn,
        player1->type
    );
    printf(
        "\nPlayer 2\nClass: %s\nHealth: %d\nID: %d\nTurn?: %d\nType: %c\n",
        player2->playerClass->name,
        player2->health,
        player2->identifier,
        player2->isTurn,
        player2->type
    );

    pauseEnter();
    clrscr();

    // free(player1); free(player2);

    return res;
}

int useItems(Item inv[8], Player *p1, Player *p2, char itemType, int *option)
{
    Item tmpInv[8]; initializeInv(tmpInv);
    Item tmpInv2[8]; initializeInv(tmpInv2);

    getInv(tmpInv, *p1, *p2, p1->isTurn);

    int itemCount = 0;
    for (int i = 0; i < 8; i++)
    {
        if (tmpInv[i].type == itemType)
        {
            tmpInv2[itemCount] = tmpInv[i];
            itemCount++;
        }
    }
    for (int i = 0; i < itemCount; i++)
    {
        printf("%d. %s\n", i+1, tmpInv2[i].name);
    }

    char key = c_getch(); 
    
    clrscr(); 
    int selectionIndex = atoi( &key ); 
    if (selectionIndex < 1 || selectionIndex > itemCount) 
    {
        *option = 0;
        return 0;
    }

    if ( (selectionIndex > 0) && (itemCount >= selectionIndex) )
    {
        int healed = (itemType == 'S') ? (1) : (0);

        char *playerA = malloc(9 * sizeof(char));
        char *playerB = malloc(9 * sizeof(char));
        char *item = malloc(20 * sizeof(char));
        char *type = malloc(7 * sizeof(char));
        int healthChange = tmpInv2[selectionIndex-1].healthDiff;
        int finalHealth = 0;

        strcpy(item, tmpInv2[selectionIndex-1].name);

        clrscr();

        if (p1->isTurn && healed)
        {
            strcpy(playerA, "Player 1");
            strcpy(playerB, playerA);
            strcpy(type, "healed");
            finalHealth = p1->health + healthChange;
            if (finalHealth > p1->maxHealth) { finalHealth = p1->maxHealth; }
            p1->health = finalHealth;
        } else if (p1->isTurn && !healed)
        {
            strcpy(playerA, "Player 1");
            strcpy(playerB, "Player 2");
            strcpy(type, "taken");
            finalHealth = p2->health + healthChange;
            if (finalHealth > p2->maxHealth) { finalHealth = p2->maxHealth; }
            p2->health = finalHealth;
        } else if (p2->isTurn && healed)
        {
            strcpy(playerA, "Player 2");
            strcpy(playerB, playerA);
            strcpy(type, "healed");
            finalHealth = p2->health + healthChange;
            if (finalHealth > p2->maxHealth) { finalHealth = p2->maxHealth; }
            p2->health = finalHealth;
        } else if (p2->isTurn && !healed)
        {
            strcpy(playerA, "Player 2");
            strcpy(playerB, "Player 1");
            strcpy(type, "taken");
            finalHealth = p1->health + healthChange;
            if (finalHealth > p1->maxHealth) { finalHealth = p1->maxHealth; }
            p1->health = finalHealth;
        }

        if (finalHealth < 0) { finalHealth = 0; }

        if (healed && tmpInv2[selectionIndex-1].healthDiff < 0)
        {
            strcpy(type, "taken");
        }

        printf("%s used %s. %s has %s %d and is now on %d", playerA, item, playerB, type, abs(healthChange), finalHealth);

        pauseEnter();
    } else {
        // Implement Error maybe
        *option = 0;
        return 0;
    }

    int index = findItemIndex(tmpInv, tmpInv2[selectionIndex-1]);
    if (inv[index].consumable) { removeItemInv(inv, index); }

    copyInv( inv, tmpInv );

    *option = 0;
    clrscr();
    return 0;
}

// Command Line User Interface
int CLUI(Player *p1, Player *p2, int *option, int *running)
{
    int check;
    Item inv[8];

    if (p1->health <= 0 || p2->health <= 0)
    {
        clrscr();

        check = (p1->health <= 0);
        (check) ? ( printf("Player 1 has Died\n") ) : ( printf("Player 2 has Died\n") );

        *running = 0;
        return 0;
    }


    check = (p1->isTurn);
    switch (*option)
    {
        case KEY_0:
            *option = 0;
            clrscr();
            break;

        case KEY_1:
            getInv(inv, *p1, *p2, check);

            for (int i = 0; i < 8; i++)
            {
                printf("%s\n", inv[i].name);
            }
            printf("\n0 to Exit.\n");
            *option = c_getch();
            return 0;

        case KEY_2:
            useItems(inv, p1, p2, 'W', option);
            (check) ? (copyInv( p1->playerClass->inv, inv )) : (copyInv( p2->playerClass->inv, inv ));
            return 1;

        case KEY_3:
            useItems(inv, p1, p2, 'S', option);
            (check) ? (copyInv( p1->playerClass->inv, inv )) : (copyInv( p2->playerClass->inv, inv ));
            return 0;

        case 0:
            clrscr();
            if (check)
            {
                printf("----- Player 1 ------ \n");
                printf("Health: %d\n", p1->health);
            } else {
                printf("----- Player 2 ----- \n");
                printf("Health: %d\n", p2->health);
            }
            printf("1. Inventory\n");
            printf("2. Attack\n");
            printf("3. Support\n");
            *option = c_getch();
            clrscr();
            return 0;
    }
    return 0;
}

int Engine(int running, Player player1, Player player2, Class *classes[CLASSCOUNT])
{
    int option = 0; int check;

    Player *pointerP1 = &player1;
    Player *pointerP2 = &player2;

    clrscr();
    // Main loop
    while (running)
    {
        // sortInv(pointerP1->playerClass->inv);
        // sortInv(pointerP2->playerClass->inv);

        check = CLUI(pointerP1, pointerP2, &option, &running);
        (check) ? ( invert(&player1.isTurn) ) : NONE;
        (check) ? ( invert(&player2.isTurn) ) : NONE;
        check = 0;
    }

    return 0;
}
