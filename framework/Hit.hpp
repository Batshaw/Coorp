#ifndef HIT_HPP
#define HIT_HPP
#include <glm/vec3.hpp>

struct Hit{

    Hit():
        hit_{false}, distance_{10000.0f}, normalVector_{}, schnittPunkt_{}  {}

    Hit(bool hit, float distance, glm::vec3 normalVector, glm::vec3 schnittPunkt):
        hit_{hit}, distance_{distance}, normalVector_{normalVector}, schnittPunkt_{schnittPunkt}   {}
         
    bool hit_;
    float distance_;
    // Shape closestShape_;
    glm::vec3 normalVector_;
    glm::vec3 schnittPunkt_;
};

#endif  // HIT_HPP