#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/glm.hpp>
#include <string>
#include "color.hpp"

struct Light
{
    std::string _name;
    glm::vec3 _origin;
    Color _color;
    float _brightness;

    Light() : _name{"default Light"},
              _origin{10.0f, 20.0f, 10.0f},
              _color{1.0f, 1.0f, 1.0f},
              _brightness{2000.0f} {};

    Light(std::string const &name,
          glm::vec3 const &p,
          Color const &c,
          float m) : _name{name},
                     _origin{p},
                     _color{c},
                     _brightness{m}{}
};

#endif