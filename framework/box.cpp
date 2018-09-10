#define CATCH_CONFIG_RUNNER

#include "box.hpp"
#include "scene.hpp"
#include "renderer.hpp"
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

bool Box::intersect(Ray const& ray, float& t){
    bool result = false;
    glm::vec3 schnittPunkt;
    // if(ray.direction.x != 0){
    //     if(ray.direction.x > 0){
    //         t = (min_.x - ray.origin.x)/ray.direction.x;
    //     }
    //     else t = (max_.x - ray.origin.x)/ray.direction.x;
    //     if(t > 0){
    //         schnittPunkt = ray.origin + t*ray.direction;
    //         // std::cout<<schnittPunkt.x<< " "<< schnittPunkt.y<< " "<< schnittPunkt.z<< " \n";
    //         if(is_inBox(schnittPunkt)){
    //             result = true;
    //             // std::cout<< "t = "<< t<< "\n";
    //         }
    //     }
    // }
    // if(ray.direction.y != 0){
    //     if(ray.direction.y > 0){
    //         t = (min_.y - ray.origin.y)/ray.direction.y;
    //     }
    //     else t = (max_.y - ray.origin.y)/ray.direction.y;
    //     if(t > 0){
    //         schnittPunkt = ray.origin + t*ray.direction;
    //         // std::cout<<schnittPunkt.x<< " "<< schnittPunkt.y<< " "<< schnittPunkt.z<< " \n";
    //         if(is_inBox(schnittPunkt)){
    //             result = true;
    //             // std::cout<< "t = "<< t<< "\n";
    //         }
    //     }
    // }
    // if(ray.direction.z != 0){
    //     if(ray.direction.z > 0){
    //         t = (min_.z - ray.origin.z)/ray.direction.z;
    //     }
    //     else t = (max_.z - ray.origin.z)/ray.direction.z;
    //     if(t > 0){
    //         schnittPunkt = ray.origin + t*ray.direction;
    //         // std::cout<<schnittPunkt.x<< " "<< schnittPunkt.y<< " "<< schnittPunkt.z<< " \n";
    //         if(is_inBox(schnittPunkt)){
    //             result = true;
    //             // std::cout<< "t = "<< t<< "\n";
    //         }
    //     }
    // }
    // return result;
    if(ray.direction.x == 0 && ray.direction.y == 0 && ray.direction.z == 0){
        std::cout<< "add another direction (!= 0)";
    }
    else{
        std::vector<float> distanceVec;
        float minX = (min_.x - ray.origin.x)/ray.direction.x;
        float maxX = (max_.x - ray.origin.x)/ray.direction.x;
        distanceVec.push_back(minX);
        distanceVec.push_back(maxX);

        float minY = (min_.y - ray.origin.y)/ray.direction.y;
        float maxY = (max_.y - ray.origin.y)/ray.direction.y;
        distanceVec.push_back(minY);
        distanceVec.push_back(maxY);

        float minZ = (min_.z - ray.origin.z)/ray.direction.z;
        float maxZ = (max_.z - ray.origin.z)/ray.direction.z;
        distanceVec.push_back(minZ);
        distanceVec.push_back(maxZ);

        std::sort(distanceVec.begin(), distanceVec.end());

        for(auto i : distanceVec){
            if(!std::isinf(i)){
                schnittPunkt = ray.origin + (i * ray.direction);
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

Hit Box::intersectHit(Ray const& ray, float& t){
    // float t;
    glm::vec3 schnittPunkt;
    glm::vec3 normalVec;
    Ray transformedRay{transformRay(getWorldMatInv(), ray)};
    // Ray transformedRay{ray};
    bool isHit = intersect(ray, t);
    // if(transformedRay.direction.x == 0 && transformedRay.direction.y == 0 && transformedRay.direction.z == 0){
    //     std::cout<< "add another direction (!= 0)";
    // }
    // else{
    //     std::vector<float> distanceVec;
    //     float minX = (min_.x - transformedRay.origin.x)/transformedRay.direction.x;
    //     float maxX = (max_.x - transformedRay.origin.x)/transformedRay.direction.x;
    //     distanceVec.push_back(minX);
    //     distanceVec.push_back(maxX);

    //     float minY = (min_.y - transformedRay.origin.y)/transformedRay.direction.y;
    //     float maxY = (max_.y - transformedRay.origin.y)/transformedRay.direction.y;
    //     distanceVec.push_back(minY);
    //     distanceVec.push_back(maxY);

    //     float minZ = (min_.z - transformedRay.origin.z)/transformedRay.direction.z;
    //     float maxZ = (max_.z - transformedRay.origin.z)/transformedRay.direction.z;
    //     distanceVec.push_back(minZ);
    //     distanceVec.push_back(maxZ);

    //     std::sort(distanceVec.begin(), distanceVec.end());

    //     for(auto i : distanceVec){
    //         if(!std::isinf(i)){
    //             schnittPunkt = transformedRay.origin + (i * transformedRay.direction);
    //             if((schnittPunkt.x <= max_.x && schnittPunkt.x >= min_.x)
    //                 && (schnittPunkt.y <= max_.y && schnittPunkt.y >= min_.y)
    //                 && (schnittPunkt.z <= max_.z && schnittPunkt.z >= min_.z)){
    //                     t = i;
    //                     isHit = true;
    //                 }
    //         }
    //     }
    // }
    schnittPunkt = transformedRay.origin + (t * transformedRay.direction);
    if(isHit == true){
        // schnittPunkt = transformedRay.origin + t*transformedRay.direction;
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
        schnittPunkt = glm::vec3(getWorldMat()*glm::vec4(schnittPunkt, 1.0f));
        normalVec = glm::vec3(glm::normalize(glm::transpose(getWorldMatInv())*glm::vec4(normalVec, 0.0f)));
        glm::vec3 vector = schnittPunkt - transformedRay.origin;
        float d = std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2) + std::pow(vector.z, 2));
        return Hit{true, d, this, glm::normalize(normalVec), schnittPunkt};
    }

    return Hit{};
}

// Hit Box::intersectHit(Ray const& ray, float& t){
//     // float t;
//     glm::vec3 schnittPunkt;
//     glm::vec3 normalVec;
//     Ray transformedRay{transformRay(getWorldMatInv(), ray)};
//     bool isHit = false;
//     float minX, minY, minZ;
//     float maxX, maxY, maxZ;
//     // if(transformedRay.direction.x == 0 && transformedRay.direction.y == 0 && transformedRay.direction.z == 0){
//     //     std::cout<< "add another direction (!= 0)";
//     // }
//     // else{
//     std::vector<float> distanceVec;
//     if(transformedRay.direction.x >= 0){
//         minX = (min_.x - transformedRay.origin.x)/transformedRay.direction.x;
//         maxX = (max_.x - transformedRay.origin.x)/transformedRay.direction.x;
//         distanceVec.push_back(minX);
//         distanceVec.push_back(maxX);
//     }
//     else{
//         minX = (max_.x - transformedRay.origin.x)/transformedRay.direction.x;
//         maxX = (min_.x - transformedRay.origin.x)/transformedRay.direction.x;
//         distanceVec.push_back(minX);
//         distanceVec.push_back(maxX);
//     }

//     if(transformedRay.direction.y >= 0){
//         minY = (min_.y - transformedRay.origin.y)/transformedRay.direction.y;
//         maxY = (max_.y - transformedRay.origin.y)/transformedRay.direction.y;
//         distanceVec.push_back(minY);
//         distanceVec.push_back(maxY);
//     }
//     else{
//         minY = (max_.y - transformedRay.origin.y)/transformedRay.direction.y;
//         maxY = (min_.y - transformedRay.origin.y)/transformedRay.direction.y;
//         distanceVec.push_back(minY);
//         distanceVec.push_back(maxY);
//     }

//     if(transformedRay.direction.z >= 0){
//         minZ = (min_.z - transformedRay.origin.z)/transformedRay.direction.z;
//         maxZ = (max_.z - transformedRay.origin.z)/transformedRay.direction.z;
//         distanceVec.push_back(minZ);
//         distanceVec.push_back(maxZ);
//     }
//     else{
//         minZ = (max_.z - transformedRay.origin.z)/transformedRay.direction.z;
//         maxZ = (min_.z - transformedRay.origin.z)/transformedRay.direction.z;
//         distanceVec.push_back(minZ);
//         distanceVec.push_back(maxZ);
//     }  

//     std::sort(distanceVec.begin(), distanceVec.end());
//     // for(auto i : distanceVec){
//     //         if(!std::isinf(i)){
//     //             schnittPunkt = transformedRay.origin + (i * transformedRay.direction);
//     //             if((schnittPunkt.x <= max_.x && schnittPunkt.x >= min_.x)
//     //                 && (schnittPunkt.y <= max_.y && schnittPunkt.y >= min_.y)
//     //                 && (schnittPunkt.z <= max_.z && schnittPunkt.z >= min_.z)){
//     //                     t = i;
//     //                     isHit = true;
//     //             }
//     //         }
//     // }

//     float bigDistance;
//     float smallDistance;
//     int faceIn;
//     int faceOut;
//     if(minX > minY){
//         bigDistance = minX;
//         if(transformedRay.direction.x >= 0.0f){
//             faceIn = 0;                     //Number of the faces of box, number 0 is the face with -x in the normalVector
//         }
//         else faceIn = 3;
//     }
//     else{
//         bigDistance = minY;
//         if(transformedRay.direction.y >= 0.0f){
//             faceIn = 1;                     //Number of the faces of box, number 0 is the face with -x in the normalVector
//         }
//         else faceIn = 4;
//     }
//     if(minZ > bigDistance){
//         bigDistance = minZ;
//         if(transformedRay.direction.z >= 0.0f){
//             faceIn = 2;                     //Number of the faces of box, number 0 is the face with -x in the normalVector
//         }
//         else faceIn = 5;
//     }

//     if(maxX < maxY){
//         smallDistance = maxX;
//         if(transformedRay.direction.x >= 0.0f){
//             faceOut = 3;                     //Number of the faces of box, number 0 is the face with -x in the normalVector
//         }
//         else faceIn = 0;
//     }
//     else{
//         smallDistance = maxY;
//         if(transformedRay.direction.y >= 0.0f){
//             faceIn = 4;                     //Number of the faces of box, number 0 is the face with -x in the normalVector
//         }
//         else faceIn = 1;
//     }
//     if(minZ < smallDistance){
//         smallDistance = maxZ;
//         if(transformedRay.direction.z >= 0){
//             faceIn = 5;                     //Number of the faces of box, number 0 is the face with -x in the normalVector
//         }
//         else faceIn = 2;
//     }

//     if(bigDistance < smallDistance && smallDistance > 10e-6){
//         isHit = true;
//     }
//     // isHit = bigDistance < smallDistance && smallDistance > 10e-6;
//     // for(auto i : distanceVec){
//     //         if(!std::isinf(i)){
//     //             schnittPunkt = transformedRay.origin + (i * transformedRay.direction);
//     //             if((schnittPunkt.x <= max_.x && schnittPunkt.x >= min_.x)
//     //                 && (schnittPunkt.y <= max_.y && schnittPunkt.y >= min_.y)
//     //                 && (schnittPunkt.z <= max_.z && schnittPunkt.z >= min_.z)){
//     //                     t = i;
//     //                     isHit = true;
//     //             }
//     //         }
//     // }

//     if(isHit == true){
//         if(bigDistance > 10e-6){
//             t = bigDistance;
//             normalVec = getNormal(faceIn);
//         }
//         else{
//             t = smallDistance;
//             normalVec = getNormal(faceOut);
//         }

//         schnittPunkt = transformedRay.origin + t*transformedRay.direction;
//         // if(schnittPunkt.x == Approx(min_.x)){
//         //     normalVec = glm::vec3{-1.0f, 0.0f, 0.0f};
//         // }
//         // if(schnittPunkt.y == Approx(min_.y)){
//         //     normalVec = glm::vec3{0.0f, -1.0f, 0.0f};
//         // }
//         // if(schnittPunkt.z == Approx(min_.z)){
//         //     normalVec = glm::vec3{0.0f, 0.0f, -1.0f};
//         // }
//         // if(schnittPunkt.x == Approx(max_.x)){
//         //     normalVec = glm::vec3{1.0f, 0.0f, 0.0f};
//         // }
//         // if(schnittPunkt.y == Approx(max_.y)){
//         //     normalVec = glm::vec3{0.0f, 1.0f, 0.0f};
//         // }
//         // if(schnittPunkt.z == Approx(max_.z)){
//         //     normalVec = glm::vec3{0.0f, 0.0f, 1.0f};
//         // }
//         // schnittPunkt = glm::vec3(getWorldMat()*glm::vec4(schnittPunkt, 1.0f));
//         // normalVec = glm::vec3(glm::normalize(glm::transpose(getWorldMatInv())*glm::vec4(normalVec, 0.0f)));
//         return Hit{true, t, this, glm::normalize(normalVec), schnittPunkt};
//     }

//     return Hit{};
// }

glm::vec3 Box::getNormal(int face){
    switch(face){
        case 0: return glm::vec3{1.0f, 0.0f, 0.0f};
        case 1: return glm::vec3{0.0f, 1.0f, 0.0f};
        case 2: return glm::vec3{0.0f, 0.0f, 1.0f};
        case 3: return glm::vec3{-1.0f, 0.0f, 0.0f};
        case 4: return glm::vec3{0.0f, -1.0f, 0.0f};
        case 5: return glm::vec3{0.0f, 0.0f, -1.0f};
    }
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