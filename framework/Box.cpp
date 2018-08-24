#include "Box.hpp"
#include <cmath>
#include <algorithm>

Box::Box() : Shape(),
             _minimum{glm::vec3(0.0, 0.0, 0.0)},
             _maximum{glm::vec3(1.0, 1.0, 1.0)}
{
}

Box::Box(glm::vec3 const &_p1, glm::vec3 const &_p2) : Shape(),
                                                       _minimum{set_min(_p1.x, _p2.x), set_min(_p1.y, _p2.y), set_min(_p1.z, _p2.z)},
                                                       _maximum{set_max(_p1.x, _p2.x), set_max(_p1.y, _p2.y), set_max(_p1.z, _p2.z)}
{
}

Box::Box(std::string const &n, std::shared_ptr<Material> const &material) : Shape(n, material),
                                                                            _minimum{glm::vec3(0.0, 0.0, 0.0)},
                                                                            _maximum{glm::vec3(1.0, 1.0, 1.0)} {};

Box::Box(glm::vec3 const &_p1, glm::vec3 const &_p2, std::string const &n, std::shared_ptr<Material> const &material) : Shape(n, material),
                                                                                                                        _minimum{set_min(_p1.x, _p2.x), set_min(_p1.y, _p2.y), set_min(_p1.z, _p2.z)},
                                                                                                                        _maximum{set_max(_p1.x, _p2.x), set_max(_p1.y, _p2.y), set_max(_p1.z, _p2.z)}
{
}

Box::~Box(){};

float Box::set_max(float coor1, float coor2)
{
    return ((coor2 > coor1) ? coor2 : coor1);
}

float Box::set_min(float coor1, float coor2)
{
    return ((coor2 < coor1) ? coor2 : coor1);
}

float Box::length() const
{
    return std::fabs(_maximum.x - _minimum.x);
}

float Box::width() const
{
    return std::fabs(_maximum.y - _minimum.y);
}

float Box::height() const
{
    return std::fabs(_maximum.z - _minimum.z);
}

float Box::area() const
{
    return 2 * (length() * width() +
                height() * width() +
                length() * height());
};

float Box::volume() const
{
    return length() *
           width() *
           height();
};

std::ostream &Box::print(std::ostream &os) const
{
    Shape::print(os);
    os << "pmin : (" << _minimum.x << "; " << _minimum.y << "; " << _minimum.z << ")" << std::endl;
    os << "pmax : (" << _maximum.x << "; " << _maximum.y << "; " << _maximum.z << ")" << std::endl;

    return os;
};

