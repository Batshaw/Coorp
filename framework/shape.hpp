#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include "color.hpp"
#include <ostream>

class Shape{
    public:
        Shape();
        Shape(std::string const& name);
        Shape(Color const& color);
        Shape(std::string const& name, Color const& color);

        std::string getName() const;
        Color getColor() const;

        virtual float area() const = 0;
        virtual float volumen() const = 0;
        
        virtual std::ostream& print(std::ostream& os) const;

    protected:
        std::string name_;
        Color color_;

};

std::ostream& operator<<(std::ostream&os, Shape const& s);

#endif  //SHAPE_HPP