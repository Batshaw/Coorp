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

using namespace std;
using namespace glm;

class Shape
{
private:
public:
  Shape();
  Shape(string const &n, shared_ptr<Material> const &material);
  //ohne virtual wird der Destruktor die abgeleitene Klasse nicht aufgerufen
  ~Shape();

  virtual float area() = 0;
  virtual float volume() = 0;
  virtual ostream &print(ostream &os) const;

  //virtual bool intersect(Ray const& _r) const = 0;

  virtual bool intersect(Ray const &_r, float &_t) const = 0;
  virtual Hit intersection(Ray const &_r, float &_t) const = 0;
  virtual glm::vec3 get_normal(Hit const& _inter) const = 0;

  string name();
  // Color color();
  shared_ptr<Material> get_material_() const;

protected:
  string name_;
  // Color color_;
  shared_ptr<Material> material_;
};

ostream &operator<<(ostream &os, Shape const &s);

#endif //SHAPE_HPP
