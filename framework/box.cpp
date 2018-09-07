#define CATCH_CONFIG_RUNNER

#include "box.hpp"
#include <cmath>
#include <memory>
#include <vector>
#include <algorithm>
#include <limits>
#include <catch-1.5/catch.hpp>
#include "scene.hpp"

// Konstruktor
Box::Box() : Shape{}, min_{glm::vec3{0.0f}}, max_{glm::vec3{5.0f}} {}

Box::Box(glm::vec3 const &min, glm::vec3 const &max) : min_{set_min(min, max)},
                                                       max_{set_max(min, max)} {};

Box::Box(glm::vec3 const &min, glm::vec3 const &max, std::string const &name, std::shared_ptr<Material> const &material) : Shape{name, material},
                                                                                                                           min_{set_min(min, max)},
                                                                                                                           max_{set_max(min, max)} {};

Box::~Box(){};

glm::vec3 Box::set_max(glm::vec3 coor1, glm::vec3 coor2) const
{
    float x = std::max(coor1.x, coor2.x);
    float y = std::max(coor1.y, coor2.y);
    float z = std::max(coor1.z, coor2.z);

    return glm::vec3{x, y, z};
}

glm::vec3 Box::set_min(glm::vec3 coor1, glm::vec3 coor2) const
{
    float x = std::min(coor1.x, coor2.x);
    float y = std::min(coor1.y, coor2.y);
    float z = std::min(coor1.z, coor2.z);

    return glm::vec3{x, y, z};
}

// get-Methode
glm::vec3 Box::getMin() const
{
    return min_;
}
glm::vec3 Box::getMax() const
{
    return max_;
}

// area und volumen
float Box::area() const
{
    float a = std::fabs(max_.x - min_.x);
    float b = std::fabs(max_.y - min_.y);
    float c = std::fabs(max_.z - min_.z);
    return 2 * (a * b + a * c + b * c);
}
float Box::volumen() const
{
    float x = std::fabs(max_.x - min_.x);
    float y = std::fabs(max_.y - min_.y);
    float z = std::fabs(max_.z - min_.z);
    return x * y * z;
}

// in Box???
bool Box::is_inBox(glm::vec3 const &punkt)
{
    if (min_.x <= punkt.x && punkt.x <= max_.x && min_.y <= punkt.y && punkt.y <= max_.y && min_.z <= punkt.z && punkt.z <= max_.z)
    {
        return true;
    }
    else
        return false;
}

bool Box::intersect(Ray const &r, float &t)
{
    bool result = false;
    glm::vec3 schnittPunkt;

    if (r.direction_.x == 0 && r.direction_.y == 0 && r.direction_.z == 0)
    {
        std::cout << "add another direction (!= 0)";
    }
    else
    {
        std::vector<float> distanceVec;
        float minX = (min_.x - r.origin_.x) / r.direction_.x;
        float maxX = (max_.x - r.origin_.x) / r.direction_.x;
        distanceVec.push_back(minX);
        distanceVec.push_back(maxX);

        float minY = (min_.y - r.origin_.y) / r.direction_.y;
        float maxY = (max_.y - r.origin_.y) / r.direction_.y;
        distanceVec.push_back(minY);
        distanceVec.push_back(maxY);

        float minZ = (min_.z - r.origin_.z) / r.direction_.z;
        float maxZ = (max_.z - r.origin_.z) / r.direction_.z;
        distanceVec.push_back(minZ);
        distanceVec.push_back(maxZ);

        std::sort(distanceVec.begin(), distanceVec.end());

        for (auto i : distanceVec)
        {
            if (!std::isinf(i))
            {
                schnittPunkt = r.origin_ + (i * r.direction_);
                if ((schnittPunkt.x <= max_.x && schnittPunkt.x >= min_.x) && (schnittPunkt.y <= max_.y && schnittPunkt.y >= min_.y) && (schnittPunkt.z <= max_.z && schnittPunkt.z >= min_.z))
                {
                    t = i;
                    result = true;
                    return result;
                }
            }
        }
    }
    return result;
}

Hit Box::intersectHit(Ray const &ray)
{
    float t;

    //Ray transform_ray = ray;
    Ray transform_ray{transformRay(world_transformation_, ray)};

    bool isHit = intersect(transform_ray, t);

    //Normal vector mit transformierte Strahl finden
    glm::vec3 raw_normal;
    glm::vec3 raw_point;
    if (isHit == true)
    {
        //Schnittpunkt mit transformierte Strahl finden
        raw_point = transform_ray.origin_ + (t * transform_ray.direction_);

        if (raw_point.x == Approx(min_.x))
        {
            raw_normal = glm::vec3{-1.0f, 0.0f, 0.0f};
        }
        if (raw_point.y == Approx(min_.y))
        {
            raw_normal = glm::vec3{0.0f, -1.0f, 0.0f};
        }
        if (raw_point.z == Approx(min_.z))
        {
            raw_normal = glm::vec3{0.0f, 0.0f, -1.0f};
        }
        if (raw_point.x == Approx(max_.x))
        {
            raw_normal = glm::vec3{1.0f, 0.0f, 0.0f};
        }
        if (raw_point.y == Approx(max_.y))
        {
            raw_normal = glm::vec3{0.0f, 1.0f, 0.0f};
        }
        if (raw_point.z == Approx(max_.z))
        {
            raw_normal = glm::vec3{0.0f, 0.0f, 1.0f};
        }

        glm::vec4 transformed_point = glm::transpose(world_transformation_inv_) * glm::vec4{raw_point, 1.0f};
        glm::vec3 schnittPunkt{transformed_point};

        glm::vec4 transformed_normal = glm::transpose(world_transformation_inv_) * glm::vec4{raw_normal, 1.0f};
        glm::vec3 normalVec{transformed_normal};

        return Hit{true, t, this, glm::normalize(raw_normal), raw_point};
    }

    return Hit{};
}

// print-Methode
std::ostream &Box::print(std::ostream &os) const
{
    Shape::print(os);
    os << "MaxPoint of the Box is: (" << max_.x << ", " << max_.y << ", " << max_.z << ").\n";
    os << "MinPoint of the Box is: (" << min_.x << ", " << min_.y << ", " << min_.z << ")." << std::endl;
    return os;
}
std::ostream &operator<<(std::ostream &os, Box const &b)
{
    return b.print(os);
}