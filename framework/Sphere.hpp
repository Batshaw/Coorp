#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>
#include "ray.hpp"

class Sphere : public Shape{
    public:
        // Konstruktor
        Sphere();
        Sphere(glm::vec3 const& m, float const& r);
        /*Sphere(glm::vec3 const& m, float const& r, std::string const& name);
        Sphere(glm::vec3 const& m, float const& r, Color const& color);*/
        Sphere(glm::vec3 const& m, float const& r, std::string const& name, std::shared_ptr<Material> const& material);
        Sphere(float _x, float _y, float _z, float _r = 1.0);
        Sphere(glm::vec3 const &_p, float _r, std::shared_ptr<Material> const& material, std::string const &_n);

        //Destruktor (Aufgabe8):
        ~Sphere();        

        // Methode
        float area() const override;
        float volumen() const override;
        glm::vec3 getMittel() const;
        float getRadius() const;
        // std::string getName() const override;
        // Color getColor() const override;

        std::ostream& print(std::ostream& os) const override;

        // intersect-Methode
        bool intersect(Ray const& r, float& t) override;
        Hit intersectHit(Ray const& ray) override;

    protected:
        glm::vec3 mittel_;
        float radius_;

};

std::ostream& operator<<(std::ostream& os, Sphere const& s);

#endif  //SPHERE_HPP