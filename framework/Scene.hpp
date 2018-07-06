#include <vector>
#include "Shape.hpp"
#include <fstream>
#include "material.hpp"
#include <algorithm>
#include <string>
#include <map>
#include <set>

using namespace std;

struct Scene
{
    vector<std::shared_ptr<Material>> material_vector;
    map<std::string, std::shared_ptr<Material>> material_map;
    set<std::shared_ptr<Material>> material_set;
};

void load_sdf(string filename, Scene* scene)
{
    // std::ifstream ifs(filename);
    std::ifstream ifs;
    ifs.open(filename);

    
    if (ifs) {
        std::cout<<filename<<endl;
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
                scene->material_map.insert(make_pair(neu_material->name_, neu_material));
                scene->material_set.insert(neu_material);
            }
        }
    }
    }
    
    else
    {
        cout<<"file not found"<<endl;
    }
    

/*vector<std::shared_ptr<Material>>::iterator iter;


for(iter = scene->material_vector.begin(); iter != scene->material_vector.end(); ++iter)
{
    cout<<*(*iter)<<endl;
}*/


    
}

bool operator<(std::shared_ptr<Material> const& lhs, std::shared_ptr<Material> const& rhs){
        return lhs->name_ < rhs->name_;
};
std::shared_ptr<Material> findMaterialVector(std::string const& findName, vector<std::shared_ptr<Material>> const& material_vector){
    // find_if with a lambda that capture the needed name
    auto iterLambda = find_if(material_vector.begin(), material_vector.end(),[findName](std::shared_ptr<Material> const& material){    //capture findName by reference
        return material->name_ == findName;
    });

    // scope to show the material that was founded
    if(iterLambda == material_vector.end()){
        std::cout<< "Do not exist!!!!!!!\n";
        return nullptr;
    }
    else{
        std::cout<< "Here's what u need: \n";
        std::cout<< *(*iterLambda)<< "\n";   // show the value of the value of the lambda that is the material.
        return *iterLambda;
    }
};

std::shared_ptr<Material> findMaterialSet(std::string const& findName, set<std::shared_ptr<Material>> const& material_set){
    auto iterLambda = find_if(material_set.begin(), material_set.end(),[findName](std::shared_ptr<Material> const& material){    //capture findName by reference
        return material->name_ == findName;                             
    });
    if(iterLambda == material_set.end()){
        std::cout<< "Do not exist!!!!!\n";
        return nullptr;
    }
    else{
        std::cout<< "Here's what u need: \n";
        std::cout<< *(*iterLambda)<< endl;
        return *iterLambda;
    }
}

std::shared_ptr<Material> findMaterialMap(std::string const& findName, map<std::string, std::shared_ptr<Material>> const& material_map){
    auto iter = material_map.find(findName);
    if(iter == material_map.end()){
        std::cout<< "Do not exist!!!!!\n";
        return nullptr;
    }
    else{
        std::cout<< "Here's what u need: \n";
        std::cout<< *iter->second<< endl;
        return iter->second;
    }
};