#ifndef HIT_HPP
#define HIT_HPP

#include <glm/vec3.hpp>

class Shape;

struct Hit{

    Hit():
        hit_{false}, distance_{10000.0f}, closestShape_{nullptr}, normalVector_{}, schnittPunkt_{}  {}

    Hit(Hit const &input):
        hit_{input.hit_}, distance_{input.distance_}, closestShape_{input.closestShape_}, normalVector_{input.normalVector_}, schnittPunkt_{input.schnittPunkt_}   {}


    Hit(bool hit, float distance, Shape const *closestShape, glm::vec3 normalVector, glm::vec3 schnittPunkt):
        hit_{hit}, distance_{distance},closestShape_{closestShape}, normalVector_{normalVector}, schnittPunkt_{schnittPunkt}   {}
         
    bool hit_;
    float distance_;
    Shape const *closestShape_;
    glm::vec3 normalVector_;
    glm::vec3 schnittPunkt_;
};

#endif  // HIT_HPP