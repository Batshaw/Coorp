#include "Shape.hpp"

Shape::Shape() : name_{"default name"} {};

Shape::Shape(std::string const &n, std::shared_ptr<Material> const &material) : name_{n},
                                                                                material_{material} {};

Shape::Shape(std::string const &n, std::shared_ptr<Material> const &material, glm::mat4 const &world_trans_) : name_{n},
                                                                                                               material_{material},
                                                                                                               world_transformation_{world_trans_},
                                                                                                               world_transformation_inv_{glm::inverse(world_trans_)} {};

Shape::~Shape(){};

std::string Shape::name() const
{
    return name_;
}

std::shared_ptr<Material> Shape::get_material_() const
{
    return material_;
}

std::ostream &Shape::print(std::ostream &os) const
{
    os << name_ << " " << *material_ << std::endl;
    return os;
};

void Shape::translate(glm::vec3 const &a_)
{
    glm::mat4 trans_mat;
    trans_mat[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
    trans_mat[1] = glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};
    trans_mat[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
    trans_mat[3] = glm::vec4{a_, 1.0f};

    world_transformation_ = trans_mat * world_transformation_;
    world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::scale(glm::vec3 const &b_)
{
    glm::mat4 scale_mat;
    scale_mat[0] = glm::vec4{b_.x, 0.0f, 0.0f, 0.0f};
    scale_mat[1] = glm::vec4{0.0f, b_.y, 0.0f, 0.0f};
    scale_mat[2] = glm::vec4{0.0f, 0.0f, b_.z, 0.0f};
    scale_mat[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};

    world_transformation_ = scale_mat * world_transformation_;
    world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::rotate(float rad_, glm::vec3 const &c_)
{
    rotate_x(rad_ * c_.x);
    rotate_y(rad_ * c_.y);
    rotate_z(rad_ * c_.z);
}

void Shape::rotate_x(float rad_)
{
    glm::mat4 rotate_mat;

    rotate_mat[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
    rotate_mat[1] = glm::vec4{0.0f, cos(rad_), -sin(rad_), 0.0f};
    rotate_mat[2] = glm::vec4{0.0f, sin(rad_), cos(rad_), 0.0f};
    rotate_mat[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};

    world_transformation_ = rotate_mat * world_transformation_;
    world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::rotate_y(float rad_)
{
    glm::mat4 rotate_mat;

    rotate_mat[0] = glm::vec4{cos(rad_), 0.0f, -sin(rad_), 0.0f};
    rotate_mat[1] = glm::vec4{0.0f, 1.0, 0.0f, 0.0f};
    rotate_mat[2] = glm::vec4{sin(rad_), 0.0f, cos(rad_), 0.0f};
    rotate_mat[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};

    world_transformation_ = rotate_mat * world_transformation_;
    world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::rotate_z(float rad_)
{
    glm::mat4 rotate_mat;

    rotate_mat[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
    rotate_mat[1] = glm::vec4{0.0f, cos(rad_), 0.0f, -sin(rad_)};
    rotate_mat[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
    rotate_mat[3] = glm::vec4{0.0f, sin(rad_), 0.0f, cos(rad_)};

    world_transformation_ = rotate_mat * world_transformation_;
    world_transformation_inv_ = glm::inverse(world_transformation_);
}

std::ostream &operator<<(std::ostream &os, Shape const &s)
{
    return s.print(os);
}
