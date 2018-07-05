#include "Box.hpp"
#include <cmath>
#include <algorithm>

Box::Box() : Shape(),
             _minimum{vec3(0.0, 0.0, 0.0)},
             _maximum{vec3(1.0, 1.0, 1.0)}
{
}

Box::Box(vec3 const &_p1, vec3 const &_p2) : Shape(),
                                             _minimum{set_min(_p1.x, _p2.x), set_min(_p1.y, _p2.y), set_min(_p1.z, _p2.z)},
                                             _maximum{set_max(_p1.x, _p2.x), set_max(_p1.y, _p2.y), set_max(_p1.z, _p2.z)}

{
}

Box::Box(string const &n, Color const &col) : Shape(n, col),
                                              _minimum{vec3(0.0, 0.0, 0.0)},
                                              _maximum{vec3(1.0, 1.0, 1.0)} {};

Box::Box(vec3 const &_p1, vec3 const &_p2, string const &n, Color const &col) : Shape(n, col),
                                                                                _minimum{set_min(_p1.x, _p2.x), set_min(_p1.y, _p2.y), set_min(_p1.z, _p2.z)},
                                                                                _maximum{set_max(_p1.x, _p2.x), set_max(_p1.y, _p2.y), set_max(_p1.z, _p2.z)}
{
}

Box::~Box(){};
float Box::set_max(float const &coor1, float const &coor2)
{
    if (coor2 > coor1)
    {
        return coor2;
    }
    else
    {
        return coor1;
    }
}
float Box::set_min(float const &coor1, float const &coor2)
{
    if (coor2 < coor1)
    {
        return coor2;
    }
    else
    {
        return coor1;
    }
}

float Box::length() const
{
    return fabs(_maximum.x - _minimum.x);
}

float Box::width() const
{
    return fabs(_maximum.y - _minimum.y);
}

float Box::height() const
{
    return fabs(_maximum.z - _minimum.z);
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

bool Box::intersect(Ray const &_r) const
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
        target[i] = anchor_coor[i];
    }

    sort(distance, distance + 3);

    for (int i = 0; i < 3; i++)
    {
        cout << " distance " << i << ": " << distance[i] << endl;
    }

    for (int i = 0; i < 3; i++)
    {
        target_coor[(i + 1) % 3] = ray_origin[(i + 1) % 3] + distance[i] * ray_direction[(i + 1) % 3];
        target_coor[(i + 2) % 3] = ray_origin[(i + 2) % 3] + distance[i] * ray_direction[(i + 2) % 3];
        cout << " target: " << target_coor[0] << ", " << target_coor[1] << ", " << target_coor[2] << endl;

        if (target_coor[0] >= _minimum.x && target_coor[0] <= _maximum.x &&
            target_coor[1] >= _minimum.y && target_coor[1] <= _maximum.y &&
            target_coor[2] >= _minimum.z && target_coor[2] <= _maximum.z )
        {
            _t = distance[i];
            target = {target_coor[0], target_coor[1], target_coor[2]};
            return true;
        }
    }

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

    if (abs(origin - min) > abs(origin - max))
    {
        return max;
    }
    else
    {
        return min;
    }
}

float Box::furthest_komponent(float const &min, float const &max, float const &origin) const
{
    if (abs(origin - min) < abs(origin - max))
    {
        return max;
    }
    else
    {
        return min;
    }
}

bool Box::is_on_surface(vec3 const &p1, vec3 const &p2, vec3 const &input, float &distance) const
{

    float coor1[3] = {p1.x, p1.y, p1.z};
    float coor2[3] = {p2.x, p2.y, p2.z};

    float input_coor[3] = {input.x, input.y, input.z};

    bool inside[2] = {false, false};

    for (int i = 0; i < 3; i++)
    {

        if (coor1[i] != coor2[i])
        {

            if (coor1[i] > coor2[i])
            {

                if (input_coor[i] > coor2[i] && input_coor[i] < coor1[i])
                {
                    inside[0] = true;
                }

                else
                {
                    inside[0] = false;
                }
            }
            else
            {
                if (input_coor[i] > coor2[i] && input_coor[i] < coor1[i])
                {
                    inside[0] = true;
                }

                else
                {
                    inside[0] = false;
                }
            }
        }
    }

    for (int i = 0; i < 2; i++)
    {

        if (!inside[i])
        {
            return false;
        }
    }

    return true;
}
