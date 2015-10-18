#ifndef FEATURES_HPP
#define FEATURES_HPP

#include <string>

class Features
{
public:
    /**
     * @brief Features  Constructor.
     */
    Features();
    /**
     * @brief ~Features  Destructor.
     */
    virtual ~Features();
    /**
     * @brief toString  Used to get a \c string representation of the features.
     *
     * @return          a \c string representation of the features.
     */
    virtual std::string toString() const = 0;
};

#endif // FEATURES_HPP
