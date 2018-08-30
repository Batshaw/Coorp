#ifndef RAY_HPP
#define RAY_HPP

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

struct Ray
{
    glm::vec3 origin = {0.0f, 0.0f, 0.0f};
    glm::vec3 direction = {0.0f, 0.0f, -1.0f};

    Ray() : origin{0.0f, 0.0f, 0.0f}, direction{0.0f, 0.0f, -1.0f} {}

    Ray(glm::vec3 origin_, glm::vec3 direction_) : origin{origin_}, direction{glm::normalize(direction_)} {}
};

glm::vec3 get_point(float t_, Ray const &ray)
{
    return ray.origin + ray.direction * t_;
}

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
