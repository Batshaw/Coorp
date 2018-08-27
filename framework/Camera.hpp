#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <glm/vec3.hpp>
#include "ray.hpp"

struct Camera
{
    std::string _name;
    float _fov_x;
    glm::vec3 _eye;
    glm::vec3 _dir;
    glm::vec3 _up;

    Camera():
        _name{"default camera"}, _fov_x{45.0f}  {}
    //Konstruktor mit Name und Öffnungswinkel: 
    Camera(std::string name_, float fov_x_):
        _name{name_}, _fov_x{fov_x_}, _eye(glm::vec3{0.0f, 0.0f, 0.0f}), _dir(glm::vec3{0.0f, 0.0f, -1.0f}), _up(glm::vec3{1.0f, 0.0f, 0.0f})  {}

    //Konstruktor für Aufgabe 7.3:
    Camera(std::string name_, float fov_x_, glm::vec3 eye_, glm::vec3 dir_, glm::vec3 up_):
        _name{name_}, _fov_x{fov_x_}, _eye{eye_}, _dir{dir_}, _up{up_}  {}

    Ray rayThroughPixel(float x, float y, float width_, float height_) const{
        glm::vec3 origin{0.0f, 0.0f, 0.0f};
        glm::vec3 direction{x-width_/2, y-height_/2, -width_/2/tan(_fov_x/2)};   //tan(Öffnungswinkel/2)=(width/2)/distance von Camera zum Bildebene.
        Ray rayCamera{origin, direction};
        return rayCamera;
    }
    

     
};

#endif 
