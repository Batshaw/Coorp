#include <vector>
#include "Shape.hpp"
#include <fstream>
#include "material.hpp"

using namespace std;

struct Scene
{
    vector<std::shared_ptr<Material>> material_vector;
};

void load_sdf(string filename, Scene* scene)
{
    std::ifstream ifs(filename);

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

                float material_koof[10];

                
                for(int i = 0; i < 10; i++)
                {
                    current_line_stream >> material_koof[i];
                }
                

                std::shared_ptr<Material> neu_material = std::make_shared<Material>(mat_name, Color{material_koof[0], material_koof[1], material_koof[2]}, Color{material_koof[3], material_koof[4], material_koof[5]}, Color{material_koof[6], material_koof[7], material_koof[8]}, material_koof[9]);

                scene->material_vector.push_back(neu_material);
            }
        }
    }
}

std::shared_ptr<Material> findMaterial(std::string const& name, Scene& scene){
    
};
bool operator<(std::shared_ptr<Material> const& lhs, std::shared_ptr<Material> const& rhs){
        return lhs->name_ < rhs->name_;
};
