#include "shape.hpp"
#include "glm/vec3.hpp"

// Konstruktor
Shape::Shape():
    name_{"unknown"}, color_{Color(0.0f, 0.0f, 0.0f)}   {}
Shape::Shape(std::string const& name):
    name_{name}, color_{Color(0.0f, 0.0f, 0.0f)}    {}
Shape::Shape(Color const& color):
    name_{"unknown"}, color_{color} {}
Shape::Shape(std::string const& name, Color const& color):
    name_{name}, color_{color}  {}

// get-Methode
std::string Shape::getName() const{
    return name_;
}
Color Shape::getColor() const{
    return color_;
}
