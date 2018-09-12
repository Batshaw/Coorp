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

Box::Box(glm::vec3 const &min, glm::vec3 const &max) : Shape{},
                                                       min_{setMin(min, max)},
                                                       max_{setMax(min, max)} {};

Box::Box(glm::vec3 const &min, glm::vec3 const &max, std::string const &name, std::shared_ptr<Material> const &material) : Shape{name, material},
                                                                                                                           min_{setMin(min, max)},
                                                                                                                           max_{setMax(min, max)} {};

Box::~Box(){};

glm::vec3 Box::setMax(glm::vec3 const &coor1, glm::vec3 const &coor2) const
{
    float x = std::max(coor1.x, coor2.x);
    float y = std::max(coor1.y, coor2.y);
    float z = std::max(coor1.z, coor2.z);

    return glm::vec3{x, y, z};
}

glm::vec3 Box::setMin(glm::vec3 const &coor1, glm::vec3 const &coor2) const
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
bool Box::onSurface(glm::vec3 const &punkt) const
{
    if (min_.x <= punkt.x && punkt.x <= max_.x && min_.y <= punkt.y && punkt.y <= max_.y && min_.z <= punkt.z && punkt.z <= max_.z)
    {
        return true;
    }
    else
        return false;
}

bool Box::intersect(Ray const &ray, float &t) const
{
    bool result = false;
    glm::vec3 schnittPunkt;
    if (ray.direction_.x == 0 && ray.direction_.y == 0 && ray.direction_.z == 0)
    {
        std::cout << "add another direction_ (!= 0)";
    }
    else
    {
        std::vector<float> distanceVec;
        float minX = (min_.x - ray.origin_.x) / ray.direction_.x;
        float maxX = (max_.x - ray.origin_.x) / ray.direction_.x;
        distanceVec.push_back(minX);
        distanceVec.push_back(maxX);

        float minY = (min_.y - ray.origin_.y) / ray.direction_.y;
        float maxY = (max_.y - ray.origin_.y) / ray.direction_.y;
        distanceVec.push_back(minY);
        distanceVec.push_back(maxY);

        float minZ = (min_.z - ray.origin_.z) / ray.direction_.z;
        float maxZ = (max_.z - ray.origin_.z) / ray.direction_.z;
        distanceVec.push_back(minZ);
        distanceVec.push_back(maxZ);

        std::sort(distanceVec.begin(), distanceVec.end());

        for (auto i : distanceVec)
        {
            if (!std::isinf(i))
            {
                schnittPunkt = ray.origin_ + (i * ray.direction_);
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

Hit Box::intersectHit(Ray const &ray, float &t) const
{
    // float t;
    glm::vec3 schnittPunkt;
    glm::vec3 normalVec;
    Ray transformedRay{transformRay(world_transformation_inv_, ray)};
    bool isHit = intersect(transformedRay, t);
    schnittPunkt = transformedRay.origin_ + (t * transformedRay.direction_);
    if (isHit == true)
    {
        // schnittPunkt = transformedRay.origin_ + t*transformedRay.direction_;
        if (schnittPunkt.x == Approx(min_.x))
        {
            normalVec = glm::vec3{-1.0f, 0.0f, 0.0f};
        }
        if (schnittPunkt.y == Approx(min_.y))
        {
            normalVec = glm::vec3{0.0f, -1.0f, 0.0f};
        }
        if (schnittPunkt.z == Approx(min_.z))
        {
            normalVec = glm::vec3{0.0f, 0.0f, -1.0f};
        }
        if (schnittPunkt.x == Approx(max_.x))
        {
            normalVec = glm::vec3{1.0f, 0.0f, 0.0f};
        }
        if (schnittPunkt.y == Approx(max_.y))
        {
            normalVec = glm::vec3{0.0f, 1.0f, 0.0f};
        }
        if (schnittPunkt.z == Approx(max_.z))
        {
            normalVec = glm::vec3{0.0f, 0.0f, 1.0f};
        }
        schnittPunkt = glm::vec3(world_transformation_ * glm::vec4(schnittPunkt, 1.0f));
        normalVec = glm::vec3(glm::normalize(glm::transpose(world_transformation_) * glm::vec4(normalVec, 0.0f)));
        glm::vec3 vector = schnittPunkt - transformedRay.origin_;
        float d = std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2) + std::pow(vector.z, 2));
        return Hit{true, d, this, glm::normalize(normalVec), schnittPunkt};
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