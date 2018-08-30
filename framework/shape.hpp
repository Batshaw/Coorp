#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include "color.hpp"
#include <ostream>
#include "material.hpp"
#include "ray.hpp"
#include "glm/vec3.hpp"
#include <memory>

class Shape{
    public:
        Shape();
        /*Shape(std::string const& name);
        Shape(std::shared_ptr<Material> material);*/
        Shape(std::string const& name, std::shared_ptr<Material> const& material);
        virtual ~Shape();

        std::string getName() const;
        Color getColor() const;
        std::shared_ptr<Material> getMaterial() const;

        virtual float area() const = 0;
        virtual float volumen() const = 0;
        
        virtual bool intersect(Ray const& r, float& t) = 0;
        
        virtual std::ostream& print(std::ostream& os) const;

    protected:
        std::string name_;
        std::shared_ptr<Material> material_;

};

std::ostream& operator<<(std::ostream&os, Shape const& s);

#endif  //SHAPE_HPP