#include "include/combat.h"
#include "include/config.h"

#include "raylib.h"

void CombatWheelConstructor(CombatWheel *combatWheel){
    combatWheel->options[Rock] = (WheelOption){Rock, "Rock", 0, 0, 0};
    combatWheel->options[Fire] = (WheelOption){Fire, "Fire", 0, 0, 0};
    combatWheel->options[Scissors] = (WheelOption){Scissors, "Scissors", 0, 0, 0};
    combatWheel->options[Human] = (WheelOption){Human, "Human", 0, 0, 0};
    combatWheel->options[Sponge] = (WheelOption){Sponge, "Sponge", 0, 0, 0};
    combatWheel->options[Paper] = (WheelOption){Paper, "Paper", 0, 0, 0};
    combatWheel->options[Air] = (WheelOption){Air, "Air", 0, 0, 0};
    combatWheel->options[Water] = (WheelOption){Water, "Water", 0, 0, 0};
    combatWheel->options[Gun] = (WheelOption){Gun, "Gun", 0, 0, 0};
}

int CheckActiveOption(CombatWheel *CombatWheel, Choice choice) {
    return CombatWheel->options[choice].isActivated;
}