#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#include <vector>
#include <string>

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
     *                      is worse than the fitness of {@ref i}.
     */
    virtual bool operator < ( const Individual< T >& i ) const ;
    /**
     * @brief operator <=   Used to know if this individual is
     *                      worse or equal than the individual {@ref i}.
     *
     * @param i             Individual that will be compared to this.
     *
     * @return              \c true if the fitness of this individual
     *                      is worse or equal than the fitness of {@ref i}.
     */
    virtual bool operator <= ( const Individual< T >& i ) const ;
    /**
     * @brief operator >=   Used to know if this individual is
     *                      better or equal than the individual {@ref i}.
     *
     * @param i             Individual that will be compared to this.
     *
     * @return              \c true if the fitness of this individual
     *                      is better or equal than the fitness of {@ref i}.
     */
    virtual bool operator >= ( const Individual< T >& i ) const ;
    /**
     * @brief operator >    Used to know if this individual is
     *                      better than the individual {@ref i}.
     *
     * @param i             Individual that will be compared to this.
     *
     * @return              \c true if the fitness of this individual
     *                      is better than the fitness of {@ref i}.
     */
    virtual bool operator > ( const Individual< T >& i ) const ;
    /**
     * @brief toString      Convert the individual into a textual
     *                      representation.
     *
     * @return              String that represents the individual.
     */
    virtual std::string toString() const = 0;
};


template< class T >
Individual< T >::Individual() : fitness( 0.0 ) {}

template< class T >
Individual< T >::~Individual() {}

template< class T >
bool Individual< T >::operator < ( const Individual< T >& i ) const
{
    return this->fitness < i.fitness;
}

template< class T >
bool Individual< T >::operator <= ( const Individual< T >& i ) const
{
    return this->fitness <= i.fitness;
}

template< class T >
bool Individual< T >::operator > ( const Individual< T >& i ) const
{
    return this->fitness > i.fitness;
}

template< class T >
bool Individual< T >::operator >= ( const Individual< T >& i ) const
{
    return this->fitness >= i.fitness;
}


#endif // INDIVIDUAL_HPP
