#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/glm.hpp>
#include "Ray.hpp"

Ray transformRay(glm::mat4 const &mat, Ray const &ray)
{
    glm::vec4 o_{ray.origin, 1.0f};    //Punkte
    glm::vec4 d_{ray.direction, 0.0f}; //Vector

    //Tranformierte
    glm::vec3 origin_{mat * o_};
    glm::vec3 direction_{mat * d_};

    return Ray{origin_, direction_};
}

#endif
