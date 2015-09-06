#ifndef ITEM_H
#define ITEM_H


class Item
{
public:
    /** Profit (value) of the item. */
    unsigned long profit;
    /** Weight of the item */
    unsigned long weight;
    /** Index of the city that this item belongs. */
    unsigned long cityIndex;

    /**
     * @brief Item  Constructor that initializes all variables
     *              with the \c 0 value.
     */
    Item();
};

#endif // ITEM_H
