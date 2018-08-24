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
            if (is_inBox(_schnittPunkt))
            {
                _result = true;
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
            if (is_inBox(_schnittPunkt))
            {
                _result = true;
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
            if (is_inBox(_schnittPunkt))
            {
                _result = true;

            }
        }
    }
    //Zum testen mit side index 5
    glm::vec3 _normal = get_normal(5);

    return Hit{_t,_result,_schnittPunkt,_normal,this};
}

//old get_normal
glm::vec3 Box::get_normal(Hit const &hit) const
{
    return hit.normal_;
}

glm::vec3 Box::get_normal(int _side) const
{
    switch (_side)
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