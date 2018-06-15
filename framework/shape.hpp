#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include "color.hpp"

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
        

    protected:
        std::string name_;
        Color color_;

};

#endif  //SHAPE_HPP