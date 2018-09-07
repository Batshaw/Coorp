#include "sphere.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "scene.hpp"

// Konstruktor
Sphere::Sphere() : mittel_{glm::vec3{0.0f}}, radius_{5.0f}, Shape{} {}

Sphere::Sphere(glm::vec3 const &m, float const &r) : mittel_{m}, radius_{r}, Shape{} {}

Sphere::Sphere(float _x, float _y, float _z, float _r) : mittel_{glm::vec3(_x, _y, _z)}, radius_{_r} {}

Sphere::Sphere(glm::vec3 const &_p, float _r, std::shared_ptr<Material> const &material, std::string const &_n) : Shape(_n, material), mittel_{_p}, radius_{_r} {}

/*Sphere::Sphere(glm::vec3 const& m, float const& r, std::string const& name):
    mittel_{m}, radius_{r}, Shape{name} {}

Sphere::Sphere(glm::vec3 const& m, float const& r, Color const& color):
    mittel_{m}, radius_{r}, Shape{color} {}*/

Sphere::Sphere(glm::vec3 const &m, float const &r, std::string const &name, std::shared_ptr<Material> const &material) : mittel_{m}, radius_{r}, Shape{name, material} {};

Sphere::~Sphere(){};

// get-Methode
glm::vec3 Sphere::get_mittel() const
{
    return mittel_;
}
float Sphere::get_radius() const
{
    return radius_;
}

// area und volumen
float const PI = atan(1.0f) * 4;
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
bool Sphere::intersect(Ray const &r, float &t)
{
    // from the ray_origin to the intersectPosition
    glm::vec3 v = glm::normalize(r.direction_); //convert to the unit vector with same direction
    auto squaredRadius = std::pow(radius_, 2);
    bool result = glm::intersectRaySphere(r.origin_, v, mittel_, squaredRadius, t);
    return result;
}

Hit Sphere::intersectHit(Ray const &ray)
{
    float distance;
    Ray transform_ray = transformRay(world_transformation_, ray);

    glm::vec3 v = glm::normalize(transform_ray.direction_);
    auto squaredRadius = std::pow(radius_, 2);
    bool result = intersect(transform_ray, distance);
    if (result == true)
    {

        glm::vec3 raw_point = (transform_ray.origin_ + (distance * transform_ray.direction_));
        glm::vec4 transformed_point = world_transformation_inv_ * glm::vec4{raw_point, 1.0f};
        glm::vec3 schnittPunkt{transformed_point};

        glm::vec3 raw_normal = glm::normalize(schnittPunkt - mittel_);
        glm::vec4 transformed_normal = world_transformation_inv_ * glm::vec4{raw_normal, 1.0f};
        glm::vec3 normalVector{transformed_normal};

        return Hit{true, distance, this, glm::normalize(raw_normal), raw_point};
    }
    return Hit{};
}