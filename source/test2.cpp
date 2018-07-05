#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "Scene.hpp"
#include "Shape.hpp"
#include "Box.hpp"

TEST_CASE("aufgabe3", "[interect]")
{
    Ray ray;
    ray.origin = {0.0,0.0,-8.0};
    ray.direction = {1, 1, -1.0};

    float distance = 0;

    vec3 v1{-1.5, -7.6, -1.5};
    vec3 v2{4.5, 6.7, -7.0};

    Box box1{v1, v2};

    cout<<box1;
    REQUIRE(box1.intersect(ray, distance) == true);

}


TEST_CASE("aufgabe5", "[scene]")
{

Scene scene1;

    std::ifstream ifs("scene1.sdf");

    std::string line_buffer;

    while (std::getline(ifs, line_buffer))
    {

        std::stringstream current_line_stream(line_buffer);

        std::string first_symbol;

        current_line_stream >> first_symbol;

        if ("define" == first_symbol)
        {

            std::string variable_name;
            current_line_stream >> variable_name;

            if ("material" == variable_name)
            {
                std::string mat_name;
                current_line_stream >> mat_name;

                float ka_r, ka_g, ka_b;
                float kd_r, kd_g, kd_b;
                float ks_r, ks_g, ks_b;

                float m_;

                current_line_stream >> ka_r;
                current_line_stream >> ka_g;
                current_line_stream >> ka_b;

                current_line_stream >> kd_r;
                current_line_stream >> kd_g;
                current_line_stream >> kd_b;

                current_line_stream >> ks_r;
                current_line_stream >> ks_g;
                current_line_stream >> ks_b;

                current_line_stream >> m_;

                std::shared_ptr<Material> neu_material = std::make_shared<Material>(mat_name, Color{ka_r, ka_g, ka_b}, Color{kd_r, kd_g, kd_b}, Color{ks_r, ks_g, ks_b}, m_);
                
                scene1.material_vector.push_back(neu_material);
            }
        }
    }
}


int main(int argc, char *argv[])
{

    return Catch::Session().run(argc, argv);
}
