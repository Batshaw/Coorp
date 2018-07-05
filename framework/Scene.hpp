#include <vector>
#include "Shape.hpp"
#include <fstream>
#include "material.hpp"
#include <algorithm>
#include <string>

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

/*bool operator<(std::shared_ptr<Material> const& lhs, std::shared_ptr<Material> const& rhs){
        return lhs->name_ < rhs->name_;
};*/
std::shared_ptr<Material> findMaterial(std::string const& findName, vector<std::shared_ptr<Material>> material_vector){
    // find_if with a lambda that capture the needed name
    auto lambda = find_if(material_vector.begin(), material_vector.end(),[&findName](std::shared_ptr<Material> const& material){    //capture findName by reference
        return material->name_ == findName;
    });

    // scope to show the material that was founded
    if(lambda == material_vector.end()){
        cout<< "Do not exist!!!!!!!"<< endl;
        return nullptr;
    }
    else{
        cout<< "Here's what u need: \n";
        cout<< *(*lambda)<< endl;   // show the value of the value of the lambda that is the material.
        return *lambda;
    }
};

