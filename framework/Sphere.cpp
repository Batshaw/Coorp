#include "Sphere.hpp"
#include <cmath>
#define piconst atan(1.0f) * 4

Sphere::Sphere() : Shape(),
                   _mpunkt{glm::vec3(0.0, 0.0, 0.0)},
                   _radius{1.0} {};

Sphere::Sphere(glm::vec3 const &_p, float _r) : _mpunkt{_p},
                                                _radius{_r} {};

Sphere::Sphere(float _x, float _y, float _z, float _r) : _mpunkt{glm::vec3(_x, _y, _z)},
                                                         _radius{_r} {};

Sphere::Sphere(glm::vec3 const &_p, float _r, std::shared_ptr<Material> const &material, string const &_n) : Shape(_n, material),
                                                                                                             _mpunkt{_p},
                                                                                                             _radius{_r} {};

Sphere::~Sphere(){};

float Sphere::radius() const
{
    return _radius;
}

float Sphere::area()
{
    return piconst * std::pow(_radius, 2) * 4;
};

float Sphere::volume()
{
    return piconst * std::pow(_radius, 3) * 4 / 3;
};

ostream &Sphere::print(ostream &os) const
{
    return Shape::print(os);
}

bool Sphere::intersect(Ray const &_r, float &_t) const
{
    //float distance = 0.0f;
    auto ndirection = glm::normalize(_r.direction);

    auto result = glm::intersectRaySphere(_r.origin,
                                          ndirection,
                                          _mpunkt,
                                          std::pow(_radius, 2),
                                          _t);
    return result;
}

Hit Sphere::intersection(Ray const &_r, float &_t) const
{
    Hit temp;
    if (intersect(_r, _t))
    {
        temp.isHit_ = true;
        temp.distance_ = _t;
        temp.coor_ = _r.get_point(temp.distance_);
        temp.normal_ = glm::normalize(temp.coor_ - _mpunkt);
        //this is type const*
        temp.closest_ = make_shared<Sphere>(this);
    }

    return temp;
};

glm::vec3 Sphere::get_normal(Hit const &hit) const
{
    return glm::normalize(glm::vec3{(hit.coor_ - _mpunkt)});
}
/*bool Sphere::intersect(Ray const& _r, float& _t) const{
    return false;
}*/
