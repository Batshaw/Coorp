#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include "color.hpp"
#include <ostream>
#include "material.hpp"
#include "ray.hpp"
#include "glm/vec3.hpp"
#include "hit.hpp"
#include <memory>

class Shape
{
public:
  Shape();
  /*Shape(std::string const& name);
        Shape(std::shared_ptr<Material> material);*/
  Shape(std::string const &name, std::shared_ptr<Material> const &material);
  Shape(std::string const &name, std::shared_ptr<Material> const &material, glm::mat4 const &worldTransform);
  virtual ~Shape();

  std::string get_name() const;
  Color get_color() const;
  std::shared_ptr<Material> get_material() const;
  glm::mat4 world_transformation() const;
  glm::mat4 world_transformation_inv() const;

  virtual float area() const = 0;
  virtual float volumen() const = 0;

  virtual bool intersect(Ray const &r, float &t) = 0;
  virtual Hit intersectHit(Ray const &ray) = 0;

  virtual std::ostream &print(std::ostream &os) const;

  void transform(glm::vec3 const &translation, glm::vec3 const &scaling, float angle, glm::vec3 const &rotation);
  void translate(glm::vec3 const &a);
  void scale(glm::vec3 const &b);
  void rotate(float rad, glm::vec3 const &c);
  void rotate_x(float rad);
  void rotate_y(float rad);
  void rotate_z(float rad);

protected:
  std::string name_;
  std::shared_ptr<Material> material_;

  glm::mat4 world_transformation_{1, 0, 0, 0,
                                  0, 1, 0, 0,
                                  0, 0, 1, 0,
                                  0, 0, 0, 1};

  glm::mat4 world_transformation_inv_{1, 0, 0, 0,
                                      0, 1, 0, 0,
                                      0, 0, 1, 0,
                                      0, 0, 0, 1};
};

std::ostream &operator<<(std::ostream &os, Shape const &s);

#endif //SHAPE_HPP