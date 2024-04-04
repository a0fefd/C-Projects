#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "engine.h"

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
    cocaine.healthDiff = 10; // Health +
    health_potion.healthDiff = 25;

    broadsword.healthDiff = -10; // Health -
    longsword.healthDiff = -20;
    dagger.healthDiff = -5;
    grenade.healthDiff = -15;
    suspistol.healthDiff = -999;

    cocaine.consumable = health_potion.consumable = grenade.consumable = 1;
    broadsword.consumable = longsword.consumable = dagger.consumable = suspistol.consumable = 0;

    // Define and setup the different effects
    Effect health_damage;
    Effect super_health;
    Effect super_damage;
    Effect death;

    health_damage.damageDiff = 10;
    health_damage.damageMulti = 1.2f;
    health_damage.healthDiff = 40;
    health_damage.healthMulti = 1.1f;
    
    super_health.damageDiff = 0;
    super_health.damageMulti = 0.25f;
    super_health.healthDiff = 100;
    super_health.healthMulti = 2.0f;
    
    super_damage.damageDiff = 25;
    super_damage.damageMulti = 1.75f;
    super_damage.healthDiff = -25;
    super_damage.healthMulti = 0.6f;
    
    death.damageDiff = 0;
    death.damageMulti = 0;
    death.healthDiff = -999;
    death.healthMulti = 0;


    // Define each base class and their abilities
    Class blackman;
    ClassAbility dropped_soap;

    Class vietcong;
    ClassAbility one_with_the_trees;
    
    Class mexican;
    ClassAbility coke_vacuum;

    Class austrian_painter;
    ClassAbility third_reich;

    // Setup the abilities
    strcpy(dropped_soap.name, "Make them Drop the Soap");
    strcpy(dropped_soap.message, "just dropped the soap!");
    dropped_soap.delay = 5;
    dropped_soap.effect = super_damage;

    strcpy(one_with_the_trees.name, "Become One with the Trees");
    strcpy(one_with_the_trees.message, "has fused with nature!");
    one_with_the_trees.delay = 4;
    one_with_the_trees.effect = health_damage;

    strcpy(coke_vacuum.name, "Your Nose is now a Vacuum");
    strcpy(coke_vacuum.message, "has turned their nostrils into a Coke Vacuum!");
    coke_vacuum.delay = 2;
    coke_vacuum.effect = health_damage;

    strcpy(third_reich.name, "Summon the power of the Third Reich");
    strcpy(third_reich.message, "just channelled the power of the Third Reich!");
    third_reich.delay = 6;
    third_reich.effect = super_health;



    // Set the Class stats
    strcpy(blackman.name, "Literal Blackman");
    blackman.healthModifier = 1.5f;
    blackman.ability = dropped_soap;
    blackman.inv[0] = longsword;
    blackman.inv[1] = grenade;
    blackman.inv[2] = grenade;
    blackman.inv[3] = grenade;
    blackman.inv[4] = grenade;
    blackman.inv[5] = grenade;
    blackman.inv[6] = grenade;
    blackman.inv[7] = health_potion;
    
    strcpy(vietcong.name, "Vietcong Soldier");
    vietcong.healthModifier = 0.8f;
    vietcong.ability = one_with_the_trees;
    vietcong.inv[0] = broadsword;
    vietcong.inv[1] = dagger;
    vietcong.inv[2] = grenade;
    vietcong.inv[3] = grenade;
    vietcong.inv[4] = health_potion;
    vietcong.inv[5] = health_potion;
    vietcong.inv[6] = health_potion;
    vietcong.inv[7] = health_potion;

    strcpy(mexican.name, "Mexican Druggy"); 
    mexican.healthModifier = 0.6f;
    mexican.ability = coke_vacuum;
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
    austrian_painter.ability = third_reich;
    austrian_painter.inv[0] = dagger;
    austrian_painter.inv[1] = suspistol;
    austrian_painter.inv[2] = grenade;
    austrian_painter.inv[3] = grenade;
    austrian_painter.inv[4] = grenade;
    austrian_painter.inv[5] = health_potion;
    austrian_painter.inv[6] = health_potion;
    austrian_painter.inv[7] = health_potion;

    // Define each player
    Player player1;
    Player player2;

    // Array of all the classes
    Class classes[4] = {
        blackman,
        vietcong,
        mexican,
        austrian_painter
    };
    
    Response res = Setup(&player1, &player2, classes);

    switch (res.ret)
    {
    case -1:
        printf("\n%s\n", res.message);
        return -1;
        // break;
    default:
        running = 1;
        Engine(running, player1, player2, classes);
        break;
    }

    return 0;
}
