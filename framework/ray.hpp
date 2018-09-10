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

    Ray(glm::vec3 const& origin, glm::vec3 const& direction) : origin_{origin}, direction_{glm::normalize(direction)} {}
};


#endif // RAY_HPP