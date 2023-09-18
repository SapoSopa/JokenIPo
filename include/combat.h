#ifndef COMBAT_H
#define COMBAT_H

/*
// maybe the wheel options be
*/

/* #define Rock 0
#define Fire 1
#define Scissors 2
#define Human 3
#define Sponge 4
#define Paper 5
#define Air 6
#define Water 7
#define Gun 8 */

typedef enum Choice {
    Rock,
    Fire,
    Scissors,
    Human,
    Sponge,
    Paper,
    Air,
    Water,
    Gun,
    NoneChoice = -1
} Choice;



/*
////////////////////////////
*/


typedef struct WheelOption WheelOption;
typedef struct CombatWheel CombatWheel;

struct WheelOption
{
    int id;
    char name[50];
    int sprite;
    int isActivated;
    int inFreezeCooldown;
};

struct CombatWheel
{
    WheelOption options[9];
};

void CombatWheelConstructor(CombatWheel *combatWheel);

#endif