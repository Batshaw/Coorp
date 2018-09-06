#define CATCH_CONFIG_RUNNER

#include "box.hpp"
#include <cmath>
#include <memory>
#include <vector>
#include <algorithm>
#include <limits>
#include <catch-1.5/catch.hpp>

// Konstruktor
Box::Box():
    Shape{}, min_{glm::vec3{0.0f}}, max_{glm::vec3{5.0f}}   {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max):
    min_{min}, max_{max}    {}

/*Box::Box(glm::vec3 const min, glm::vec3 const& max, std::string const& name):
    min_{min}, max_{max}, Shape{name}   {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max, Color const& color):
    min_{min}, max_{max}, Shape{color}   {}*/

Box::Box(glm::vec3 const min, glm::vec3 const& max, std::string const& name, std::shared_ptr<Material> const& material):
    Shape{name, material}, min_{min}, max_{max}   {}

Box::~Box()   {
    std::cout<< "Destructor of Sphere!"<< std::endl;
}

// get-Methode
glm::vec3 Box::getMin() const{
    return min_;
}
glm::vec3 Box::getMax() const{
    return max_;
}

// area und volumen
float Box::area() const{
    float a = fabs(max_.x - min_.x);
    float b = fabs(max_.y - min_.y);
    float c = fabs(max_.z - min_.z);
    return 2*(a*b + a*c + b*c);
}
float Box::volumen() const{
    float x = fabs(max_.x - min_.x);
    float y = fabs(max_.y - min_.y);
    float z = fabs(max_.z - min_.z);
    return x*y*z;
}

// in Box???
bool Box::is_inBox(glm::vec3 const& punkt){
    if(min_.x <= punkt.x && punkt.x <= max_.x && min_.y <= punkt.y && punkt.y <= max_.y && min_.z <= punkt.z && punkt.z <= max_.z){
        return true;
    }
    else return false;
}

bool Box::intersect(Ray const& r, float& t){
    bool result = false;
    glm::vec3 schnittPunkt;
    // if(r.direction.x != 0){
    //     if(r.direction.x > 0){
    //         t = (min_.x - r.origin.x)/r.direction.x;
    //     }
    //     else t = (max_.x - r.origin.x)/r.direction.x;
    //     if(t > 0){
    //         schnittPunkt = r.origin + t*r.direction;
    //         // std::cout<<schnittPunkt.x<< " "<< schnittPunkt.y<< " "<< schnittPunkt.z<< " \n";
    //         if(is_inBox(schnittPunkt)){
    //             result = true;
    //             // std::cout<< "t = "<< t<< "\n";
    //         }
    //     }
    // }
    // if(r.direction.y != 0){
    //     if(r.direction.y > 0){
    //         t = (min_.y - r.origin.y)/r.direction.y;
    //     }
    //     else t = (max_.y - r.origin.y)/r.direction.y;
    //     if(t > 0){
    //         schnittPunkt = r.origin + t*r.direction;
    //         // std::cout<<schnittPunkt.x<< " "<< schnittPunkt.y<< " "<< schnittPunkt.z<< " \n";
    //         if(is_inBox(schnittPunkt)){
    //             result = true;
    //             // std::cout<< "t = "<< t<< "\n";
    //         }
    //     }
    // }
    // if(r.direction.z != 0){
    //     if(r.direction.z > 0){
    //         t = (min_.z - r.origin.z)/r.direction.z;
    //     }
    //     else t = (max_.z - r.origin.z)/r.direction.z;
    //     if(t > 0){
    //         schnittPunkt = r.origin + t*r.direction;
    //         // std::cout<<schnittPunkt.x<< " "<< schnittPunkt.y<< " "<< schnittPunkt.z<< " \n";
    //         if(is_inBox(schnittPunkt)){
    //             result = true;
    //             // std::cout<< "t = "<< t<< "\n";
    //         }
    //     }
    // }
    // return result;
    if(r.direction.x == 0 && r.direction.y == 0 && r.direction.z == 0){
        std::cout<< "add another direction (!= 0)";
    }
    else{
        std::vector<float> distanceVec;
        float minX = (min_.x - r.origin.x)/r.direction.x;
        float maxX = (max_.x - r.origin.x)/r.direction.x;
        distanceVec.push_back(minX);
        distanceVec.push_back(maxX);

        float minY = (min_.y - r.origin.y)/r.direction.y;
        float maxY = (max_.y - r.origin.y)/r.direction.y;
        distanceVec.push_back(minY);
        distanceVec.push_back(maxY);

        float minZ = (min_.z - r.origin.z)/r.direction.z;
        float maxZ = (max_.z - r.origin.z)/r.direction.z;
        distanceVec.push_back(minZ);
        distanceVec.push_back(maxZ);

        std::sort(distanceVec.begin(), distanceVec.end());

        for(auto i : distanceVec){
            if(!std::isinf(i)){
                schnittPunkt = r.origin + (i * r.direction);
                if((schnittPunkt.x <= max_.x && schnittPunkt.x >= min_.x)
                    && (schnittPunkt.y <= max_.y && schnittPunkt.y >= min_.y)
                    && (schnittPunkt.z <= max_.z && schnittPunkt.z >= min_.z)){
                        t = i;
                        result = true;
                        return result;
                    }
            }
        }

    }
    return result;
}

Hit Box::intersectHit(Ray const& ray){
    float t;
    glm::vec3 schnittPunkt;
    glm::vec3 normalVec;
    bool isHit = intersect(ray, t);
    schnittPunkt = ray.origin + (t * ray.direction);
    if(isHit == true){
        // schnittPunkt = ray.origin + t*ray.direction;
        if(schnittPunkt.x == Approx(min_.x)){
            normalVec = glm::vec3{-1.0f, 0.0f, 0.0f};
        }
        if(schnittPunkt.y == Approx(min_.y)){
            normalVec = glm::vec3{0.0f, -1.0f, 0.0f};
        }
        if(schnittPunkt.z == Approx(min_.z)){
            normalVec = glm::vec3{0.0f, 0.0f, -1.0f};
        }
        if(schnittPunkt.x == Approx(max_.x)){
            normalVec = glm::vec3{1.0f, 0.0f, 0.0f};
        }
        if(schnittPunkt.y == Approx(max_.y)){
            normalVec = glm::vec3{0.0f, 1.0f, 0.0f};
        }
        if(schnittPunkt.z == Approx(max_.z)){
            normalVec = glm::vec3{0.0f, 0.0f, 1.0f};
        }
        return Hit{true, t, this, glm::normalize(normalVec), schnittPunkt};
    }

    return Hit{};
}

// print-Methode
std::ostream& Box::print(std::ostream& os) const{
    Shape::print(os);
    os<< "MaxPoint of the Box is: ("<< max_.x<< ", "<< max_.y<< ", "<<
    max_.z<< ").\n";
    os<< "MinPoint of the Box is: ("<< min_.x<< ", "<< min_.y<< ", "<<
    min_.z<< ")."<< std::endl;
    return os;
}
std::ostream& operator<<(std::ostream& os, Box const& b){
    return b.print(os);
}