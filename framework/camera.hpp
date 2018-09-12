#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include "ray.hpp"

#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>


struct Camera
{
    std::string name_;
    float fov_x_;
    glm::vec3 eye_;
    glm::vec3 dir_;
    glm::vec3 up_;

    glm::mat4 world_transformation_;

    glm::mat4 world_transformation_inv_;

    Camera() : name_{"default camera"},
               fov_x_{45},
               eye_{0.0f, 0.0f, 0.0f},
               dir_{0.0f, 0.0f, -1.0f},
               up_{0.0f, 1.0f, 0.0f},
               world_transformation_{1.0f},
               world_transformation_inv_{glm::inverse(world_transformation_)} {}

    //Konstruktor mit Name und Öffnungswinkel:
    Camera(std::string const &name, float fov_x) : name_{name},
                                                   fov_x_{fov_x},
                                                   eye_{0.0f, 0.0f, 0.0f},
                                                   dir_{0.0f, 0.0f, -1.0f},
                                                   up_{0.0f, 1.0f, 0.0f},
                                                   world_transformation_{1.0f},
                                                   world_transformation_inv_{glm::inverse(world_transformation_)} {}

    //Konstruktor für Aufgabe 7.3:
    Camera(std::string const &name, float fov_x, glm::vec3 const &eye, glm::vec3 const &dir, glm::vec3 const &up, glm::mat4 const &world_transformation) : name_{name},
                                                                                                                                                           fov_x_{fov_x},
                                                                                                                                                           eye_{eye},
                                                                                                                                                           dir_{dir},
                                                                                                                                                           up_{up},
                                                                                                                                                           world_transformation_{world_transformation},
                                                                                                                                                           world_transformation_inv_{glm::inverse(world_transformation)} {}
};


#endif
