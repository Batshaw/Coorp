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


class Shape
{
private:
public:
  Shape();
  Shape(std::string const &n, std::shared_ptr<Material> const &material);
  
  Shape(std::string const &n, std::shared_ptr<Material> const &material, glm::mat4 const& world_trans_);
  //ohne virtual wird der Destruktor die abgeleitene Klasse nicht aufgerufen
  ~Shape();

  virtual float area() const = 0;
  virtual float volume() const = 0;
  virtual std::ostream &print(std::ostream &os) const;

  virtual bool intersect(Ray const& _r, float& _t) = 0 ;
  virtual Hit intersect_hit(Ray const &_r) = 0 ;

  std::string name() const;
  std::shared_ptr<Material> get_material_() const;

  //Transformation rechnen
  virtual void translate(glm::vec3 const &a_);
  virtual void scale(glm::vec3 const &b_);
  virtual void rotate(float rad_, glm::vec3 const &c_);
  virtual void rotate_x(float rad_);
  virtual void rotate_y(float rad_);
  virtual void rotate_z(float rad_);

protected:
  std::string name_;
  // Color color_;
  std::shared_ptr<Material> material_;
  glm::mat4 world_transformation_;
  glm::mat4 world_transformation_inv_;
};

std::ostream &operator<<(std::ostream &os, Shape const &s);

#endif //SHAPE_HPP
