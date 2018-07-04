#include "shape.hpp"
#include "glm/vec3.hpp"
#include <ostream>

// Konstruktor
Shape::Shape():
    name_{"unknown"}   {}
/*Shape::Shape(std::string const& name):
    name_{name}, color_{Color(0.0f, 0.0f, 0.0f)}    {}
Shape::Shape(Color const& color):
    name_{"unknown"}, color_{color} {}*/
Shape::Shape(std::string const& name, std::shared_ptr<Material> const& material):
    name_{name}, material_{material}  {
        std::cout<< "Constructor of Shape!"<< std::endl;
    }

// Destruktor (Aufgabe8):
Shape::~Shape() {
    std::cout<< "Destuction of Shape!"<< std::endl;
}

// get-Methode
std::string Shape::getName() const{
    return name_;
}
std::shared_ptr<Material> Shape::getColor() const{
    return material_;
}

std::ostream& Shape::print(std::ostream& os) const{
    os<< "The Shape: "<< name_ << " has color: "<< color_<< "\n";
    return os;
}
std::ostream& operator<<(std::ostream& os, Shape const& s){
    return s.print(os);
}