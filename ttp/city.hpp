#ifndef CITY_HPP
#define CITY_HPP

#include <cmath>        // std::pow(), std::sqrt()
#include <stdexcept>
#include <string>

class City
{
public:
    /** City index. */
    unsigned long index;
    /** Coordinate of the city on the x axis. */
    double xCord;
    /** Coordinate of the city on the y axis. */
    double yCord;
    /** Sum of profit (value) of all items that belongs to this city. */
    unsigned long long totalProfit;
    /** Sum of weight of all items that belongs to this city. */
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
    double euclDistTo( const City& dst );
    /**
     * @brief calcPwRatio   Calculate the ratio between the \ref totalProfit and
     *                      \ref totalWeight. If \ref totalWeight is equal to 0,
     *                      than a std::overflow_error exception will be thrown.
     */
    void  calcPwRatio();
};

#endif // CITY_HPP
