#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <glm/vec3.hpp>
#include "Ray.hpp"

struct Camera
{
    std::string _name;
    float _fov_x;
    glm::vec3 _eye;
    glm::vec3 _dir;
    glm::vec3 _up;
    glm::mat4 _world_transformation;
    glm::mat4 _transformation_inv;

    //Default Constructor
    Camera() : _name{"default camera"},
               _fov_x{45},
               _eye{0.0f, 0.0f, 0.0f},
               _dir{0.0f, 0.0f, -1.0f},
               _up{0.0f, 1.0f, 0.0f},
               _world_transformation{},
               _transformation_inv{glm::inverse(_world_transformation)} {}

    //Konstruktor mit Name und Öffnungswinkel:
    Camera(std::string name_, float fov_x_) : _name{name_},
                                              _fov_x{fov_x_},
                                              _eye{0.0f, 0.0f, 0.0f},
                                              _dir{0.0f, 0.0f, -1.0f},
                                              _up{0.0f, 1.0f, 0.0f},
                                              _world_transformation{},
                                              _transformation_inv{glm::inverse(_world_transformation)} {}

    //Konstruktor für Aufgabe 7.3:
    Camera(std::string name_, float fov_x_, glm::vec3 eye_, glm::vec3 dir_, glm::vec3 up_, glm::mat4 world_transformation_) : _name{name_},
                                                                                                                              _fov_x{fov_x_},
                                                                                                                              _eye{eye_},
                                                                                                                              _dir{dir_},
                                                                                                                              _up{up_},
                                                                                                                              _world_transformation{world_transformation_},
                                                                                                                              _transformation_inv{glm::inverse(_world_transformation)} {}

    Ray rayThroughPixel(float x, float y, float width_, float height_) const
    {
        glm::vec3 origin{0.0f, 0.0f, 0.0f};
        glm::vec3 direction{x - width_ / 2, y - height_ / 2, -(width_ / 2) / tan(_fov_x / 2)}; //tan(Öffnungswinkel/2)=(width/2)/distance von Camera zum Bildebene.
        Ray rayCamera{origin, direction};
        return rayCamera;
    }

    void camera_translate(glm::vec3 trans_)
    {
        glm::mat4 translate_matrix;
        translate_matrix[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
        translate_matrix[1] = glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};
        translate_matrix[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
        translate_matrix[3] = glm::vec4{trans_, 1.0f};

        _world_transformation = translate_matrix * _world_transformation;
        _transformation_inv = glm::inverse(_world_transformation);
    }
    void camera_rotate(float rad_, glm::vec3 rotate_)
    {
        camera_rotatex(rad_ * rotate_.x);
        camera_rotatey(rad_ * rotate_.y);
        camera_rotatez(rad_ * rotate_.z);
    }
    void camera_rotatex(float rad_)
    {
        glm::mat4 rotate_matrix;
        rotate_matrix[0] = glm::vec4{0.0f, 0.0f, 0.0f, 0.0f};
        rotate_matrix[1] = glm::vec4{0.0f, cos(rad_), -sin(rad_), 0.0f};
        rotate_matrix[2] = glm::vec4{0.0f, sin(rad_), cos(rad_), 0.0f};
        rotate_matrix[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};

        _world_transformation = rotate_matrix * _world_transformation;
        _transformation_inv = glm::inverse(_world_transformation);
    };
    void camera_rotatey(float rad_)
    {
        glm::mat4 rotate_matrix;
        rotate_matrix[0] = glm::vec4{cos(rad_), 0.0f, -sin(rad_), 0.0f};
        rotate_matrix[1] = glm::vec4{0.0f, 1.0, 0.0f, 0.0f};
        rotate_matrix[2] = glm::vec4{sin(rad_), 0.0f, cos(rad_), 0.0f};
        rotate_matrix[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};

        _world_transformation = rotate_matrix * _world_transformation;
        _transformation_inv = glm::inverse(_world_transformation);
    };
    void camera_rotatez(float rad_)
    {
        glm::mat4 rotate_matrix;
        rotate_matrix[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
        rotate_matrix[1] = glm::vec4{0.0f, cos(rad_), 0.0f, -sin(rad_)};
        rotate_matrix[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
        rotate_matrix[3] = glm::vec4{0.0f, sin(rad_), 0.0f, cos(rad_)};

        _world_transformation = rotate_matrix * _world_transformation;
        _transformation_inv = glm::inverse(_world_transformation);
    };
};

#endif
