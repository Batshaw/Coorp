#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sdfloader.hpp"

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
