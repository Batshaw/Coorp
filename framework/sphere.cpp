#include "sphere.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

// Konstruktor
Sphere::Sphere():
    mittel_{glm::vec3{0.0f}}, radius_{5.0f}, Shape{}    {}

Sphere::Sphere(glm::vec3 const& m, float const& r):
    mittel_{m}, radius_{r}, Shape{} {}

Sphere::Sphere(glm::vec3 const& m, float const& r, std::string const& name):
    mittel_{m}, radius_{r}, Shape{name} {}

Sphere::Sphere(glm::vec3 const& m, float const& r, Color const& color):
    mittel_{m}, radius_{r}, Shape{color} {}

Sphere::Sphere(glm::vec3 const& m, float const& r, std::string const& name, Color const& color):
    mittel_{m}, radius_{r}, Shape{name, color} {}

// get-Methode
glm::vec3 Sphere::getMittel() const{
    return mittel_;
}
float Sphere::getRadius() const{
    return radius_;
}

// area und volumen
float const PI = atan(1.0f)*4;
float Sphere::area() const{
    return 4*PI*std::pow(radius_, 2);
}
float Sphere::volumen() const{
    return 4*PI*std::pow(radius_, 3)/3;
}

// print-Methode
std::ostream& Sphere::print(std::ostream& os) const{
    Shape::print(os);
    os<< "Coordinates of the middle point: ("<< mittel_.x;
    os<< ", "<< mittel_.y<< ", "<< mittel_.z<< ").\n";
    os<< " Radius of the Sphere is: "<< radius_<<"."<< std::endl;
    return os;
}
std::ostream& operator<<(std::ostream& os, Sphere const& s){
    return s.print(os);
}

// intersect-Methode
bool Sphere::intersect(Ray const& r){
    float distance; // from the ray_origin to the intersectPosition
    glm::vec3 v = glm::normalize(r.direction);   //convert to the unit vector with same direction
    auto squaredRadius = std::pow(radius_, 2);
    bool result = glm::intersectRaySphere(r.origin, v, mittel_, squaredRadius, distance);
    return result;
}