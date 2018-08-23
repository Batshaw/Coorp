#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include <glm/vec3.hpp>
#include <iostream>
#include "color.hpp"
#include "Ray.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <memory>
#include "material.hpp"
#include "Hit.hpp"
#include "Light.hpp"

struct Hit;

class Shape
{
private:
public:
  Shape();
  Shape(std::string const &n, std::shared_ptr<Material> const &material);
  //ohne virtual wird der Destruktor die abgeleitene Klasse nicht aufgerufen
  ~Shape();

  virtual float area() const = 0;
  virtual float volume() const = 0;
  virtual std::ostream &print(std::ostream &os) const;

  //virtual bool intersect(Ray const& _r) const = 0;

  virtual bool intersect(Ray const &_r, float &_t) const = 0;
  virtual Hit intersection(Ray const &_r, float &_t) const = 0;
  virtual glm::vec3 get_normal(Hit const &_inter) const = 0;
  virtual glm::vec3 get_vector_to_light(Hit const &_inter, Light const &_light) const = 0;

  std::string name();
  // Color color();
  std::shared_ptr<Material> get_material_() const;

protected:
  std::string name_;
  // Color color_;
  std::shared_ptr<Material> material_;
};

std::ostream &operator<<(std::ostream &os, Shape const &s);

#endif //SHAPE_HPP
