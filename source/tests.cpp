#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "box.hpp"
#include "sphere.hpp"
#include "color.hpp"
#include "shape.hpp"

TEST_CASE("get-Methode for Box", "[get]"){
  glm::vec3 min{20.5f, 15.5f, -10.0f};
  glm::vec3 max{30.0f, 20.0f, 5.0f};
  Color c{0.0f, 0.0f, 0.5f};
  Box b(min, max, "Box-1", c);
  REQUIRE(b.getMax().x == 30.0f);
}

TEST_CASE("get-Methode for Sphere", "[get]"){
  glm::vec3 mittel{32.0f, 15.5f, -25.0f};
  float radius = 23.0f;
  Color c{0.0f, 0.7f, 0.0f};
  Sphere s(mittel, radius, c);
  REQUIRE(s.getMittel().y == 15.5f);
}

TEST_CASE("calculate area of the Box", "[calculate]"){
  glm::vec3 min{20.5f, 15.5f, -10.0f};
  glm::vec3 max{30.0f, 20.0f, 5.0f};
  Color c{0.0f, 0.0f, 0.5f};
  Box b(min, max, "Box-1", c);
  REQUIRE(b.area() == 505.5f);
}
TEST_CASE("calculate volume of the Box", "[calculate]"){
  glm::vec3 min{20.5f, 15.5f, -10.0f};
  glm::vec3 max{30.0f, 20.0f, 5.0f};
  Color c{0.0f, 0.0f, 0.5f};
  Box b(min, max, "Box-1", c);
  REQUIRE(b.volumen() == 641.25f);
  std::cout<< b;
}

TEST_CASE("calculate area of the Sphere", "[calculate]"){
  glm::vec3 mittel{32.0f, 15.5f, -25.0f};
  float radius = 23.0f;
  Color c{0.0f, 0.7f, 0.0f};
  Sphere s(mittel, radius, c);
  REQUIRE(s.area() == Approx(6647.61f).epsilon(0.01));
}
TEST_CASE("calculate volume of the Sphere", "[calculate]"){
  glm::vec3 mittel{32.0f, 15.5f, -25.0f};
  float radius = 23.0f;
  Color c{0.0f, 0.7f, 0.0f};
  Sphere s(mittel, radius, c);
  REQUIRE(s.volumen() == Approx(50965.01).epsilon(0.01));
  std::cout<< s;
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
