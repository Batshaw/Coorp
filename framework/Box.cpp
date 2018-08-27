#include "Box.hpp"
#include <cmath>
#include <algorithm>

Box::Box() : Shape(),
             _minimum{vec3(0.0, 0.0, 0.0)},
             _maximum{vec3(1.0, 1.0, 1.0)}
{
}

Box::Box(glm::vec3 const &_p1, glm::vec3 const &_p2) : Shape(),
                                                       _minimum{set_min(_p1.x, _p2.x), set_min(_p1.y, _p2.y), set_min(_p1.z, _p2.z)},
                                                       _maximum{set_max(_p1.x, _p2.x), set_max(_p1.y, _p2.y), set_max(_p1.z, _p2.z)}
{
}

Box::Box(string const &n, std::shared_ptr<Material> const &material) : Shape(n, material),
                                                                       _minimum{vec3(0.0, 0.0, 0.0)},
                                                                       _maximum{vec3(1.0, 1.0, 1.0)} {};

Box::Box(vec3 const &_p1, vec3 const &_p2, string const &n, std::shared_ptr<Material> const &material) : Shape(n, material),
                                                                                                         _minimum{set_min(_p1.x, _p2.x), set_min(_p1.y, _p2.y), set_min(_p1.z, _p2.z)},
                                                                                                         _maximum{set_max(_p1.x, _p2.x), set_max(_p1.y, _p2.y), set_max(_p1.z, _p2.z)}
{
}

Box::~Box(){};

float Box::set_max(float const &coor1, float const &coor2)
{
    return ((coor2 > coor1) ? coor2 : coor1);
}

float Box::set_min(float const &coor1, float const &coor2)
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

float Box::area()
{
    return 2 * (length() * width() +
                height() * width() +
                length() * height());
};

float Box::volume()
{
    return length() *
           width() *
           height();
};

ostream &Box::print(ostream &os) const
{
    Shape::print(os);
    os << "pmin : (" << _minimum.x << "; " << _minimum.y << "; " << _minimum.z << ")" << endl;
    os << "pmax : (" << _maximum.x << "; " << _maximum.y << "; " << _maximum.z << ")" << endl;

    return os;
}

/*bool Box::intersect(Ray const &_r) const
{

    return true;
}

bool Box::intersect(Ray const &_r, float &_t) const
{
    vec3 anchor{nearest_corner(_minimum, _maximum, _r.origin)};

    cout << "anchor : (" << anchor.x << "; " << anchor.y << "; " << anchor.z << ")" << endl;

    float anchor_coor[3] = {anchor.x, anchor.y, anchor.z};
    float ray_origin[3] = {_r.origin.x, _r.origin.y, _r.origin.z};
    float ray_direction[3] = {_r.direction.x, _r.direction.y, _r.direction.z};

    float distance[3];

    vec3 target;
    float target_coor[3];

    for (int i = 0; i < 3; i++)
    {
        distance[i] = (anchor_coor[i] - ray_origin[i]) / ray_direction[i];
        target_coor[i] = anchor_coor[i];
    }

    sort(distance, distance + 3);

    for (int i = 0; i < 3; i++)
    {
        target_coor[(i + 1) % 3] = ray_origin[(i + 1) % 3] + distance[i] * ray_direction[(i + 1) % 3];
        target_coor[(i + 2) % 3] = ray_origin[(i + 2) % 3] + distance[i] * ray_direction[(i + 2) % 3];

        target = {target_coor[0], target_coor[1], target_coor[2]};

        if (is_on_surface(target))
        {
            _t = distance[i];
            cout << "target : (" << target.x << "; " << target.y << "; " << target.z << ")" << endl;
            cout << "distance: " << _t << endl;
            return true;
        }
    }

    cout << "distance: " << distance[0] << endl;
    return false;
}

vec3 Box::nearest_corner(vec3 const &min, vec3 const &max, vec3 const &origin) const
{

    float x, y, z;
    x = nearest_komponent(min.x, max.x, origin.x);
    y = nearest_komponent(min.y, max.y, origin.y);
    z = nearest_komponent(min.z, max.z, origin.z);

    vec3 anchor{x, y, z};

    return anchor;
}

vec3 Box::furthest_corner(vec3 const &min, vec3 const &max, vec3 const &origin) const
{

    float x, y, z;
    x = furthest_komponent(min.x, max.x, origin.x);
    y = furthest_komponent(min.y, max.y, origin.y);
    z = furthest_komponent(min.z, max.z, origin.z);

    vec3 anchor{x, y, z};

    return anchor;
}

float Box::nearest_komponent(float const &min, float const &max, float const &origin) const
{
    return ((abs(origin - min) > abs(origin - max)) ? max : min);
}

float Box::furthest_komponent(float const &min, float const &max, float const &origin) const
{
    return ((abs(origin - min) < abs(origin - max)) ? max : min);
}

bool Box::is_on_surface(vec3 const &input) const
{

    return ((input.x >= _minimum.x && input.x <= _maximum.x &&
             input.y >= _minimum.y && input.y <= _maximum.y &&
             input.z >= _minimum.z && input.z <= _maximum.z))
               ? true
               : false;
}*/

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

bool Box::intersect(Ray const &_r, float &_t) const
{
    bool result = false;
    glm::vec3 schnittPunkt;
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
            schnittPunkt = _r.origin + _t * _r.direction;
            std::cout << schnittPunkt.x << " " << schnittPunkt.y << " " << schnittPunkt.z << " \n";
            if (is_inBox(schnittPunkt))
            {
                result = true;
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
            schnittPunkt = _r.origin + _t * _r.direction;
            std::cout << schnittPunkt.x << " " << schnittPunkt.y << " " << schnittPunkt.z << " \n";
            if (is_inBox(schnittPunkt))
            {
                result = true;
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
            schnittPunkt = _r.origin + _t * _r.direction;
            std::cout << schnittPunkt.x << " " << schnittPunkt.y << " " << schnittPunkt.z << " \n";
            if (is_inBox(schnittPunkt))
            {
                result = true;
                std::cout << "t = " << _t << "\n";
            }
        }
    }
    return result;
};

Hit Box::intersection(Ray const &_r, float &_t) const
{

    Hit temp;
    glm::vec3 normal{0, 0, 0};

    if (intersect(_r, _t))
    {
        temp.isHit_ = true;
        temp.distance_ = _t;
        temp.coor_ = _r.get_point(temp.distance_);
        temp.normal_ = normal;
        //this is type const*
        temp.closest_ = make_shared<Box>(this);
    }

    return temp;
}
