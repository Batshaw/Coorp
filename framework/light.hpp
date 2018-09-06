#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/glm.hpp>
#include <string>
#include "color.hpp"

struct Light
{
    std::string name_;
    glm::vec3 origin_;
    Color color_;
    float brightness_;

    Light() : name_{"default Light"},
              origin_{10.0f, 20.0f, 10.0f},
              color_{1.0f, 1.0f, 1.0f},
              brightness_{1.0f} {};

    Light(std::string const &name,
          glm::vec3 const &p,
          Color const &c,
          float m) : name_{name},
                     origin_{p},
                     color_{c},
                     brightness_{m}{}
};

#endif
