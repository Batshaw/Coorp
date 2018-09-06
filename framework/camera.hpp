#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <glm/vec3.hpp>
#include "ray.hpp"

struct Camera
{
    std::string name_;
    float fov_x_;
    glm::vec3 eye_;
    glm::vec3 dir_;
    glm::vec3 up_;
    glm::mat4 world_transformation_;
    glm::mat4 transformation_inv_;

    Camera() : name_{"default camera"},
               fov_x_{45},
               eye_{0.0f, 0.0f, 0.0f},
               dir_{0.0f, 0.0f, -1.0f},
               up_{0.0f, 1.0f, 0.0f},
               world_transformation_{},
               transformation_inv_{glm::inverse(world_transformation_)} {}

    //Konstruktor mit Name und Öffnungswinkel:
    Camera(std::string const& name, float fov_x) : name_{name},
                                            fov_x_{fov_x},
                                            eye_{0.0f, 0.0f, 0.0f},
                                            dir_{0.0f, 0.0f, -1.0f},
                                            up_{0.0f, 1.0f, 0.0f},
                                            world_transformation_{},
                                            transformation_inv_{glm::inverse(world_transformation_)} {}

    //Konstruktor für Aufgabe 7.3:
    Camera(std::string const& name, float fov_x, glm::vec3 const& eye, glm::vec3 const& dir, glm::vec3 const& up, glm::mat4 const& world_transformation) : name_{name},
                                                                                                                        fov_x_{fov_x},
                                                                                                                        eye_{eye},
                                                                                                                        dir_{dir},
                                                                                                                        up_{up},
                                                                                                                        world_transformation_{world_transformation},
                                                                                                                        transformation_inv_{glm::inverse(world_transformation)} {}

    Ray rayThroughPixel(float x, float y, float width, float height) const
    {
        glm::vec3 origin{0.0f, 0.0f, 0.0f};
        glm::vec3 direction{x - width / 2, y - height / 2, (-width / 2) / tan(fov_x_ / 2)}; //tan(Öffnungswinkel/2)=(width/2)/distance von Camera zum Bildebene.
        Ray rayCamera{origin, direction};
        return rayCamera;
    }

    void camera_translate(glm::vec3 const& trans)
    {
        glm::mat4 translate_matrix;
        translate_matrix[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
        translate_matrix[1] = glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};
        translate_matrix[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
        translate_matrix[3] = glm::vec4{trans, 1.0f};

        world_transformation_ = translate_matrix * world_transformation_;
        transformation_inv_ = glm::inverse(world_transformation_);
    }
    void camera_rotate(float radian, glm::vec3 const& rotate)
    {
        camera_rotatex(radian * rotate.x);
        camera_rotatey(radian * rotate.y);
        camera_rotatez(radian * rotate.z);
    }
    void camera_rotatex(float radian)
    {
        glm::mat4 rotate_matrix;
        rotate_matrix[0] = glm::vec4{0.0f, 0.0f, 0.0f, 0.0f};
        rotate_matrix[1] = glm::vec4{0.0f, cos(radian), -sin(radian), 0.0f};
        rotate_matrix[2] = glm::vec4{0.0f, sin(radian), cos(radian), 0.0f};
        rotate_matrix[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};

        world_transformation_ = rotate_matrix * world_transformation_;
        transformation_inv_ = glm::inverse(world_transformation_);
    };
    void camera_rotatey(float radian)
    {
        glm::mat4 rotate_matrix;
        rotate_matrix[0] = glm::vec4{cos(radian), 0.0f, -sin(radian), 0.0f};
        rotate_matrix[1] = glm::vec4{0.0f, 1.0, 0.0f, 0.0f};
        rotate_matrix[2] = glm::vec4{sin(radian), 0.0f, cos(radian), 0.0f};
        rotate_matrix[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};

        world_transformation_ = rotate_matrix * world_transformation_;
        transformation_inv_ = glm::inverse(world_transformation_);
    };

    void camera_rotatez(float radian)
    {
        glm::mat4 rotate_matrix;
        rotate_matrix[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
        rotate_matrix[1] = glm::vec4{0.0f, cos(radian), 0.0f, -sin(radian)};
        rotate_matrix[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
        rotate_matrix[3] = glm::vec4{0.0f, sin(radian), 0.0f, cos(radian)};

        world_transformation_ = rotate_matrix * world_transformation_;
        transformation_inv_ = glm::inverse(world_transformation_);
    };
};

#endif
