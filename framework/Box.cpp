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

/*
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

//old intersect method
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
            //std::cout << schnittPunkt.x << " " << schnittPunkt.y << " " << schnittPunkt.z << " \n";
            if (is_inBox(schnittPunkt))
            {
                result = true;
                //std::cout << "t = " << _t << "\n";
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
            //std::cout << schnittPunkt.x << " " << schnittPunkt.y << " " << schnittPunkt.z << " \n";
            if (is_inBox(schnittPunkt))
            {
                result = true;
                //std::cout << "t = " << _t << "\n";
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
            //std::cout << schnittPunkt.x << " " << schnittPunkt.y << " " << schnittPunkt.z << " \n";
            if (is_inBox(schnittPunkt))
            {
                result = true;
                //std::cout << "t = " << _t << "\n";
            }
        }
    }
    return result;
};

bool Box::intersect(Ray const &_r, float &_t, int &_index) const
{
    bool result = false;
    glm::vec3 schnittPunkt;

    float dmin_x, dmin_y, dmin_z;
    float dmax_x, dmax_y, dmax_z;

    float entry_distance;
    float exit_distance;

    int entry_plane_index;
    int exit_plane_index;

    if (_r.direction.x != 0)
    {
        if (_r.direction.x > 0)
        {
            dmin_x = (_minimum.x - _r.origin.x) / _r.direction.x;
        }
        else
            dmax_x = (_maximum.x - _r.origin.x) / _r.direction.x;
    }

    if (_r.direction.y != 0)
    {
        if (_r.direction.y > 0)
        {
            dmin_y = (_minimum.y - _r.origin.y) / _r.direction.y;
        }
        else
            dmax_y = (_maximum.y - _r.origin.y) / _r.direction.y;
    }

    if (_r.direction.z != 0)
    {
        if (_r.direction.z > 0)
        {
            dmin_z = (_minimum.z - _r.origin.z) / _r.direction.z;
        }
        else
            dmax_z = (_maximum.z - _r.origin.z) / _r.direction.z;
    }

    if (dmin_x > dmin_y)
    {

        entry_distance = dmin_x;
        entry_plane_index = (_r.direction.x >= 0) ? 0 : 3;
    }
    else
    {

        entry_distance = dmin_y;
        entry_plane_index = (_r.direction.y >= 0) ? 1 : 4;
    }
    if (dmin_z > entry_distance)
    {

        entry_distance = dmin_z;
        entry_plane_index = (_r.direction.z >= 0) ? 2 : 5;
    }

    if (dmax_x > dmax_y)
    {
        exit_distance = dmax_x;
        exit_plane_index = (_r.direction.x >= 0) ? 3 : 0;
    }
    else
    {
        exit_distance = dmax_y;
        exit_plane_index = (_r.direction.y >= 0) ? 4 : 1;
    }
    if (dmax_z > exit_distance)
    {
        exit_distance = dmax_z;
        exit_plane_index = (_r.direction.z >= 0) ? 5 : 2;
    }

    result = entry_distance < exit_distance && exit_distance != 0;

    if (result)
    {

        if (entry_distance > 0)
        {
            _t = entry_distance;
            _index = entry_plane_index;
        }

        else
        {
            _t = exit_distance;
            _index = exit_plane_index;
        }
    }

    return result;
};

Hit Box::intersection(Ray const &_r, float &_t) const
{
    int index;
    Hit null_hit{nullptr};
    glm::vec3 normal{0, 0, 0};

    if (intersect(_r, _t, index))
    {
        Hit temp{true, _t, (_r.get_point(temp.distance_)), (get_normal(index)), this};
        return temp;
    }

    return null_hit;
}

//old get_normal
glm::vec3 Box::get_normal(Hit const &hit) const
{
    return glm::normalize(glm::vec3{(hit.coor_)});
}

glm::vec3 Box::get_normal(int &_side) const
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