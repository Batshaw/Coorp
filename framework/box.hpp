#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>


class Box : public Shape{
    public:
        // Konstruktor
        Box();
        Box(glm::vec3 const& min, glm::vec3 const& max);
        Box(glm::vec3 const min, glm::vec3 const& max, std::string const& name);
        Box(glm::vec3 const& min, glm::vec3 const& max, Color const& color);
        Box(glm::vec3 const min, glm::vec3 const& max, std::string const& name, Color const& color);

        // Methode
        float area() const override;
        float volumen() const override;
        glm::vec3 getMax() const;
        glm::vec3 getMin() const;

    private:
        glm::vec3 min_;
        glm::vec3 max_;

};

#endif  //BOX_HPP