#include "Shape.hpp"

Shape::Shape() : name_{"default name"} {};

Shape::Shape(std::string const &n, std::shared_ptr<Material> const &material) : name_{n}, material_{material} {};

Shape::~Shape(){};

std::string Shape::name()
{
    return name_;
}

std::shared_ptr<Material> Shape::get_material_() const{
    return material_;
}

/* Color Shape::color()
{
    return color_;
}*/

std::ostream& Shape::print(std::ostream &os) const
{
    os << name_ << " " << material_ << std::endl;
    return os;
};

std::ostream &operator<<(std::ostream &os, Shape const &s)
{
    return s.print(os);
}


