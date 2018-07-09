#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "Scene.hpp"
#include "Shape.hpp"
#include "Box.hpp"
#include "material.hpp"

TEST_CASE("aufgabe3", "[interect]")
{
    Ray ray;
<<<<<<< HEAD
    ray.origin = {0.0,0.0,-8.0};
    ray.direction = {1, 1, -1.0};
    float distance = 0;

    vec3 v1{-1.5, -7.6, -1.5};
    vec3 v2{4.5, 6.7, -7.0};

    Box box1{v1, v2};

    cout<<box1;
    REQUIRE(box1.intersect(ray, distance) == true);

}
=======
    ray.origin = {0.0, 0.0, -8.0};
    ray.direction = {1, 1, -1.0};

    float distance = 0;

    vec3 v1{-1.5, -7.6, -1.5};
    vec3 v2{4.5, 6.7, -7.0};
    Box box1{v1, v2};
>>>>>>> 847b38725f134112943ab21dd8f30a706e6555aa

    cout << box1;
    REQUIRE(box1.intersect(ray, distance) == true);
}

TEST_CASE("aufgabe5", "[scene]")
{
    Scene scene1;
    load_sdf("scene1.sdf", &scene1);
    findMaterialVector("green", scene1.material_vector);
    findMaterialMap("red", scene1.material_map);
    findMaterialSet("blue", scene1.material_set);
}

int main(int argc, char *argv[])
{
    return Catch::Session().run(argc, argv);
}
