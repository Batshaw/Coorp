#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Shape.hpp"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include "material.hpp"

class Sphere : public Shape
{
private:
  glm::vec3 _mpunkt;
  float _radius;

public:
  Sphere();

  Sphere(glm::vec3 const &_p, float _r = 1.0);
  Sphere(float _x, float _y, float _z, float _r = 1.0);
  Sphere(glm::vec3 const &_p, float _r, std::shared_ptr<Material> const &material, string const &_n);

  ~Sphere();

  float radius() const;

  float area() override;
  float volume() override;

  ostream &print(ostream &os) const override;

  //bool intersect(Ray const& _r) const override;
  bool intersect(Ray const &_r, float &_t) const override;
  Hit intersection(Ray const &_r, float &_t) const override;
  glm::vec3 get_normal(Hit const &hit) const;
};

#endif //SPHERE_HPP
