#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <iostream>

struct Ray
{
    //Default Konstruktor
    Ray() : origin_{0.0f, 0.0f, 0.0f}, direction_{0.0f, 0.0f, -1.0f} {}

    //Userdefined Konsturktor
    Ray(glm::vec3 const &origin, glm::vec3 const &direction) : origin_{origin}, direction_{glm::normalize(direction)} {}

    //Kope Konstruktor
    Ray(Ray const& input) : origin_{input.origin_}, direction_{input.direction_} {}

    //Membervariable
    glm::vec3 origin_ = {0.0f, 0.0f, 0.0f};
    glm::vec3 direction_ = {0.0f, 0.0f, -1.0f};
};

#endif // RAY_HPP