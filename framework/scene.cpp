#include "scene.hpp"
#include <memory>
#include <map>
#include <vector>
#include <set>
#include "shape.hpp"
#include "material.hpp"
#include "light.hpp"
#include "box.hpp"
#include "sphere.hpp"

std::shared_ptr<Material> findMaterialVector(std::string const &findName, vector<std::shared_ptr<Material>> const &material_vector)
{   
    // Default material to return
    std::shared_ptr<Material> defaultMaterial(new Material);

    // find_if with a lambda that capture the needed name
    auto iterLambda = find_if(material_vector.begin(), material_vector.end(), [findName](std::shared_ptr<Material> const &material) { //capture findName by reference
        return material->name_ == findName;
    });

    // scope to show the material that was founded
    if (iterLambda == material_vector.end())
    {
        std::cout << "Do not exist!!!!!!! Use default Material\n"; //Material nicht gefunden wird, wird DefaultKonstruktor genutzt!
        std::cout << *defaultMaterial;
        return defaultMaterial;
    }
    else
    {
        std::cout << "Here's what u need from vector: \n";
        std::cout << *(*iterLambda) << "\n"; // show the value of the value of the lambda that is the material.
        return *iterLambda;
    }
}

void load_sdf(std::string const& filename, Scene &scene)
{
    // Scene scene;
    std::ifstream ifs;
    std::string dir = "../sdf/"+ filename;
    ifs.open(dir);

    if (ifs)
    {
        std::cout <<"Sdf file loaded from: "<< dir << endl;
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

                    for (int i = 0; i < 10; i++)
                    {
                        current_line_stream >> material_koof[i];
                    }

                    std::shared_ptr<Material> neu_material = std::make_shared<Material>(mat_name,
                                                                                        Color{material_koof[0], material_koof[1], material_koof[2]},
                                                                                        Color{material_koof[3], material_koof[4], material_koof[5]},
                                                                                        Color{material_koof[6], material_koof[7], material_koof[8]},
                                                                                        material_koof[9]);

                    scene.material_vector.push_back(neu_material);
                    // scene.material_map.insert(make_pair(neu_material->name_, neu_material));
                    // scene.material_set.insert(neu_material);
                }

                else if ("shape" == variable_name)
                {
                    std::string shape_type;
                    current_line_stream >> shape_type;

                    if ("box" == shape_type)
                    {

                        std::string shape_name;
                        current_line_stream >> shape_name;

                        float shape_points[6];

                        for (int i = 0; i < 6; i++)
                        {
                            current_line_stream >> shape_points[i];
                        }

                        std::string mat_name;
                        current_line_stream >> mat_name;

                        std::shared_ptr<Shape> neu_box = std::make_shared<Box>(glm::vec3(shape_points[0], shape_points[1], shape_points[2]),
                                                                               glm::vec3(shape_points[3], shape_points[4], shape_points[5]),
                                                                               shape_name,
                                                                               findMaterialVector(mat_name, scene.material_vector));

                        scene.shape_vector.push_back(neu_box);
                    }

                    else if ("sphere" == shape_type)
                    {
                        std::string shape_name;
                        current_line_stream >> shape_name;

                        float shape_points[4];

                        for (int i = 0; i < 4; i++)
                        {
                            current_line_stream >> shape_points[i];
                        }

                        std::string mat_name;
                        current_line_stream >> mat_name;

                        std::shared_ptr<Shape> neu_sphere = std::make_shared<Sphere>(glm::vec3(shape_points[0], shape_points[1], shape_points[2]),
                                                                                     shape_points[3],
                                                                                     findMaterialVector(mat_name, scene.material_vector),
                                                                                     shape_name);

                        scene.shape_vector.push_back(neu_sphere);
                    }
                }

                else if ("light" == variable_name)
                {
                    std::string light_name;
                    current_line_stream >> light_name;

                    float light_att[7];

                    for (int i = 0; i < 4; i++)
                    {
                        current_line_stream >> light_att[i];
                    }

                    std::shared_ptr<Light> neu_light = std::make_shared<Light>(light_name,
                                                                               glm::vec3(light_att[0], light_att[1], light_att[2]),
                                                                               Color(light_att[3], light_att[4], light_att[5]),
                                                                               light_att[6]);

                    scene.light_vector.push_back(neu_light);
                }
                else if ("camera" == variable_name){
                    Camera temp;
                    std::string camera_name;

                    current_line_stream >> temp._name;
                    current_line_stream >> temp._fov_x;

                    scene.camera = temp;

                }
            }
        }
    }

    else
    {
        cout << "file not found" << endl;
    }
    ifs.close();
    // return scene;
}