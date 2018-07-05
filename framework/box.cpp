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
    if(r.direction.x != 0){
        if(r.direction.x > 0){
            t = (min_.x - r.origin.x)/r.direction.x;
        }
        else t = (max_.x - r.origin.x)/r.direction.x;
        if(t > 0){
            schnittPunkt = r.origin + t*r.direction;
            std::cout<<schnittPunkt.x<< " "<< schnittPunkt.y<< " "<< schnittPunkt.z<< " \n";
            if(is_inBox(schnittPunkt)){
                result = true;
                std::cout<< "t = "<< t<< "\n";
            }
        }
    }
    if(r.direction.y != 0){
        if(r.direction.y > 0){
            t = (min_.y - r.origin.y)/r.direction.y;
        }
        else t = (max_.y - r.origin.y)/r.direction.y;
        if(t > 0){
            schnittPunkt = r.origin + t*r.direction;
            std::cout<<schnittPunkt.x<< " "<< schnittPunkt.y<< " "<< schnittPunkt.z<< " \n";
            if(is_inBox(schnittPunkt)){
                result = true;
                std::cout<< "t = "<< t<< "\n";
            }
        }
    }
    if(r.direction.z != 0){
        if(r.direction.z > 0){
            t = (min_.z - r.origin.z)/r.direction.z;
        }
        else t = (max_.z - r.origin.z)/r.direction.z;
        if(t > 0){
            schnittPunkt = r.origin + t*r.direction;
            std::cout<<schnittPunkt.x<< " "<< schnittPunkt.y<< " "<< schnittPunkt.z<< " \n";
            if(is_inBox(schnittPunkt)){
                result = true;
                std::cout<< "t = "<< t<< "\n";
            }
        }
    }
    return result;
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