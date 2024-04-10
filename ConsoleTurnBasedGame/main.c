#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "engine.h"
#include "../utils_lib/utils.h"

int main(int argc, char **argv) 
{
    int running;

    // Define each base item
    Item broadsword;
    Item longsword;
    Item health_potion;
    Item dagger;
    Item grenade;
    Item cocaine;
    Item suspistol;

    // Set item id's
    broadsword.id = 1;
    longsword.id = 2;
    health_potion.id = 3;
    dagger.id = 4;
    grenade.id = 5;
    cocaine.id = 6;
    suspistol.id = 7;

    // Set the name of each item
    strcpy(broadsword.name, "Broadsword");
    strcpy(longsword.name, "Longsword");
    strcpy(health_potion.name, "Health Potion");
    strcpy(dagger.name, "Dagger");
    strcpy(grenade.name, "Grenade");
    strcpy(cocaine.name, "White Powder");
    strcpy(suspistol.name, "Walther PPK 7.65");

    // Set the type of each item
    broadsword.type = longsword.type = dagger.type = grenade.type = 'W'; // Weapon
    health_potion.type = cocaine.type = suspistol.type = 'S'; // Support

    // Set the final item stats
    cocaine.healthDiff = 15; // Health +
    health_potion.healthDiff = 25;

    broadsword.healthDiff = -15; // Health -
    longsword.healthDiff = -25;
    dagger.healthDiff = -10;
    grenade.healthDiff = -30;
    suspistol.healthDiff = -999;

    cocaine.consumable = health_potion.consumable = grenade.consumable = 1;
    broadsword.consumable = longsword.consumable = dagger.consumable = suspistol.consumable = 0;

    // Define each base class
    Class blackman;
    Class vietcong;
    Class mexican;
    Class austrian_painter;

    // Set the Class stats
    strcpy(blackman.name, "Literal Blackman");
    blackman.healthModifier = 1.2f;
    blackman.inv[0] = longsword;
    blackman.inv[1] = grenade;
    blackman.inv[2] = grenade;
    blackman.inv[3] = grenade;
    blackman.inv[4] = grenade;
    blackman.inv[5] = grenade;
    blackman.inv[6] = grenade;
    blackman.inv[7] = health_potion;
    
    strcpy(vietcong.name, "Vietcong Soldier");
    vietcong.healthModifier = 0.9f;
    vietcong.inv[0] = broadsword;
    vietcong.inv[1] = dagger;
    vietcong.inv[2] = grenade;
    vietcong.inv[3] = grenade;
    vietcong.inv[4] = health_potion;
    vietcong.inv[5] = health_potion;
    vietcong.inv[6] = health_potion;
    vietcong.inv[7] = health_potion;

    strcpy(mexican.name, "Mexican Druggy"); 
    mexican.healthModifier = 0.8f;
    mexican.inv[0] = dagger;
    mexican.inv[1] = grenade;
    mexican.inv[2] = grenade;
    mexican.inv[3] = cocaine;
    mexican.inv[4] = cocaine;
    mexican.inv[5] = cocaine;
    mexican.inv[6] = cocaine;
    mexican.inv[7] = cocaine;
    
    strcpy(austrian_painter.name, "An Austrian Painter");
    austrian_painter.healthModifier = 1.0f;
    austrian_painter.inv[0] = dagger;
    austrian_painter.inv[1] = suspistol;
    austrian_painter.inv[2] = grenade;
    austrian_painter.inv[3] = grenade;
    austrian_painter.inv[4] = grenade;
    austrian_painter.inv[5] = health_potion;
    austrian_painter.inv[6] = health_potion;
    austrian_painter.inv[7] = health_potion;

    Player player1;
    Player player2;

    // Array of all the classes
    Class *classes[CLASSCOUNT];

    classes[0] = &blackman;
    classes[1] = &vietcong;
    classes[2] = &mexican;
    classes[3] = &austrian_painter;
	// add "white" class

    Response res = Setup(&player1, &player2, classes);

    switch (res.ret)
    {
    case -1:
        printf("\n%s", res.message);
        pauseEnter();
        
        return -1;
        // break;
    default:
        pauseEnter();
        clrscr();

        running = 1;
        Engine(running, player1, player2, classes);
        break;
    }

    return 0;
}
