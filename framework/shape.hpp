#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <memory>
#include <ostream>
#include <string>
#include "color.hpp"
#include <ostream>
#include "material.hpp"
#include "ray.hpp"
#include "hit.hpp"

#define GLM_FORCE_RADIANS
#include "glm/vec3.hpp"
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

class Shape
{
public:
  Shape();
  Shape(std::string const &name, std::shared_ptr<Material> const &material);
  Shape(std::string const &name, std::shared_ptr<Material> const &material, glm::mat4 const &worldTransform);
  virtual ~Shape();

  //Public Methode
  std::string getName() const;
  std::shared_ptr<Material> getMaterial() const;
  glm::mat4 getMatrix() const;
  glm::mat4 getInverse() const;

  //Pure virtual Funktion
  virtual float area() const = 0;
  virtual float volumen() const = 0;
  virtual bool intersect(Ray const &r, float &t) const = 0;
  virtual Hit intersectHit(Ray const &ray, float &t) const = 0;
  virtual std::ostream &print(std::ostream &os) const;
  void transform(glm::mat4 const &matrix);

  glm::mat4 animation_matrix_{1.0f};

  //Alle Membervariable ist protected. Nur erreichbar von sich selbst und abgeleiten Klassen
protected:
  std::string name_;
  std::shared_ptr<Material> material_;
  glm::mat4 world_transformation_;
  glm::mat4 world_transformation_inv_;
};

std::ostream &operator<<(std::ostream &os, Shape const &s);

#endif //SHAPE_HPP
