#include "Sphere.hpp"
#include <cmath>

Sphere::Sphere() : Shape(),
                   _mpunkt{glm::vec3(0.0, 0.0, 0.0)},
                   _radius{1.0} {};

Sphere::Sphere(glm::vec3 const &_p, float _r) : _mpunkt{_p},
                                                _radius{_r} {};

Sphere::Sphere(float _x, float _y, float _z, float _r) : _mpunkt{glm::vec3(_x, _y, _z)},
                                                         _radius{_r} {};

Sphere::Sphere(glm::vec3 const &_p, float _r, std::shared_ptr<Material> const& material, string const &_n) : Shape(_n, material),
                                                                                     _mpunkt{_p},
                                                                                     _radius{_r} 
{
};


Sphere::~Sphere()
{
};

float const M_PI = atan(1.0f)*4;
float Sphere::radius() const
{
    return _radius;
}

float Sphere::area()
{
    return M_PI * pow(_radius, 2) * 4;
};

float Sphere::volume()
{
    return M_PI * pow(_radius, 3) * 4 / 3;
};

ostream &Sphere::print(ostream &os) const
{
    return Shape::print(os);
}

bool Sphere::intersect(Ray const& _r) const
{
    float distance = 0.0f;
    auto ndirection = glm::normalize(_r.direction);

    auto result = glm::intersectRaySphere(_r.origin,
                                          ndirection,
                                          _mpunkt,
                                          pow(_radius, 2),
                                          distance);
    return result;
}

bool Sphere::intersect(Ray const& _r, float& _t) const{
    return false;
}
