#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "Scene.hpp"
#include "Shape.hpp"
#include "Box.hpp"
#include "material.hpp"

TEST_CASE("final1", "[scene]")
{
    Scene scene2;
    load_sdf("scene2.sdf", scene2);

}

int main(int argc, char *argv[])
{
    return Catch::Session().run(argc, argv);
}
