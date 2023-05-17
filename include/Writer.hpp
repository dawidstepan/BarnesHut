#ifndef GROUPMPROJECT_WRITER_HPP
#define GROUPMPROJECT_WRITER_HPP

#include <vector>
#include "Body.hpp"

/**
 * \brief responsible for writing data from memory to output file
 *
 * needs to be initialized with pointer to \code stateOfBodiesOverTime \endcode
 * similar to \code InputHandler \endcode
 * \todo implement writeDataToDisc()
 */
class Writer {
public:
    Writer (std::vector<std::vector<Body>>* stateOfBodiesOverTime) : stateOfBodiesOverTime(stateOfBodiesOverTime){};
    void writeDataToDisc();
private:
    std::vector<std::vector<Body>>* stateOfBodiesOverTime;
};


#endif //GROUPMPROJECT_WRITER_HPP
