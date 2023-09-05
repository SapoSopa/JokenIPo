#ifndef ITEMS_H
#define ITEMS_H

typedef struct M_Item Item;

struct M_Item {
    int id;
    int cooldown;
    int (*Effect)(Player *player, Player *enemy);
};

#endif