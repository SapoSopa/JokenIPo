#ifndef ITEMS_H
#define ITEMS_H

typedef struct M_Player ArenaPlayer;
typedef struct M_Enemy ArenaEnemy;

typedef struct M_Item Item;
typedef enum M_ItemID ItemID;

enum M_ItemID {
    NoneItem,
    AnotherItem
    //Player Items
    //Enemy Items
    //Ambient Items
    //Common Items
    //Special Items
};

struct M_Item {
    int id;
    int cooldown;
    int (*Effect)(ArenaPlayer *player, ArenaEnemy *enemy);
};

Item* getItem(ItemID id);

#endif