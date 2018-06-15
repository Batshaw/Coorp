#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>


class Box: public Shape{
    public:

        Box();
        Box(glm::vec3 const& min, glm::vec3 const& max);
        float area() const override;
        float volumen() const override;
        glm::vec3 const& getMax() const;
        glm::vec3 const& getMin() const;

    private:
        glm::vec3 min_;
        glm::vec3 max_;

};

#endif  //BOX_HPP