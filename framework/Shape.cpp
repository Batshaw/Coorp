#include "Shape.hpp"

Shape::Shape() : name_{"default name"} {};

Shape::Shape(string const &n, shared_ptr<Material> const& material) : 
    name_{n}, material_{material}   {};

Shape::~Shape()
{
};

string Shape::name()
{
    return name_;
}

/* Color Shape::color()
{
    return color_;
}*/

ostream &Shape::print(ostream &os) const
{
    os << name_ << " " << material_<< endl;
    return os;
};

ostream &operator<<(ostream &os, Shape const &s)
{
    return s.print(os);
}
