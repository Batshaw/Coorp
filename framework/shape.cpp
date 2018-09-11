#include "shape.hpp"

// Konstruktor
Shape::Shape() : name_{"unknown"}, material_{std::make_shared<Material>(Material())}, world_transformation_{1.0f}, world_transformation_inv_{glm::inverse(world_transformation_)} {};

//Shape mit Name und Material
Shape::Shape(std::string const &name, std::shared_ptr<Material> const &material) : name_{name}, material_{material}, world_transformation_{1.0f}, world_transformation_inv_{glm::inverse(world_transformation_)} {};

//vollig Userdefined Konstuktor
Shape::Shape(std::string const &name, std::shared_ptr<Material> const &material, glm::mat4 const &worldTransform) : name_{name}, material_{material}, world_transformation_{worldTransform}, world_transformation_inv_{glm::inverse(worldTransform)} {}

//Destruktor (Aufgabe8):
Shape::~Shape(){};

// get-Methode
std::string Shape::getName() const
{
    return name_;
}
std::shared_ptr<Material> Shape::getMaterial() const
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

//Get world_transformation_ Matrix
glm::mat4 Shape::getMatrix() const
{
    return world_transformation_;
};

//Get world_transformation_inv_ Matrix
glm::mat4 Shape::getInverse() const
{
    return world_transformation_inv_;
};

//transform Methoden
void Shape::transform(glm::mat4 const &matrix)
{
    world_transformation_ = matrix * world_transformation_;
    world_transformation_inv_ = glm::inverse(world_transformation_);
};