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
  virtual Hit intersectHit(Ray const &ray, float& t) = 0;

  virtual std::ostream &print(std::ostream &os) const;

  void transform(glm::mat4 const& matrix);
  /*  glm::mat4 translate(glm::vec3 const &a);
  glm::mat4 scale(glm::vec3 const &b);
  glm::mat4 rotate(glm::vec3 const &c);
  glm::mat4 rotate_x(float rad);
  glm::mat4 rotate_y(float rad);
  glm::mat4 rotate_z(float rad);
 */

protected:
  std::string name_;
  std::shared_ptr<Material> material_;

  glm::mat4 world_transformation_{1, 0, 0, 0,
                                  0, 1, 0, 0,
                                  0, 0, 1, 0,
                                  0, 0, 0, 1};

  glm::mat4 world_transformation_inv_{glm::inverse(world_transformation_)};
};

std::ostream &operator<<(std::ostream &os, Shape const &s);

#endif //SHAPE_HPP
