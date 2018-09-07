#include "shape.hpp"
#include "glm/vec3.hpp"
#include <ostream>
#include <memory>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

// Konstruktor
Shape::Shape() : name_{"unknown"} {};

Shape::Shape(std::string const &name, std::shared_ptr<Material> const &material) : name_{name}, material_{material} {};

Shape::Shape(std::string const &name, std::shared_ptr<Material> const &material, glm::mat4 const &worldTransform) : name_{name}, material_{material}, world_transformation_{worldTransform}, world_transformation_inv_{glm::inverse(worldTransform)} {}

// Destruktor (Aufgabe8):
Shape::~Shape(){};

// get-Methode
std::string Shape::get_name() const
{
    return name_;
}
std::shared_ptr<Material> Shape::get_material() const
{
    return material_;
}

std::ostream &Shape::print(std::ostream &os) const
{
    os << "The Shape: " << name_ << " has color: " << *material_ << "\n";
    return os;
}
std::ostream &operator<<(std::ostream &os, Shape const &s)
{
    return s.print(os);
}

glm::mat4 Shape::world_transformation() const
{
    return world_transformation_;
};

glm::mat4 Shape::world_transformation_inv() const
{
    return world_transformation_inv_;
};

//transform Methoden
void Shape::transform()
{
    world_transformation_ = glm::translate(translation_) * glm::rotate(rotation_angle_, rotation_) * glm::scale(scaling_) * world_transformation_;
    world_transformation_inv_ = glm::inverse(world_transformation_);
    std::cout << "This shape: " << name_ << std::endl;
    std::cout << "transform: " << std::endl;
    std::cout << glm::to_string(world_transformation_) << std::endl;
    std::cout << "inverse: " << std::endl;
    std::cout << glm::to_string(world_transformation_inv_) << std::endl;
}
/* 
glm::mat4 Shape::translate(glm::vec3 const &a)
{
    glm::mat4 trans_mat; // = glm::make_translation;
    trans_mat[0] = glm::vec4{1.0f, 0.0f, 0.0f, a[0]};
    trans_mat[1] = glm::vec4{0.0f, 1.0f, 0.0f, a[1]};
    trans_mat[2] = glm::vec4{0.0f, 0.0f, 1.0f, a[2]};
    trans_mat[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};

    return trans_mat;
    world_transformation_ = trans_mat * world_transformation_;
    world_transformation_inv_ = glm::inverse(world_transformation_);
}

glm::mat4 Shape::scale(glm::vec3 const &b)
{
    glm::mat4 scale_mat;
    scale_mat[0] = glm::vec4{b.x, 0.0f, 0.0f, 0.0f};
    scale_mat[1] = glm::vec4{0.0f, b.y, 0.0f, 0.0f};
    scale_mat[2] = glm::vec4{0.0f, 0.0f, b.z, 0.0f};
    scale_mat[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};

    return scale_mat;

    world_transformation_ = scale_mat * world_transformation_;
    world_transformation_inv_ = glm::inverse(world_transformation_);
}

glm::mat4 Shape::rotate(glm::vec3 const &c)
{

    glm::mat4 rotate_mat = rotate_x(c.x)* rotate_y(c.y)
    rotate_z(c.z);;

    rotate_x(c.x);
    rotate_y(c.y);
    rotate_z(c.z);
}

glm::mat4 Shape::rotate_x(float rad)
{
    glm::mat4 rotate_mat;

    rotate_mat[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
    rotate_mat[1] = glm::vec4{0.0f, cos(rad), -sin(rad), 0.0f};
    rotate_mat[2] = glm::vec4{0.0f, sin(rad), cos(rad), 0.0f};
    rotate_mat[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};

    return rotate_mat;
}

glm::mat4 Shape::rotate_y(float rad)
{
    glm::mat4 rotate_mat;

    rotate_mat[0] = glm::vec4{cos(rad), 0.0f, -sin(rad), 0.0f};
    rotate_mat[1] = glm::vec4{0.0f, 1.0, 0.0f, 0.0f};
    rotate_mat[2] = glm::vec4{sin(rad), 0.0f, cos(rad), 0.0f};
    rotate_mat[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};

    return rotate_mat;
}

glm::mat4 Shape::rotate_z(float rad)
{
    glm::mat4 rotate_mat;

    rotate_mat[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
    rotate_mat[1] = glm::vec4{0.0f, cos(rad), 0.0f, -sin(rad)};
    rotate_mat[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
    rotate_mat[3] = glm::vec4{0.0f, sin(rad), 0.0f, cos(rad)};

    return rotate_mat;
} */
