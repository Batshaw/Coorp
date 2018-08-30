#include "box.hpp"
#include <cmath>
#include <memory>
#include "material.hpp"
#include "shape.hpp"

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

bool Box::intersect(Ray const& r, float& t){
    
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