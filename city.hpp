#ifndef CITY_H
#define CITY_H

#include <cmath>
#include <stdexcept>

class City
{
public:
    /** City index. */
    unsigned long index;
    /** Coordinate of the city on the x axis. */
    unsigned long xCord;
    /** Coordinate of the city on the y axis. */
    unsigned long yCord;
    /** Sum of profit (value) of all items that belongs to this city. */
    unsigned long long totalProfit;
    /** Sum of weight of all itens that belongs to this city. */
    unsigned long long totalWeight;
    /** Ratio between the total profit ({ @link totalProfit }) of the city
     * and his total weight ({ @link totalWeight }). */
    float pwRatio;

    /**
     * @brief City  Constructor that initializes all variables with the \c 0 value.
     */
    City();

    /**
     * @brief euclDistTo    Calculate the Euclidean distance from this
     *                      city to the city passed as a parameter.
     *
     * @param dst           Destiny city.
     *
     * @return              Distance from this city to \ref dst city.
     */
    float euclDistTo( City& dst );

    /**
     * @brief calcPwRatio   Calculate the ratio between the \ref totalProfit and
     *                      \ref totalWeight. If \ref totalWeight is equal to 0,
     *                      than a std::overflow_error exception will be throwed.
     */
    void  calcPwRatio();
};

#endif // CITY_H
