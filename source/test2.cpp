#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "Scene.hpp"
#include "Shape.hpp"
#include "Box.hpp"
#include "material.hpp"

using namespace std;

/*TEST_CASE("aufgabe3", "[interect]")
{
    Ray ray;
    ray.origin = {0.0,0.0,-8.0};
    ray.direction = {1, 1, -1.0};
    float distance = 0;

    glm::vec3 v1{-1.5, -7.6, -1.5};
    glm::vec3 v2{4.5, 6.7, -7.0};
    Box box1{v1,v2};

    std::cout<<box1;
    REQUIRE(box1.intersect(ray, distance) == true);
}*/

TEST_CASE("test ray_tracer mit Box 2.0", "[intersect]"){
  glm::vec3 origin{0, 0, 0};
  glm::vec3 direction{1, 0, 0};
  Ray r{origin, direction};
  glm::vec3 min{2.0f, -3.5f, -4.0f};
  glm::vec3 max{3.0f, 5.0f, 6.5f};
  Box b(min, max);
  float t;
  REQUIRE(b.intersect(r, t) == true);
  std::cout<< "End!";
}

TEST_CASE("aufgabe5", "[scene]")
{
    Scene scene1;
    load_sdf("scene1.sdf", scene1);
    findMaterialVector("green", scene1.material_vector);
    findMaterialMap("red", scene1.material_map);
    findMaterialSet("blue", scene1.material_set);
}


int main(int argc, char *argv[])
{
    return Catch::Session().run(argc, argv);
}

