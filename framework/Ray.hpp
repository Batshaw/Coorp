#ifndef RAY_HPP
#define RAY_HPP 

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

struct Ray
{
    glm::vec3 origin = {0.0f, 0.0f, 0.0f};
    glm::vec3 direction = {0.0f, 0.0f, -1.0f};

    Ray():
        origin{0.0f, 0.0f, 0.0f}, direction{0.0f, 0.0f, -1.0f}  {}

    Ray(glm::vec3 origin_, glm::vec3 direction_):
        origin{origin_}, direction{glm::normalize(direction_)}  {}

    glm::vec3 get_point(float t_) const{
        return origin + direction*t_;
    }


};


#endif