// in Box???
bool Box::is_inBox(glm::vec3 const &punkt) const
{
    if (_minimum.x <= punkt.x && punkt.x <= _maximum.x && _minimum.y <= punkt.y && punkt.y <= _maximum.y && _minimum.z <= punkt.z && punkt.z <= _maximum.z)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//old intersect method
/* s */

/* bool Box::intersect(Ray const &_r, float &_t, int &_index) const
{
    bool _result = false;
    glm::vec3 _schnittPunkt;
    if (_r.direction.x != 0)
    {
        if (_r.direction.x > 0)
        {
            _t = (_minimum.x - _r.origin.x) / _r.direction.x;
        }
        else
            _t = (_maximum.x - _r.origin.x) / _r.direction.x;
        if (_t > 0)
        {
            _schnittPunkt = _r.origin + _t * _r.direction;
            std::cout << _schnittPunkt.x << " " << _schnittPunkt.y << " " << _schnittPunkt.z << " \n";
            if (is_inBox(_schnittPunkt))
            {
                _result = true;
                std::cout << "t = " << _t << "\n";
            }
        }
    }
    if (_r.direction.y != 0)
    {
        if (_r.direction.y > 0)
        {
            _t = (_minimum.y - _r.origin.y) / _r.direction.y;
        }
        else
            _t = (_maximum.y - _r.origin.y) / _r.direction.y;
        if (_t > 0)
        {
            _schnittPunkt = _r.origin + _t * _r.direction;
            std::cout << _schnittPunkt.x << " " << _schnittPunkt.y << " " << _schnittPunkt.z << " \n";
            if (is_inBox(_schnittPunkt))
            {
                _result = true;
                std::cout << "t = " << _t << "\n";
            }
        }
    }
    if (_r.direction.z != 0)
    {
        if (_r.direction.z > 0)
        {
            _t = (_minimum.z - _r.origin.z) / _r.direction.z;
        }
        else
            _t = (_maximum.z - _r.origin.z) / _r.direction.z;
        if (_t > 0)
        {
            _schnittPunkt = _r.origin + _t * _r.direction;
            std::cout << _schnittPunkt.x << " " << _schnittPunkt.y << " " << _schnittPunkt.z << " \n";
            if (is_inBox(_schnittPunkt))
            {
                _result = true;
                std::cout << "t = " << _t << "\n";
            }
        }
    }
    return _result;
}; */

Hit Box::intersect(Ray const &_r) const
{
    float _t = 0;

    float dmin_x, dmin_y, dmin_z;
    float dmax_x, dmax_y, dmax_z;

    float entry_distance;
    float exit_distance;

    bool _result = false;

    glm::vec3 _schnittPunkt;

    int entry_side;
    int exit_side;

    if (_r.direction.x != 0)
    {
        if (_r.direction.x > 0)
        {
            dmin_x = (_minimum.x - _r.origin.x) / _r.direction.x;
            dmax_x = (_maximum.x - _r.origin.x) / _r.direction.x;
        }
        else
        {
            dmin_x = (_maximum.x - _r.origin.x) / _r.direction.x;
            dmax_x = (_minimum.x - _r.origin.x) / _r.direction.x;
        }
    }
    if (_r.direction.y != 0)
    {
        if (_r.direction.y > 0)
        {
            dmin_y = (_minimum.y - _r.origin.y) / _r.direction.y;
            dmax_y = (_maximum.y - _r.origin.y) / _r.direction.y;
        }
        else
        {
            dmin_y = (_maximum.y - _r.origin.y) / _r.direction.y;
            dmax_y = (_minimum.y - _r.origin.y) / _r.direction.y;
        }
    }
    if (_r.direction.z != 0)
    {
        if (_r.direction.z > 0)
        {
            dmin_z = (_minimum.z - _r.origin.z) / _r.direction.z;
            dmax_z = (_maximum.z - _r.origin.z) / _r.direction.z;
        }
        else
        {
            dmin_z = (_maximum.z - _r.origin.z) / _r.direction.z;
            dmax_z = (_minimum.z - _r.origin.z) / _r.direction.z;
        }
    }

    if (dmin_x < dmin_y)
    {
        entry_distance = dmin_x;
        entry_side = (_r.direction.x >= 0.0) ? 0 : 3;
    }
    else
    {
        entry_distance = dmin_y;
        entry_side = (_r.direction.y >= 0.0) ? 1 : 4;
    }

    if (dmin_z < entry_distance)
    {
        entry_distance = dmin_z;
        entry_side = (_r.direction.z >= 0.0) ? 2 : 5;
    }

    if (dmax_x > dmax_y)
    {
        exit_distance = dmax_x;
        exit_side = (_r.direction.x >= 0.0) ? 3 : 0;
    }
    else
    {
        exit_distance = dmax_y;
        exit_side = (_r.direction.y >= 0.0) ? 4 : 1;
    }

    if (dmax_z > exit_distance)
    {
        exit_distance = dmax_z;
        exit_side = (_r.direction.z >= 0.0) ? 5 : 2;
    }

    _result = (entry_distance < exit_distance && exit_distance > 0.0f);

    if (_result = true)
    {
        Hit hit{_t, _result, _schnittPunkt, get_normal(entry_side), this};
        return hit;
    }
    else
    {
        Hit hit{_t, _result, _schnittPunkt, get_normal(exit_side), this};
        return hit;
    }
}

//old get_normal
glm::vec3 Box::get_normal(Hit const &hit) const
{
    return hit.normal_;
}

glm::vec3 Box::get_normal(int &__side) const
{
    switch (__side)
    {
    case 0:
        return glm::vec3{-1.0, 0.0, 0.0}; // -x
    case 1:
        return glm::vec3{0.0, -1.0, 0.0}; // -y
    case 2:
        return glm::vec3{0.0, 0.0, -1.0}; // -z
    case 3:
        return glm::vec3{1.0, 0.0, 0.0}; // +x-Plane
    case 4:
        return glm::vec3{0.0, 1.0, 0.0}; // +y-Plane
    case 5:
        return glm::vec3{0.0, 0.0, 1.0}; // +z-Plane
    }
}

glm::vec3 Box::get_vector_to_light(Hit const &_inter, Light const &_light) const
{

    return glm::normalize(glm::vec3{_inter.coor_ - _light._origin});
}