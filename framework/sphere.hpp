#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include "ray.hpp"

#define GLM_FORCE_RADIANS 
#include <glm/vec3.hpp>

class Sphere : public Shape{
    public:
        // Konstruktor
        Sphere();
        Sphere(glm::vec3 const& m, float r);
        Sphere(float x, float y, float z, float r = 1.0);
        Sphere(glm::vec3 const& m, float r, std::string const& name, std::shared_ptr<Material> const& material);

        //Destruktor (Aufgabe8):
        ~Sphere();        

        // Methode
        float area() const override;
        float volumen() const override;
        glm::vec3 getCenter() const;
        float getRadius() const;
        std::ostream& print(std::ostream& os) const override;

        // intersect-Methode
        bool intersect(Ray const& r, float& t) const override;
        Hit intersectHit(Ray const& ray, float& t) const override;

    protected:
        glm::vec3 mittel_;
        float radius_;

};

std::ostream& operator<<(std::ostream& os, Sphere const& s);

#endif  //SPHERE_HPP