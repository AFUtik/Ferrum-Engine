#ifndef INSTANCEBUFFER_HPP
#define INSTANCEBUFFER_HPP

#include <vector>
#include "glm/glm.hpp"

class InstanceBuffer {
public:
    std::vector<glm::mat4> mats;

    inline size_t getInstancesCount() {return mats.size();};
};

#endif