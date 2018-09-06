#include "Box.hpp"
#include <cmath>
#include <algorithm>
#include <catch.hpp>

Box::Box() : Shape{},
             _minimum{glm::vec3(0.0f, 0.0f, 0.0f)},
             _maximum{glm::vec3(1.0f, 1.0f, 1.0f)}
{
}

Box::Box(glm::vec3 const &_p1, glm::vec3 const &_p2) : Shape{},
                                                       _minimum{set_min(_p1.x, _p2.x), set_min(_p1.y, _p2.y), set_min(_p1.z, _p2.z)},
                                                       _maximum{set_max(_p1.x, _p2.x), set_max(_p1.y, _p2.y), set_max(_p1.z, _p2.z)}
{
}

Box::Box(std::string const &n, std::shared_ptr<Material> const &material) : Shape{n, material},
                                                                            _minimum{glm::vec3(0.0f, 0.0f, 0.0f)},
                                                                            _maximum{glm::vec3(1.0f, 1.0f, 1.0f)} {};

Box::Box(glm::vec3 const &_p1, glm::vec3 const &_p2, std::string const &n, std::shared_ptr<Material> const &material) : Shape{n, material},
                                                                                                                        _minimum{set_min(_p1.x, _p2.x), set_min(_p1.y, _p2.y), set_min(_p1.z, _p2.z)},
                                                                                                                        _maximum{set_max(_p1.x, _p2.x), set_max(_p1.y, _p2.y), set_max(_p1.z, _p2.z)}
{
}

Box::~Box(){};

float Box::set_max(float coor1, float coor2) const
{
    return std::max(coor1, coor2);
}

float Box::set_min(float coor1, float coor2) const
{
    return std::min(coor1, coor2);
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

bool Box::intersect(Ray const &_r, float &_t)
{
    bool result = false;
    if (_r.direction.x == 0 &&
        _r.direction.y == 0 &&
        _r.direction.z == 0)
    {
        std::cout << "add another direction (!= 0)";
    }
    else
    {
        std::vector<float> distance_vec;
        float minX = (_minimum.x - _r.origin.x) / _r.direction.x;
        float maxX = (_maximum.x - _r.origin.x) / _r.direction.x;
        distance_vec.push_back(minX);
        distance_vec.push_back(maxX);

        float minY = (_minimum.y - _r.origin.y) / _r.direction.y;
        float maxY = (_maximum.y - _r.origin.y) / _r.direction.y;
        distance_vec.push_back(minY);
        distance_vec.push_back(maxY);

        float minZ = (_minimum.z - _r.origin.z) / _r.direction.z;
        float maxZ = (_maximum.z - _r.origin.z) / _r.direction.z;
        distance_vec.push_back(minZ);
        distance_vec.push_back(maxZ);

        std::sort(distance_vec.begin(), distance_vec.end());

        for (auto i : distance_vec)
        {
            if (!std::isinf(i))
            {
                glm::vec3 schnittPunkt{(_r.origin + (i * _r.direction))};
                if ((schnittPunkt.x <= _maximum.x && schnittPunkt.x >= _minimum.x) &&
                    (schnittPunkt.y <= _maximum.y && schnittPunkt.y >= _minimum.y) &&
                    (schnittPunkt.z <= _maximum.z && schnittPunkt.z >= _minimum.z))
                {
                    _t = i;
                    result = true;
                    return result;
                }
            }
        }

        return false;
    };
}

Hit Box::intersect_hit(Ray const &_r)
{
    float distance;
    bool is_hit = intersect(_r, distance);

    if (is_hit)
    {
        glm::vec3 schnitt_punkt{(_r.origin + (distance * _r.direction))};
        glm::vec3 normal_vector{get_normal(schnitt_punkt)};
        return Hit{distance, is_hit, schnitt_punkt, normal_vector, this};
    }
    else
    {
        return Hit{};
    }
}

//old get_normal
glm::vec3 Box::get_normal(glm::vec3 const &coor_) const
{
    if (coor_.x == Approx(_minimum.x))
    {
        return glm::vec3{-1.0, 0.0, 0.0};
    }
    else if (coor_.x == Approx(_maximum.x))
    {
        return glm::vec3{1.0, 0.0, 0.0};
    }
    else if (coor_.y == Approx(_minimum.y))
    {
        return glm::vec3{0.0, -1.0, 0.0};
    }
    else if (coor_.y == Approx(_maximum.x))
    {
        return glm::vec3{0.0, 1.0, 0.0};
    }
    else if (coor_.z == Approx(_minimum.z))
    {
        return glm::vec3{0.0, 0.0, -1.0};
    }
    else if (coor_.z == Approx(_maximum.z))
    {
        return glm::vec3{0.0, 0.0, 1.0};
    }
}

glm::vec3 Box::get_vector_to_light(Hit const &_inter, Light const &_light) const
{
    return glm::normalize(glm::vec3{_inter.coor_ - _light._origin});
}