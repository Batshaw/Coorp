#include "shape.hpp"


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
void Shape::transform(glm::mat4 const &matrix)
{
    world_transformation_ = matrix * world_transformation_;
    world_transformation_inv_ = glm::inverse(world_transformation_);
    /* 
    std::cout << "This shape: " << name_ << std::endl;
    std::cout << "translate: " << std::endl;
    std::cout << glm::to_string(trans) << std::endl;
    std::cout << "rotate: " << std::endl;
    std::cout << glm::to_string(rotat) << std::endl;
    std::cout << "scaling: " << std::endl;
    std::cout << glm::to_string(scale) << std::endl;
    std::cout << "transform: " << std::endl;
    std::cout << glm::to_string(world_transformation_) << std::endl;
    std::cout << "inverse: " << std::endl;
    std::cout << glm::to_string(world_transformation_inv_) << std::endl;
 */
};