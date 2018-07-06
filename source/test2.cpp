#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "Scene.hpp"
#include "Shape.hpp"
#include "Box.hpp"
#include "material.hpp"
#include <conio.h>

// TEST_CASE("aufgabe3", "[interect]")
// {
//     Ray ray;
//     ray.origin = {0.0,0.0,-8.0};
//     ray.direction = {1, 1, -1.0};

//     float distance = 0;

//     vec3 v1{-1.5, -7.6, -1.5};
//     vec3 v2{4.5, 6.7, -7.0};

//     Box box1{v1, v2};

//     cout<<box1;
//     REQUIRE(box1.intersect(ray, distance) == true);

// }


TEST_CASE("aufgabe5", "[scene]")
{
    Scene scene1;
    load_sdf("example.sdf", &scene1);
    findMaterialVector("green", scene1.material_vector);
    findMaterialMap("red", scene1.material_map);
    findMaterialSet("green", scene1.material_set);
    
}


int main(int argc, char *argv[])
{
    getch();
    return Catch::Session().run(argc, argv);
}
