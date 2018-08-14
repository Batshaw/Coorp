#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "Scene.hpp"
#include "Shape.hpp"
#include "Box.hpp"
#include "material.hpp"
#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

TEST_CASE("final1", "[scene]")
{
    Scene scene2;
    load_sdf("scene1.sdf", scene2);

    REQUIRE(scene2.material_vector.size() == 2);
    REQUIRE(scene2.shape_vector.size() == 2);
}

int main(int argc, char *argv[])
{

    return Catch::Session().run(argc, argv);
}
