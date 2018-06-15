#include "box.hpp"
#include <cmath>

// Konstruktor
Box::Box():
    min_{glm::vec3{0.0f}}, max_{glm::vec3{5.0f}}, Shape{}   {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max):
    min_{min}, max_{max}    {}

Box::Box(glm::vec3 const min, glm::vec3 const& max, std::string const& name):
    min_{min}, max_{max}, Shape{name}   {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max, Color const& color):
    min_{min}, max_{max}, Shape{color}   {}

Box::Box(glm::vec3 const min, glm::vec3 const& max, std::string const& name, Color const& color):
    min_{min}, max_{max}, Shape{name, color}   {}

// get-Methode
glm::vec3 getMin() const{
    return min_;
}
glm::vec3 getMax() const{
    return max_;
}

// area und volumen
float Box::area() const{
    float x = abs(max_.x - min_.x);
    float y = abs(max_.y - min_.y);
    float z = abs(max_.z - min_.z);
    return 2*(x*y + x*z + y*z);
}
float Box::volumen() const{
    float x = abs(max_.x - min_.x);
    float y = abs(max_.y - min_.y);
    float z = abs(max_.z - min_.z);
    return x*y*z;
}