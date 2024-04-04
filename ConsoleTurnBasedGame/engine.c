#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "data.h"
#include "_err.h"
#include "../conio/conio.h"
#include "../utils_lib/utils.h"

Item VOID;

void getInv(Item *inv, Player p1, Player p2, int turn)
{
    for (int i = 0; i < 8; i++)
    {
        if (p1.isTurn)
        {
            inv[i] = p1.playerClass->inv[i];
        } else {
            inv[i] = p2.playerClass->inv[i];
        }
    }
}

void sortInv(Item *inv)
{
    Item temp;
    for (int i = 0; i < 8; i++)
    {
        if ( i && ( (inv[i].type == 'W' && inv[i-1].type == 'S') || (inv[i].type == 'S' && inv[i-1].type == 'V') ) )
        {
            temp = inv[i-1];
            inv[i-1] = inv[i];
            inv[i] = temp;
        }
    }
}

void copyInv(Item *dest, Item *src)
{
    for (int i = 0; i < 8; i++)
    {
        dest[i] = src[i];
    }
}

void removeItemInv(Item *inv, int index)
{
    for (int i = index; i < 8 - 1 /* 8 is inventory size */; i++)
    {
        inv[i] = inv[i + 1];
    }
}

Response Setup(Player *player1, Player *player2, Class *classes[CLASSCOUNT])
{
    Response res;
    memset(res.message, '\0', sizeof(res.message));
    res.ret = 0;

    _err_init();
    Error *errors = getErrors();
    Error _err_ClassNum = errors[0];

    strcpy(VOID.name, " ");
    (&VOID)->type = 'V';
    (&VOID)->healthDiff = 0;
    (&VOID)->consumable = 0;

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
    player1->identifier = 1;
    player1->isTurn = 1;
    player1->type = 'H';

    player2->playerClass = classes[atoi(scan2)-1];
    player2->health = 100 * player2->playerClass->healthModifier;
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

    printf("\nPress Enter to continue. ");
    for (int ch; ( ch = getchar() ); ) 
    {
        if (ch) { break; }
    }

    clrscr();

    // free(player1); free(player2);

    return res;
}

// Command Line User Interface
int CLUI(Player *p1, Player *p2, int *option, int *running)
{
    Item inv[8]; 

    if (p1->health <= 0 || p2->health <= 0)
    {
        clrscr();
        
        int check = (p1->health <= 0);
        (check) ? ( printf("Player 1 has Died\n") ) : ( printf("Player 2 has Died\n") );

        *running = 0;
        return 0;
    }

    switch (*option)
    {
        case KEY_0:
            *option = 0; 
            clrscr();
            break;
        
        case KEY_1:
            getInv(inv, *p1, *p2, p1->isTurn);

            for (int i = 0; i < 8; i++)
            {
                printf("%s\n", inv[i].name);
            }
            printf("\n0 to Exit.\n");
            *option = c_getch();
            return 0;
        
        case KEY_2:
            getInv(inv, *p1, *p2, p1->isTurn);
            
            Item weaponInv[8]; 
            // memset(weaponInv, 0, sizeof(weaponInv));

            int weaponCount = 0;
            for (int i = 0; i < 8; i++)
            {
                if (inv[i].type == 'W')
                {
                    weaponInv[weaponCount] = inv[i];
                    weaponCount++;
                }
            }
            for (int i = 0; i < weaponCount; i++)
            {
                printf("%d. %s\n", i+1, weaponInv[i].name);
            }

            int key = c_getch(); int wp = atoi( (char*) &key );
            if ( (wp > 0) && (weaponCount > wp) )
            {
                (p1->isTurn) ? (p2->health += weaponInv[wp-1].healthDiff) : (p1->health += weaponInv[wp-1].healthDiff);
            } else {
                // Implement Error maybe
                *option = 0;
                return 0;
            }

            char **itemNames = malloc( 8 * sizeof( char* ) );
            for (int i = 0; i < 8; i++) { itemNames[i] = inv[i].name; }
            int index = findIndexString(itemNames, weaponInv[wp-1].name);
            free(itemNames);

            (inv[index].consumable) ? ( removeItemInv(inv, index) ) : NONE;

            (p1->isTurn) ? ( copyInv( p1->playerClass->inv, inv ) ) : ( copyInv( p2->playerClass->inv, inv ));

            *option = 0;
            clrscr();
            return 1;

        case 0:
            if (p1->isTurn) 
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

    sortInv(pointerP1->playerClass->inv);
    sortInv(pointerP2->playerClass->inv);

    clrscr();
    // Main loop
    while (running)
    {
        check = CLUI(pointerP1, pointerP2, &option, &running);
        (check) ? ( invert(&player1.isTurn) ) : NONE; 
        (check) ? ( invert(&player2.isTurn) ) : NONE; 
        
    }

    return 0;
}