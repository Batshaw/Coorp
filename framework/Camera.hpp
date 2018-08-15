#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <glm/vec3.hpp>

struct Camera
{
    std::string _name;
    float _fov_x;
    glm::vec3 _eye;
    glm::vec3 _dir;
    glm::vec3 _up;
    
};

#endif  //CAMERA_HPP