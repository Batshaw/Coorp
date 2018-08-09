#include <glm/glm.hpp>
#include <string>
#include "color.hpp"

struct Light
{
    std::string _name;
    glm::vec3 _origin;
    Color _color;
    float _brightness;

    Light(std::string const &name, glm::vec3 const &p, Color c, float m) : _name{name},
                                                                           _origin{p},
                                                                           _color{c},
                                                                           _brightness{m}
    {
    }
};