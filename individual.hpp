#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#include <vector>
#include <string>

#include "individual.cpp"

template< class T >
class Individual
{
public:
    /** Features of the individual. */
    T features;
    /** His fitness. */
    double fitness;

    /**
     * @brief Individual    Constructor
     */
    Individual();
    /**
     * @brief ~Individual    Destructor
     */
    virtual ~Individual();
    /**
     * @brief operator <    Used to know if this individual is
     *                      worse than the individual {@ref i}.
     *
     * @param i             Individual that will be compared to this.
     *
     * @return              \c true if the fitness of this individual
     *                      is less than the fitness of {@ref i}.
     */
    virtual bool operator < ( const Individual< T >& i );
    /**
     * @brief operator <    Used to know if this individual is
     *                      worse or equal than the individual {@ref i}.
     *
     * @param i             Individual that will be compared to this.
     *
     * @return              \c true if the fitness of this individual
     *                      is less or equal than the fitness of {@ref i}.
     */
    virtual bool operator <= ( const Individual< T >& i );
    /**
     * @brief operator <    Used to know if this individual is
     *                      better or equal than the individual {@ref i}.
     *
     * @param i             Individual that will be compared to this.
     *
     * @return              \c true if the fitness of this individual
     *                      is greater or equal than the fitness of {@ref i}.
     */
    virtual bool operator >= ( const Individual< T >& i );
    /**
     * @brief operator <    Used to know if this individual is
     *                      better than the individual {@ref i}.
     *
     * @param i             Individual that will be compared to this.
     *
     * @return              \c true if the fitness of this individual
     *                      is greater than the fitness of {@ref i}.
     */
    virtual bool operator > ( const Individual< T >& i );
    /**
     * @brief toString      Convert the individual into a textual
     *                      representation.
     *
     * @return              String that represents the individual.
     */
    virtual std::string toString() = 0;
};

#endif // INDIVIDUAL_HPP
