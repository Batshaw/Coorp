#ifndef SDFLOADER_HPP
#define SDFLOADER_HPP

#include "findmaterial.hpp"
#include "Scene.hpp"

void load_sdf(std::string filename, Scene &scene)
{

    std::ifstream ifs;
    std::string dir = "../sdf/" + filename;
    ifs.open(dir);

    if (ifs)
    {
        std::cout << "Sdf file loaded from: " << dir << endl;
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
                }

                else if ("shape" == variable_name)
                {
                    std::string shape_type;
                    current_line_stream >> shape_type;

                    if ("box" == shape_type)
                    {

                        std::string obj_name;
                        current_line_stream >> obj_name;

                        float shape_points[6];

                        for (int i = 0; i < 6; i++)
                        {
                            current_line_stream >> shape_points[i];
                        }

                        std::string mat_name;
                        current_line_stream >> mat_name;

                        std::shared_ptr<Shape> neu_box = std::make_shared<Box>(glm::vec3(shape_points[0], shape_points[1], shape_points[2]),
                                                                               glm::vec3(shape_points[3], shape_points[4], shape_points[5]),
                                                                               obj_name,
                                                                               findMaterialVector(mat_name, scene.material_vector));

                        scene.shape_vector.push_back(neu_box);
                    }

                    else if ("sphere" == shape_type)
                    {
                        std::string obj_name;
                        current_line_stream >> obj_name;

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
                                                                                     obj_name);

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

                else if ("camera" == variable_name)
                {
                    Camera temp;
                    std::string camera_name;

                    current_line_stream >> temp._name;
                    current_line_stream >> temp._fov_x;

                    scene._camera = temp;
                }

                else if ("ambient" == variable_name)
                {
                    float ambient_att[3];

                    for (int i = 0; i < 3; i++)
                    {
                        current_line_stream >> ambient_att[i];
                    }

                    Ambient temp{Color(ambient_att[0], ambient_att[1], ambient_att[2])};

                    scene._ambient = temp;
                }
            }

            else if ("transform" == first_symbol)
            {
                std::string obj_name;
                current_line_stream >> obj_name;

                for (std::shared_ptr<Shape> shape : scene.shape_vector)
                {

                    if (shape->name() == obj_name)
                    {
                        std::string transform;
                        current_line_stream >> transform;

                        glm::vec3 read_scale;
                        glm::vec3 read_translate;
                        float read_float;
                        glm::vec3 read_rotate;

                        if ("scale" == transform)
                        {
                            current_line_stream >> read_scale.x;
                            current_line_stream >> read_scale.y;
                            current_line_stream >> read_scale.z;
                        }

                        else if ("translate" == transform)
                        {
                            current_line_stream >> read_translate.x;
                            current_line_stream >> read_translate.y;
                            current_line_stream >> read_translate.z;
                        }

                        else if ("rotate" == transform)
                        {
                            current_line_stream >> read_float;
                            current_line_stream >> read_rotate.x;
                            current_line_stream >> read_rotate.y;
                            current_line_stream >> read_rotate.z;
                        }

                        shape->scale(read_scale);
                        shape->rotate(read_float, read_rotate);
                        shape->translate(read_translate);
                    }
                }

                if (scene._camera._name == obj_name)
                {
                    std::string transform;
                    current_line_stream >> transform;

                    glm::vec3 read_scale;
                    glm::vec3 read_translate;
                    float read_float;
                    glm::vec3 read_rotate;

                    if ("translate" == transform)
                    {
                        current_line_stream >> read_translate.x;
                        current_line_stream >> read_translate.y;
                        current_line_stream >> read_translate.z;
                    }

                    else if ("rotate" == transform)
                    {
                        current_line_stream >> read_float;
                        current_line_stream >> read_rotate.x;
                        current_line_stream >> read_rotate.y;
                        current_line_stream >> read_rotate.z;
                    }

                    scene._camera.camera_rotate(read_float, read_rotate);
                    scene._camera.camera_translate(read_translate);
                }
            }

            else if ("render" == first_symbol)
            {
                std::string camera_name;
                current_line_stream >> camera_name;

                if (camera_name == scene._camera._name)
                {
                    std::string file_ext(".sdf");
                    std::string type;
                    current_line_stream >> type;
                    std::string extension;
                    current_line_stream >> extension;
                    filename = filename.substr(0, filename.size() - file_ext.size());

                    scene._name = filename + "_" + type + extension;

                    current_line_stream >> scene._width;
                    current_line_stream >> scene._height;
                }
            }
        }
    }

    else
    {
        cout << "file not found" << endl;
    }

    ifs.close();
};

#endif