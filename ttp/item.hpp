#ifndef ITEM_H
#define ITEM_H

#include <stdexcept>

class Item
{
public:
    /** Index of the item. */
    unsigned long index;
    /** Profit (value) of the item. */
    unsigned long profit;
    /** Weight of the item */
    unsigned long weight;
    /** Index of the city that this item belongs. */
    unsigned long cityIndex;
    /** Ratio between the profit and his weight */
    float pwRatio;

    /**
     * @brief Item  Constructor that initializes all variables
     *              with the \c 0 value.
     */
    Item();
    /**
     * @brief calcPwRatio   Calculate the ratio between the \ref profit and
     *                      \ref weight. If \ref weight is equal to 0,
     *                      than a std::overflow_error exception will be throwed.
     */
    void  calcPwRatio();
};

#endif // ITEM_H
