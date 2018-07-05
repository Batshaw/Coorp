#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Shape.hpp"
#include <glm/vec3.hpp>


class Sphere : public Shape
{
private:
  glm::vec3 _mpunkt;
  float _radius;

public:
  Sphere();

  Sphere(glm::vec3 const &_p, float _r = 1.0);
  Sphere(float _x, float _y, float _z, float _r = 1.0);
  Sphere(glm::vec3 const &_p, float _r, Color const &_col, string const &_n);

  ~Sphere();

  float radius() const;

  float area() override;
  float volume() override;

  ostream &print(ostream &os) const override;

  bool intersect(Ray const& _r) const override;
  bool intersect(Ray const& _r, float& _t) const override;
};

#endif //SPHERE_HPP
