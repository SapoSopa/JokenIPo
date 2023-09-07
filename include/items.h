#ifndef ITEMS_H
#define ITEMS_H

typedef struct Player Player;
typedef struct Enemy Enemy;

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
    int (*Effect)(Player *player, Enemy *enemy);
};

Item* getItem(ItemID id);

#endif