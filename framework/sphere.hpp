#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Sphere : public Shape{
    public:
        // Konstruktor
        Sphere();
        Sphere(glm::vec3 const& m, float const& r);
        Sphere(glm::vec3 const& m, float const& r, std::string const& name);
        Sphere(glm::vec3 const& m, float const& r, Color const& color);
        Sphere(glm::vec3 const& m, float const& r, std::string const& name, Color const& color);

        // Methode
        float area() const override;
        float volumen() const override;
        glm::vec3 getMittel() const;
        float getRadius() const;

        std::ostream& print(std::ostream& os) const override;

    protected:
        glm::vec3 mittel_;
        float radius_;

};

std::ostream& operator<<(std::ostream& os, Sphere const& s);

#endif  //SPHERE_HPP