#include "include/items.h"
#include "include/combat.h"
#include "include/enemy.h"
#include "include/arena.h"

#include "raylib.h"

int ArenaConstructor(Arena *arena, ArenaPlayer *player, ArenaEnemy *enemy) {
    arena->round = 0;
    arena->roundMax = 10;

    arena->player = player;
    arena->enemy = enemy;

    arena->playerSelectedOption = NoneChoice;
    arena->enemySelectedOption = NoneChoice;

    arena->playerItemCooldown = 0;
    arena->enemyItemCooldown = 0;

    return 0;
}

int PlayerConstructor(ArenaPlayer *player) {
    player->life = PLAYER_MAX_LIFE;
    player->maxLife = PLAYER_MAX_LIFE;

    for (int i = 0; i < MAX_INV_SIZE; i++) {
        player->inventory[i] = NoneItem;
    }

    CombatWheelConstructor(&player->MyCombatWheel);

    for (int i = 0; i < 9; i++) {
        (*player).MyCombatWheel.options[i].isActivated = 1;
    }   

    return 0;
}

int nextRound(Arena *arena) {
    arena->round++;

    arena->playerSelectedOption = NoneChoice;
    arena->enemySelectedOption = NoneChoice;

    arena->UsedPlayerItemIdx = NoneItem;
    arena->UsedEnemyItemIdx = NoneItem;

    if (arena->playerItemCooldown > 0) {
        arena->playerItemCooldown--;
    }
    if (arena->enemyItemCooldown > 0) {
        arena->enemyItemCooldown--;
    }
    
    return 0;
}

int UpdateArena(Arena *arena, int *result, int *roundResult) {
    // bot choose action
    selectEnemyAction(arena, EnemyChooseAction(arena->enemy));        

    // item use 
    if (arena->UsedPlayerItemIdx != NoneItem && arena->playerItemCooldown <= 0)
        doPlayerItemAction(arena);

    if (arena->UsedEnemyItemIdx != NoneItem && arena->enemyItemCooldown <= 0)
        doEnemyItemAction(arena);


    // adjust life to max life if over
    if ((arena->player)->life >= (arena->player)->maxLife) 
        (arena->player)->life = (arena->player)->maxLife;
    
    if ((arena->enemy)->life >= (arena->enemy)->maxLife) 
        (arena->enemy)->life = (arena->enemy)->maxLife;
    

    // check if someone died
    if ((arena->player)->life <= 0) {
        (*result) = 2;
        return 0;
        //GameOver();
    }

    if ((arena->enemy)->life <= 0) {
        (*result) = 1;
        return 0;
        //NextMap();
    }

    if (arena->round >= arena->roundMax) {
        arena->round = 0;
        //check who has more life
        //NextMap();
    }

    if (arena->playerSelectedOption != NoneChoice && 
        arena->enemySelectedOption != NoneChoice) 
    {
        printf("enemy choice: %d\n", arena->enemySelectedOption);

        doCombat(arena, roundResult);
        nextRound(arena);
    }

    return 0;
}

////////////////////////////////////////////////////////////

int selectPlayerAction(Arena *arena, Choice playerChoice) {
    if (arena->playerSelectedOption == NoneChoice) {
        arena->playerSelectedOption = playerChoice;
        return 0;
    } else {
        return 1;
    }
}

int selectEnemyAction(Arena *arena, Choice enemyChoice) {
    if (arena->enemySelectedOption) {
        arena->enemySelectedOption = enemyChoice;
        return 0;
    } else {
        return 1;
    }
}


int selectPlayerItem(Arena *arena, int ItemInvIdx) {
    if (arena->playerSelectedOption == NoneChoice) {
        arena->UsedPlayerItemIdx = ItemInvIdx;
        return 0;
    } else {
        return 1;
    }
}

int selectEnemyItem(Arena *arena, int ItemInvIdx) {
    if (arena->enemySelectedOption == NoneChoice) {
        arena->UsedEnemyItemIdx = ItemInvIdx;
        return 0;
    } else {
        return 1;
    }
}

////////////////////////////////////////////////////////////

int doPlayerItemAction(Arena *arena) {
    int itemInvIdx = arena->UsedPlayerItemIdx;
    ItemID ChoiceItemID = (arena->player)->inventory[itemInvIdx];

    arena->playerItemCooldown = getItem(ChoiceItemID)->cooldown;
    
    if (getItem(ChoiceItemID)->Effect(arena->player, arena->enemy)){
        //remove item from inventory and organize it

        (arena->player)->inventory[itemInvIdx] = NoneItem;
        for (int i = itemInvIdx; (arena->player)->inventory[i + 1] != NoneItem && i < MAX_INV_SIZE; i++) {
            (arena->player)->inventory[i] = (arena->player)->inventory[i+1];
        }
    }
    return 0;
}

int doEnemyItemAction(Arena *arena) {
    int itemInvIdx = arena->UsedEnemyItemIdx;
    ItemID ChoiceItemID = (arena->enemy)->inventory[itemInvIdx];

    arena->enemyItemCooldown = getItem(ChoiceItemID)->cooldown;
    if (getItem(ChoiceItemID)->Effect(arena->player, arena->enemy)){
        //remove item from inventory and organize it

        (arena->enemy)->inventory[itemInvIdx] = NoneItem;
        for (int i = itemInvIdx; (arena->enemy)->inventory[i + 1] != NoneItem && i < MAX_INV_SIZE; i++) {
            (arena->enemy)->inventory[i] = (arena->enemy)->inventory[i+1];
        }
    }
    return 0;
}

int doCombat(Arena *arena, int *result) {
    Choice playerChoice = arena->playerSelectedOption;
    Choice enemyChoice = arena->enemySelectedOption;

    int winner = 0; // 0 -> draw
                    // 1 -> player win
                    // 2 -> enemy win
                    
    for (int i = 1; i <= 4; i++) {
        if ((playerChoice + i) % 8 == enemyChoice) {
            winner = 1;
            break;
        } else if ((enemyChoice + i) % 8 == playerChoice) {
            winner = 2;
            break;
        }
    }

    if (winner == 1) {
        printf("player win\n");
        (arena->enemy)->life -= MIN_DMG;
    } 
    else if (winner == 2) {
        printf("enemy win\n");
        (arena->player)->life -= MIN_DMG;
    }

    (*result) = winner;

    return 0;
}