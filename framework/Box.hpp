#ifndef BOX_HPP
#define BOX_HPP

#include "Shape.hpp"
#include <glm/vec3.hpp>
#include "material.hpp"

class Box : public Shape
{
private:
  glm::vec3 _minimum;
  glm::vec3 _maximum;

public:
  Box();
  Box(glm::vec3 const &_pmin, glm::vec3 const &_pmax);

  Box(std::string const &n, std::shared_ptr<Material> const &material);
  Box(glm::vec3 const &_pmin, glm::vec3 const &_pmax, std::string const &n, std::shared_ptr<Material> const &material);
  ~Box();

  float length() const;
  float width() const;
  float height() const;

  float area() override;
  float volume() override;

  ostream &print(std::ostream &os) const override;

  //bool intersect(Ray const &_r) const override;
  bool is_inBox(glm::vec3 const& punkt) const;
  bool intersect(Ray const& _r, float& _t) const override;
/*   Hit intersection (Ray const &_r, float &_t) const override;
  glm::vec3 get_normal(Hit const& hit) const override;
  glm::vec3 get_normal(int& _side) const;
 */
  float set_max(float const &coor1, float const &coor2);
  float set_min(float const &coor1, float const &coor2);

  /*vec3 nearest_corner(glm::vec3 const &min, glm::vec3 const &max, glm::vec3 const &origin) const;
  vec3 furthest_corner(glm::vec3 const &min, glm::vec3 const &max, glm::vec3 const &origin) const;

  float nearest_komponent(float const &min, float const &max, float const &origin) const;
  float furthest_komponent(float const &min, float const &max, float const &origin) const;

  bool is_on_surface(glm::vec3 const &input) const;*/
};

#endif //BOX_HPP