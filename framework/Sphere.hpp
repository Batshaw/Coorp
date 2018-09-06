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
  Sphere(glm::vec3 const &_p, float _r, std::shared_ptr<Material> const &material, std::string const &_n);

  ~Sphere();
  glm::vec3 center() const;
  float radius() const;

  float area() const override;
  float volume() const override;

  std::ostream &print(std::ostream &os) const override;

  bool intersect(Ray const &_r, float &_t) override;
  Hit intersect_hit(Ray const &_r) override;

  glm::vec3 get_normal(glm::vec3 const &_cut) const;
  glm::vec3 get_vector_to_light(Hit const &_inter, Light const &_light) const;
};

#endif //SPHERE_HPP
