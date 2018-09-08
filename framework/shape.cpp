#include "shape.hpp"
#include "glm/vec3.hpp"
#include <ostream>
#include <memory>

// Konstruktor
Shape::Shape():
    name_{"unknown"}   {}
/*Shape::Shape(std::string const& name):
    name_{name}, color_{Color(0.0f, 0.0f, 0.0f)}    {}
Shape::Shape(Color const& color):
    name_{"unknown"}, color_{color} {}*/
Shape::Shape(std::string const& name, std::shared_ptr<Material> const& material):
    name_{name}, material_{material}  {
        // std::cout<< "Constructor of Shape!"<< std::endl;
    }

    Shape::Shape(std::string const& name, std::shared_ptr<Material> const& material, glm::mat4 worldTransform):
        name_{name}, material_{material}, world_transformation_{worldTransform}, world_transformation_inv_{glm::inverse(worldTransform)} {}

// Destruktor (Aufgabe8):
Shape::~Shape() {
    // std::cout<< "Destruction of Shape!"<< std::endl;
}

// get-Methode
std::string Shape::getName() const{
    return name_;
}
std::shared_ptr<Material> Shape::getMaterial() const{
    return material_;
}
glm::mat4 Shape::getWorldMat() const{
    return world_transformation_;
}
glm::mat4 Shape::getWorldMatInv() const{
    return world_transformation_inv_;
}

// transform-Methode
void Shape::translate(glm::vec3 const& p){
    glm::mat4 transMat;
    transMat[0] = {1.0f, 0.0f, 0.0f, p.x};
    transMat[1] = {0.0f, 1.0f, 0.0f, p.y};
    transMat[2] = {0.0f, 0.0f, 1.0f, p.z};
    transMat[3] = {0.0f, 0.0f, 0.0f, 1.0f};
    world_transformation_ = transMat * world_transformation_;
    world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::scale(glm::vec3 const& p){
    glm::mat4 scaleMat;
    scaleMat[0] = {p.x, 0.0f, 0.0f, 0.0f};
    scaleMat[0] = {0.0f, p.y, 0.0f, 0.0f};
    scaleMat[0] = {0.0f, 0.0f, p.z, 0.0f};
    scaleMat[0] = {0.0f, 0.0f, 0.0f, 1.0f};
    world_transformation_ = scaleMat * world_transformation_;
    world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::rotate(float fi, glm::vec3 const& roVec){
    glm::mat4 rotMat;
    if(roVec.x == 1 && roVec.y == 0 && roVec.z == 0){ // rotate with X-vector
        rotMat[0] = {1.0f, 0.0f, 0.0f, 0.0f};
        rotMat[1] = {0.0f, cos(fi), -sin(fi), 0.0f};
        rotMat[2] = {0.0f, sin(fi), cos(fi), 0.0f};
        rotMat[3] = {0.0f, 0.0f, 0.0f, 1.0f};
    }
    else if(roVec.x == 0 && roVec.y == 1 && roVec.z == 0){ // rotate with Y-vector
        rotMat[0] = {cos(fi), 0.0f, sin(fi), 0.0f};
        rotMat[1] = {0.0f, 1.0f, 0.0f, 0.0f};
        rotMat[2] = {-sin(fi), 0.0f, cos(fi), 0.0f};
        rotMat[3] = {0.0f, 0.0f, 0.0f, 1.0f};
    }
    else if(roVec.x == 0 && roVec.y == 0 && roVec.z == 1){
        rotMat[0] = {cos(fi), -sin(fi), 0.0f, 0.0f};
        rotMat[1] = {sin(fi), cos(fi), 0.0f, 0.0f};
        rotMat[2] = {0.0f, 0.0f, 1.0f, 0.0f};
        rotMat[3] = {0.0f, 0.0f, 0.0f, 1.0f};
    }
    else std::cout<< "Rotate only with X, Y or Z vector!!!";
    world_transformation_ = rotMat * world_transformation_;
    world_transformation_inv_ = glm::inverse(world_transformation_);
}

std::ostream& Shape::print(std::ostream& os) const{
    os<< "The Shape: "<< name_ << " has color: "<< material_<< "\n";
    return os;
}
std::ostream& operator<<(std::ostream& os, Shape const& s){
    return s.print(os);
}