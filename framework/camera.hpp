#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <glm/vec3.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#include "ray.hpp"

struct Camera
{
    std::string name_;
    float fov_x_;
    glm::vec3 eye_;
    glm::vec3 dir_;
    glm::vec3 up_;

    glm::mat4 world_transformation_{1, 0, 0, 0,
                                    0, 1, 0, 0,
                                    0, 0, 1, 0,
                                    0, 0, 0, 1};
                                    
    glm::mat4 world_transformation_inv_{glm::inverse(world_transformation_)};

    Camera() : name_{"default camera"},
               fov_x_{45},
               eye_{0.0f, 0.0f, 0.0f},
               dir_{0.0f, 0.0f, -1.0f},
               up_{0.0f, 1.0f, 0.0f},
               world_transformation_{},
               world_transformation_inv_{glm::inverse(world_transformation_)} {}

    //Konstruktor mit Name und Öffnungswinkel:
    Camera(std::string const &name, float fov_x) : name_{name},
                                                   fov_x_{fov_x},
                                                   eye_{0.0f, 0.0f, 0.0f},
                                                   dir_{0.0f, 0.0f, -1.0f},
                                                   up_{0.0f, 1.0f, 0.0f},
                                                   world_transformation_{},
                                                   world_transformation_inv_{glm::inverse(world_transformation_)} {}

    //Konstruktor für Aufgabe 7.3:
    Camera(std::string const &name, float fov_x, glm::vec3 const &eye, glm::vec3 const &dir, glm::vec3 const &up, glm::mat4 const &world_transformation) : name_{name},
                                                                                                                                                           fov_x_{fov_x},
                                                                                                                                                           eye_{eye},
                                                                                                                                                           dir_{dir},
                                                                                                                                                           up_{up},
                                                                                                                                                           world_transformation_{world_transformation},
                                                                                                                                                           world_transformation_inv_{glm::inverse(world_transformation)} {}

    Ray rayThroughPixel(float x, float y, float width, float height) const
    {
        glm::vec3 origin{0.0f, 0.0f, 0.0f};
        glm::vec3 direction{x - width / 2, y - height / 2, (-width / 2) / tan(fov_x_ / 2)}; //tan(Öffnungswinkel/2)=(width/2)/distance von Camera zum Bildebene.
        Ray rayCamera{origin, direction};
        return rayCamera;
    }

    void transform(glm::mat4 const &matrix)
    {
        world_transformation_ = matrix * world_transformation_;
        world_transformation_inv_ = glm::inverse(world_transformation_);
        std::cout << "This camera: " << name_ << std::endl;
        std::cout << "transform: " << std::endl;
        std::cout << glm::to_string(world_transformation_) << std::endl;
        std::cout << "inverse: " << std::endl;
        std::cout << glm::to_string(world_transformation_inv_) << std::endl;
    }
};
#endif
