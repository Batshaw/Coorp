#include "sphere.hpp"
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "scene.hpp"

//Windows - Linux kompatible
#define PI (atan(1.0f) * 4)

// Konstruktor
Sphere::Sphere() : mittel_{glm::vec3{0.0f}}, radius_{5.0f}, Shape{} {}

//User defined Konstruktoren
Sphere::Sphere(glm::vec3 const &m, float r) : mittel_{m}, radius_{r}, Shape{} {}
Sphere::Sphere(float x, float y, float z, float r) : mittel_{glm::vec3(x, y, z)}, radius_{r} {}
Sphere::Sphere(glm::vec3 const &m, float r, std::string const &name, std::shared_ptr<Material> const &material) : Shape(name, material), mittel_{m}, radius_{r} {}

//Destruktor
Sphere::~Sphere(){};

// get-Methode
glm::vec3 Sphere::getCenter() const
{
    return mittel_;
}
float Sphere::getRadius() const
{
    return radius_;
}

// area und volumen
float Sphere::area() const
{
    return 4 * PI * std::pow(radius_, 2);
}
float Sphere::volumen() const
{
    return 4 * PI * std::pow(radius_, 3) / 3;
}

// print-Methode
std::ostream &Sphere::print(std::ostream &os) const
{
    Shape::print(os);
    os << "Coordinates of the middle point: (" << mittel_.x;
    os << ", " << mittel_.y << ", " << mittel_.z << ").\n";
    os << " Radius of the Sphere is: " << radius_ << "." << std::endl;
    return os;
}
std::ostream &operator<<(std::ostream &os, Sphere const &s)
{
    return s.print(os);
}

// intersect-Methode
bool Sphere::intersect(Ray const &r, float &t) const
{
    // from the ray_origin_ to the intersectPosition
    glm::vec3 v = glm::normalize(r.direction_);
    auto squaredRadius = std::pow(radius_, 2);
    bool result = glm::intersectRaySphere(r.origin_, v, mittel_, squaredRadius, t);
    return result;
}

Hit Sphere::intersectHit(Ray const &ray, float &t) const
{
    Ray transformedRay{transformRay(world_transformation_inv_, ray)};
    glm::vec3 v = glm::normalize(transformedRay.direction_);
    auto squaredRadius = std::pow(radius_, 2);
    bool result = intersect(transformedRay,t);
    if (result == true)
    {
        glm::vec3 schnittPunkt = transformedRay.origin_ + (t * transformedRay.direction_);
        glm::vec3 normalVector = glm::normalize(schnittPunkt - mittel_);
        schnittPunkt = glm::vec3(world_transformation_ * glm::vec4(schnittPunkt, 1.0f));
        normalVector = glm::vec3{glm::transpose((world_transformation_)) * glm::vec4{normalVector, 0.0f}};
        glm::vec3 vector = schnittPunkt - transformedRay.origin_;
        float d = std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2) + std::pow(vector.z, 2));
        return Hit{true, d, this, normalVector, schnittPunkt};
    }
    return Hit{};
}