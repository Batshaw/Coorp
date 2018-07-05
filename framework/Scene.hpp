#include <vector>
#include "Shape.hpp"
#include <fstream>
#include "material.hpp"

using namespace std;

struct Scene
{
    vector<std::shared_ptr<Material>> material_vector;
};

void load_sdf(string filename, Scene scene)
{
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


                float material_koof[10];

                
                for(int i = 0; i < 10; i++)
                {
                    current_line_stream >> material_koof[i];
                }
                

                std::shared_ptr<Material> neu_material = std::make_shared<Material>(mat_name, Color{material_koof, ka_g, ka_b}, Color{kd_r, kd_g, kd_b}, Color{ks_r, ks_g, ks_b}, m_);

                scene.material_vector.push_back(neu_material);
            }
        }
    }
}