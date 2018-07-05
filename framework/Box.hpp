#ifndef BOX_HPP
#define BOX_HPP

#include "Shape.hpp"
#include <glm/vec3.hpp>

class Box : public Shape
{
private:
  glm::vec3 _minimum;
  glm::vec3 _maximum;

public:
  Box();
  Box(glm::vec3 const &_pmin, glm::vec3 const &_pmax);

  Box(string const &n, Color const &col);
  Box(glm::vec3 const &_pmin, glm::vec3 const &_pmax, string const &n, Color const &col);
  ~Box();

  float length() const;
  float width() const;
  float height() const;

  float area() override;
  float volume() override;

  ostream &print(ostream &os) const override;

  bool intersect(Ray const &_r) const override;
  bool intersect(Ray const &_r, float &_t) const override;

  float set_max(float const &coor1, float const &coor2);
  float set_min(float const &coor1, float const &coor2);

  vec3 nearest_corner(vec3 const &min, vec3 const &max, vec3 const &origin) const;
  vec3 furthest_corner(vec3 const &min, vec3 const &max, vec3 const &origin) const;
  
  float nearest_komponent(float const &min, float const &max, float const &origin) const;
  float furthest_komponent(float const &min, float const &max, float const &origin) const;

  bool is_on_surface(vec3 const &p1, vec3 const &p2, vec3 const &input, float &distance) const;
};

#endif //BOX_HPP