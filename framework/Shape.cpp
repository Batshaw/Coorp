#include "Shape.hpp"

Shape::Shape() : name_{"default name"}, color_{1.0f, 1.0f, 1.0f} {};

Shape::Shape(string const &n, Color const &col) : name_{n},
                                                  color_{col}
{
}

Shape::~Shape()
{
};

string Shape::name()
{
    return name_;
}

Color Shape::color()
{
    return color_;
}

ostream &Shape::print(ostream &os) const
{
    os << name_ << " " << color_.r << "; " << color_.g << "; " << color_.b << endl;
    return os;
};

ostream &operator<<(ostream &os, Shape const &s)
{
    return s.print(os);
}
