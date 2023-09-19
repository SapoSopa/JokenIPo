#include "include/enemy.h"
#include "include/config.h"
#include "include/combat.h"
#include "include/items.h"

#include <stdlib.h>
#include <time.h>
#include "raylib.h"

static ArenaEnemy ArenaEnemies[ENEMY_COUNT];

static void InitEnemy(ArenaEnemy *enemy, int level)
{
    enemy->life = enemy->maxLife = PLAYER_MAX_LIFE;

}

void startEnemies() {

    ArenaEnemies[0].life = ArenaEnemies[0].maxLife = PLAYER_MAX_LIFE;
    CombatWheelConstructor(&ArenaEnemies[0].MyCombatWheel);
    ArenaEnemies[0].MyCombatWheel.options[Rock].isActivated = 1;

    ArenaEnemies[1].life = ArenaEnemies[1].maxLife = PLAYER_MAX_LIFE;
    CombatWheelConstructor(&ArenaEnemies[1].MyCombatWheel);
    ArenaEnemies[1].MyCombatWheel.options[Scissors].isActivated = 1;

    ArenaEnemies[2].life = ArenaEnemies[2].maxLife = PLAYER_MAX_LIFE;
    CombatWheelConstructor(&ArenaEnemies[2].MyCombatWheel);
    ArenaEnemies[2].MyCombatWheel.options[Paper].isActivated = 1;

    ArenaEnemies[3].life = ArenaEnemies[3].maxLife = PLAYER_MAX_LIFE;
    CombatWheelConstructor(&ArenaEnemies[3].MyCombatWheel);
    ArenaEnemies[3].MyCombatWheel.options[Paper].isActivated = 1;
    ArenaEnemies[3].MyCombatWheel.options[Water].isActivated = 1;

    ArenaEnemies[4].life = ArenaEnemies[4].maxLife = PLAYER_MAX_LIFE;
    CombatWheelConstructor(&ArenaEnemies[4].MyCombatWheel);
    ArenaEnemies[4].MyCombatWheel.options[Air].isActivated = 1;
    ArenaEnemies[4].MyCombatWheel.options[Gun].isActivated = 1;

    ArenaEnemies[5].life = ArenaEnemies[5].maxLife = PLAYER_MAX_LIFE;
    CombatWheelConstructor(&ArenaEnemies[5].MyCombatWheel);
    ArenaEnemies[5].MyCombatWheel.options[Water].isActivated = 1;
    ArenaEnemies[5].MyCombatWheel.options[Rock].isActivated = 1;

    ArenaEnemies[6].life = ArenaEnemies[6].maxLife = PLAYER_MAX_LIFE;
    CombatWheelConstructor(&ArenaEnemies[6].MyCombatWheel);
    ArenaEnemies[6].MyCombatWheel.options[Fire].isActivated = 1;
    ArenaEnemies[6].MyCombatWheel.options[Gun].isActivated = 1;

    ArenaEnemies[7].life = ArenaEnemies[7].maxLife = PLAYER_MAX_LIFE;
    CombatWheelConstructor(&ArenaEnemies[7].MyCombatWheel);
    ArenaEnemies[7].MyCombatWheel.options[Sponge].isActivated = 1;
    ArenaEnemies[7].MyCombatWheel.options[Scissors].isActivated = 1;

    ArenaEnemies[8].life = ArenaEnemies[8].maxLife = PLAYER_MAX_LIFE;
    CombatWheelConstructor(&ArenaEnemies[8].MyCombatWheel);
    ArenaEnemies[8].MyCombatWheel.options[Human].isActivated = 1;
    ArenaEnemies[8].MyCombatWheel.options[Fire].isActivated = 1;

    ArenaEnemies[9].life = ArenaEnemies[9].maxLife = PLAYER_MAX_LIFE;
    CombatWheelConstructor(&ArenaEnemies[9].MyCombatWheel);
    ArenaEnemies[9].MyCombatWheel.options[Scissors].isActivated = 1;
    ArenaEnemies[9].MyCombatWheel.options[Human].isActivated = 1;
    ArenaEnemies[9].MyCombatWheel.options[Sponge].isActivated = 1;

    ArenaEnemies[10].life = ArenaEnemies[10].maxLife = PLAYER_MAX_LIFE;
    CombatWheelConstructor(&ArenaEnemies[10].MyCombatWheel);
    ArenaEnemies[10].MyCombatWheel.options[Human].isActivated = 1;
    ArenaEnemies[10].MyCombatWheel.options[Sponge].isActivated = 1;
    ArenaEnemies[10].MyCombatWheel.options[Paper].isActivated = 1;

    ArenaEnemies[11].life = ArenaEnemies[11].maxLife = PLAYER_MAX_LIFE;
    CombatWheelConstructor(&ArenaEnemies[11].MyCombatWheel);
    ArenaEnemies[11].MyCombatWheel.options[Paper].isActivated = 1;
    ArenaEnemies[11].MyCombatWheel.options[Air].isActivated = 1;
    ArenaEnemies[11].MyCombatWheel.options[Water].isActivated = 1;

    ArenaEnemies[12].life = ArenaEnemies[12].maxLife = PLAYER_MAX_LIFE;
    CombatWheelConstructor(&ArenaEnemies[12].MyCombatWheel);
    ArenaEnemies[12].MyCombatWheel.options[Gun].isActivated = 1;
    ArenaEnemies[12].MyCombatWheel.options[Water].isActivated = 1;
    ArenaEnemies[12].MyCombatWheel.options[Rock].isActivated = 1;

    ArenaEnemies[13].life = ArenaEnemies[13].maxLife = PLAYER_MAX_LIFE;
    CombatWheelConstructor(&ArenaEnemies[13].MyCombatWheel);
    ArenaEnemies[13].MyCombatWheel.options[Sponge].isActivated = 1;
    ArenaEnemies[13].MyCombatWheel.options[Paper].isActivated = 1;
    ArenaEnemies[13].MyCombatWheel.options[Air].isActivated = 1;
    ArenaEnemies[13].MyCombatWheel.options[Water].isActivated = 1;

    ArenaEnemies[14].life = ArenaEnemies[14].maxLife = PLAYER_MAX_LIFE;
    CombatWheelConstructor(&ArenaEnemies[14].MyCombatWheel);
    ArenaEnemies[14].MyCombatWheel.options[Rock].isActivated = 1;
    ArenaEnemies[14].MyCombatWheel.options[Fire].isActivated = 1;
    ArenaEnemies[14].MyCombatWheel.options[Scissors].isActivated = 1;
    ArenaEnemies[14].MyCombatWheel.options[Human].isActivated = 1;

    ArenaEnemies[15].life = ArenaEnemies[15].maxLife = PLAYER_MAX_LIFE;
    CombatWheelConstructor(&ArenaEnemies[15].MyCombatWheel);
    ArenaEnemies[15].MyCombatWheel.options[Rock].isActivated = 1;
    ArenaEnemies[15].MyCombatWheel.options[Fire].isActivated = 1;
    ArenaEnemies[15].MyCombatWheel.options[Scissors].isActivated = 1;
    ArenaEnemies[15].MyCombatWheel.options[Human].isActivated = 1;
    ArenaEnemies[15].MyCombatWheel.options[Sponge].isActivated = 1;
    ArenaEnemies[15].MyCombatWheel.options[Paper].isActivated = 1;
    ArenaEnemies[15].MyCombatWheel.options[Air].isActivated = 1;
    ArenaEnemies[15].MyCombatWheel.options[Water].isActivated = 1;
    ArenaEnemies[15].MyCombatWheel.options[Gun].isActivated = 1;

    return;
}


int EnemyChooseAction(ArenaEnemy *enemy) {
    srand(time(NULL));
    int choices[9];
    int len = 0;

    for (int i = 0; i < 9; i++){
        if (enemy->MyCombatWheel.options[i].isActivated == 1){
            choices[len++] = i;
        }
    }

    int randomChoice;

    if (len)
        randomChoice = rand() % len;
    else 
        randomChoice = -1;

    return randomChoice;
} 