#include "sphere.hpp"
#include "scene.hpp"
#include "renderer.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

// Konstruktor
Sphere::Sphere():
    mittel_{glm::vec3{0.0f}}, radius_{5.0f}, Shape{}    {}

Sphere::Sphere(glm::vec3 const& m, float const& r):
    mittel_{m}, radius_{r}, Shape{} {}

Sphere::Sphere(float _x, float _y, float _z, float _r) : 
    mittel_{glm::vec3(_x, _y, _z)}, radius_{_r}    {}

Sphere::Sphere(glm::vec3 const &_p, float _r, std::shared_ptr<Material> const& material, std::string const &_n) : 
    Shape(_n, material), mittel_{_p}, radius_{_r}   {}

/*Sphere::Sphere(glm::vec3 const& m, float const& r, std::string const& name):
    mittel_{m}, radius_{r}, Shape{name} {}

Sphere::Sphere(glm::vec3 const& m, float const& r, Color const& color):
    mittel_{m}, radius_{r}, Shape{color} {}*/

Sphere::Sphere(glm::vec3 const& m, float const& r, std::string const& name, std::shared_ptr<Material> const& material):
    mittel_{m}, radius_{r}, Shape{name, material} {
        std::cout<< "Constuctor of Sphere!"<< std::endl;
    }

Sphere::~Sphere()   {
    std::cout<< "Destructor of Sphere!"<< std::endl;
}

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
bool Sphere::intersect(Ray const& r, float& t){
     // from the ray_origin to the intersectPosition
    glm::vec3 v = glm::normalize(r.direction);   //convert to the unit vector with same direction
    auto squaredRadius = std::pow(radius_, 2);
    bool result = glm::intersectRaySphere(r.origin, v, mittel_, squaredRadius, t);
    return result;
}

Hit Sphere::intersectHit(Ray const& ray, float& t){
    // float distance;
    Ray transformedRay{transformRay(getWorldMatInv(), ray)};
    glm::vec3 v = glm::normalize(transformedRay.direction);
    auto squaredRadius = std::pow(radius_, 2);
    bool result = glm::intersectRaySphere(transformedRay.origin, v, mittel_, squaredRadius, t);
    if(result == true){
        glm::vec3 schnittPunkt = transformedRay.origin + (t*transformedRay.direction);
        glm::vec3 normalVector = glm::normalize(schnittPunkt - mittel_);
        schnittPunkt = glm::vec3(world_transformation_*glm::vec4(schnittPunkt, 1.0f));
        normalVector = glm::normalize(glm::vec3(world_transformation_inv_*glm::vec4(normalVector, 0.0f)));
        glm::vec3 vector = schnittPunkt - transformedRay.origin;
        float d = std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2) + std::pow(vector.z, 2));
        return Hit{true, d, this, normalVector, schnittPunkt};
    }
    return Hit{};
}