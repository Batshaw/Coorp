#ifndef RAY_HPP
#define RAY_HPP
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <iostream>

struct Ray
{
    glm::vec3 origin_ = {0.0f, 0.0f, 0.0f};
    glm::vec3 direction_ = {0.0f, 0.0f, -1.0f};

    Ray() : origin_{0.0f, 0.0f, 0.0f}, direction_{0.0f, 0.0f, -1.0f} {}

    Ray(glm::vec3 origin, glm::vec3 direction) : origin_{origin}, direction_{glm::normalize(direction)} {}
};

Ray transformRay(glm::mat4 const& mat, Ray const& ray)
{
    glm::vec4 o{ray.origin_, 1.0f};    //Punkte
    glm::vec4 d{ray.direction_, 0.0f}; //Vector

    //Tranformierte
    glm::vec4 a{mat * o};
    glm::vec4 b{mat * d};

    glm::vec3 origin{a.x, a.y, a.z};
    glm::vec3 direction{b.x, b.y, b.z};

    return Ray{origin, direction};
}

#endif // RAY_HPP