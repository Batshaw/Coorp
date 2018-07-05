#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "Sphere.hpp"
#include "Box.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

TEST_CASE("aufgabe2", "[box&sphere]")
{
  Box box1;

  glm::vec3 v1{1.5, 1.6, 1.8};
  glm::vec3 v2{4.5, 6.7, 7.2};

  Box box2{v1, v2};

  Sphere s1;
  Sphere s2{v1};
  Sphere s3{3.0, 4.6, 3.3};
  Sphere s4{v2, 2.5};

  REQUIRE(box2.length() == Approx(3.0).epsilon(0.1));
  REQUIRE(box2.width() == Approx(5.1).epsilon(0.1));
  REQUIRE(box2.height() == Approx(5.4).epsilon(0.1));

  REQUIRE(box2.volume() == Approx(82.5).epsilon(0.1));
  REQUIRE(box2.area() == Approx(118.1).epsilon(0.1));

  REQUIRE(box1.width() == Approx(1.0).epsilon(0.1));
  REQUIRE(box1.volume() == Approx(1.0).epsilon(0.1));
  REQUIRE(box1.area() == Approx(6.0).epsilon(0.1));

  REQUIRE(s1.volume() == Approx(4.14).epsilon(0.1));
  REQUIRE(s1.area() == Approx(12.56).epsilon(0.1));
  REQUIRE(s1.radius() == Approx(1.0).epsilon(0.1));

  REQUIRE(s2.volume() == Approx(4.14).epsilon(0.1));
  REQUIRE(s2.area() == Approx(12.56).epsilon(0.1));
  REQUIRE(s2.radius() == Approx(1.0).epsilon(0.1));

  REQUIRE(s3.volume() == Approx(4.14).epsilon(0.1));
  REQUIRE(s3.area() == Approx(12.56).epsilon(0.1));
  REQUIRE(s3.radius() == Approx(1.0).epsilon(0.1));

  REQUIRE(s4.volume() == Approx(65.44).epsilon(0.1));
  REQUIRE(s4.area() == Approx(75.5).epsilon(0.1));
  REQUIRE(s4.radius() == Approx(2.5).epsilon(0.1));
}

TEST_CASE("aufgabe3", "[shape]")
{
  Box box1;

  glm::vec3 v1{1.5, 1.6, 7.2};
  glm::vec3 v2{4.5, 6.7, -7.2};
  Color col1{4.5, 6.7, 7.2};
  Color col2{1.5, 1.6, 1.8};

  Box box2{v1, v2, "box2", col1};
  Box box3{"box3", col2};

  REQUIRE(box1.name() == "");
  REQUIRE(box1.color().r == Approx(1).epsilon(0.1));
  REQUIRE(box1.color().g == Approx(1).epsilon(0.1));
  REQUIRE(box1.color().b == Approx(1).epsilon(0.1));

  REQUIRE(box2.name() == "box2");
  REQUIRE(box2.color().r == Approx(4.5).epsilon(0.1));
  REQUIRE(box2.color().g == Approx(6.7).epsilon(0.1));
  REQUIRE(box2.color().b == Approx(7.2).epsilon(0.1));

  REQUIRE(box3.name() == "box3");
  REQUIRE(box3.color().r == Approx(1.5).epsilon(0.1));
  REQUIRE(box3.color().g == Approx(1.6).epsilon(0.1));
  REQUIRE(box3.color().b == Approx(1.8).epsilon(0.1));
}

TEST_CASE("aufgabe4", "[shape]")
{
  Box box1;

  glm::vec3 v1{1.5, 1.6, 1.8};
  glm::vec3 v2{4.5, -6.7, -1.2};
  Color col1{4.5, 6.7, 7.2};
  Color col2{1.5, 1.6, 1.8};

  Box box2{v1, v2, "box2", col1};
  Box box3{"box3", col2};

  cout << box2;
  cout << box3;
}

TEST_CASE("intersect_ray_sphere", "[intersect]")
{
  // Ray
  glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};
  // ray direction has to be normalized !
  // you can use :
  //v = glm::normalize ( some_vector )
  glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};
  // Sphere
  glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
  float sphere_radius{1.0f};
  float distance = 0.0f;
  auto result = glm::intersectRaySphere(
      ray_origin, ray_direction,
      sphere_center,
      sphere_radius * sphere_radius, // squared radius !!!
      distance);
  REQUIRE(distance == Approx(4.0f));
}

TEST_CASE("intersect_ray_sphere2", "[intersect2]")
{
  Sphere s1{0.0f, 0.0f, -5.0f, 1.0f};
  Sphere s2{3.0f, 0.0f, 4.0f, 3.0f};
  Sphere s3{1.0f, 2.5f, -5.0f, 3.5f};
  Sphere s4{1.0f, 2.5f, -5.0f, 1.5f};

  Box b1;

  Ray ray;

  REQUIRE(s1.intersect(ray) == true);
  REQUIRE(s2.intersect(ray) == false);
  REQUIRE(s3.intersect(ray) == true);
  REQUIRE(s4.intersect(ray) == false);

  REQUIRE(b1.intersect(ray) == true);
}

/* TEST_CASE("aufgabe7", "[aufgabe8]")
{
  Color red{255, 0, 0};
  glm::vec3 position{0.0f, 0.0f, 0.0f};

  std::shared_ptr<Sphere> s1 =
      std::make_shared<Sphere>({position, 1.2f, red, "sphere0"});
  //s1 ist als Sphere ohne Variable während der Laufzeit erstellt und danach werden die Variablen gegeben.

  std::shared_ptr<Shape> s2 =
      std::make_shared<Sphere>({position, 1.2f, red, "sphere1"});
  //s1 ist zuerst als Shape während der Laufzeit erstellt und danach wird die Type zur Sphere geändert und werden die Variablen gegeben.

  s1->print(std::cout);
  s2->print(std::cout);
} */

TEST_CASE("aufgabe8", "[aufgabe8]")
{
  Color red{255, 0, 0};
  glm::vec3 position{0.0f, 0.0f, 0.0f};
  Sphere *s1 = new Sphere{position, 1.2f, red, "sphere0"};
  Shape *s2 = new Sphere{position, 1.2f, red, "sphere1"};
  s1->print(std::cout);
  s2->print(std::cout);
  delete s1;
  delete s2;
}

int main(int argc, char *argv[])
{

  return Catch::Session().run(argc, argv);
}
