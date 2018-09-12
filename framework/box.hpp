#ifndef BOX_HPP
#define BOX_HPP

#include <memory>
#include "shape.hpp"

#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>

class Box : public Shape
{
public:
  // Konstruktor
  Box();
  Box(glm::vec3 const &min, glm::vec3 const &max);
  Box(glm::vec3 const &min, glm::vec3 const &max, std::string const &name, std::shared_ptr<Material> const &material);
  ~Box();

  // Methode
  float area() const override;
  float volumen() const override;
  glm::vec3 getMin() const;
  glm::vec3 getMax() const;
  bool onSurface(glm::vec3 const &punkt) const;
  bool intersect(Ray const &r, float &t) const override;
  Hit intersectHit(Ray const &ray, float &t) const override;

  std::ostream &print(std::ostream &os) const override;

protected:
  glm::vec3 min_;
  glm::vec3 max_;
  glm::vec3 setMax(glm::vec3 const &coor1, glm::vec3 const &coor2) const;
  glm::vec3 setMin(glm::vec3 const &coor1, glm::vec3 const &coor2) const;
};

std::ostream &operator<<(std::ostream &os, Box const &b);

#endif //BOX_HPP
