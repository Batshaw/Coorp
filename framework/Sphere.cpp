#include "Sphere.hpp"
#include <cmath>

Sphere::Sphere() : Shape{},
                   _mpunkt{glm::vec3(0.0, 0.0, 0.0)},
                   _radius{1.0} {};

Sphere::Sphere(glm::vec3 const &_p, float _r) : _mpunkt{_p},
                                                _radius{_r} {};

Sphere::Sphere(float _x, float _y, float _z, float _r) : _mpunkt{glm::vec3(_x, _y, _z)},
                                                         _radius{_r} {};

Sphere::Sphere(glm::vec3 const &_p, float _r, std::shared_ptr<Material> const &material, std::string const &_n) : Shape{_n, material},
                                                                                                                  _mpunkt{_p},
                                                                                                                  _radius{_r} {};

Sphere::~Sphere(){};

glm::vec3 Sphere::center() const
{
    return _mpunkt;
}

float Sphere::radius() const
{
    return _radius;
}
float const PI = atan(1.0f) * 4;

float Sphere::area() const
{
    return PI * std::pow(_radius, 2) * 4;
};

float Sphere::volume() const
{
    return PI * std::pow(_radius, 3) * 4 / 3;
};

std::ostream &Sphere::print(std::ostream &os) const
{
    Shape::print(os);
    os << "center :(" << _mpunkt.x << "; " << _mpunkt.y << "; " << _mpunkt.z << ")" << std::endl;
    os << "radius : " << _radius<<std::endl;
    
    return os;
}

bool Sphere::intersect(Ray const &_r, float &_t)
{
    auto ndirection = glm::normalize(_r.direction);

    auto result = glm::intersectRaySphere(_r.origin,
                                          ndirection,
                                          _mpunkt,
                                          std::pow(_radius, 2),
                                          _t);

    return result;
}

Hit Sphere::intersect_hit(Ray const &_r)
{
    float distance;
    bool is_hit = intersect(_r, distance);
    if (is_hit)
    {
        glm::vec3 schnitt_punkt = _r.origin + (distance * _r.direction);
        glm::vec3 normal_vector = get_normal(schnitt_punkt);
        return Hit{distance, is_hit, schnitt_punkt, normal_vector, this};
    }

    return Hit{};
};

glm::vec3 Sphere::get_normal(glm::vec3 const &_cut) const
{
    return glm::normalize((_cut - _mpunkt));
}

glm::vec3 Sphere::get_vector_to_light(Hit const &_inter, Light const &_light) const
{
    return glm::normalize(glm::vec3{_inter.coor_ - _light._origin});
}
