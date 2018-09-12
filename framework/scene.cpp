#include "scene.hpp"
#include <renderer.hpp>
#include <window.hpp>
#include <iomanip>
#include <iostream>
#include <unistd.h>   //for chdir

//for linux mkdir
//#include <sys/stat.h> 

//for windows mkdir
#if defined _MSC_VER
#include <direct.h>
#elif defined __GNUC__
#include <sys/types.h>
#include <sys/stat.h>
#endif

void transform_obj(Camera &cam, glm::mat4 const &matrix)
{
    cam.world_transformation_ = matrix * cam.world_transformation_;
    cam.world_transformation_inv_ = glm::inverse(cam.world_transformation_);
}

void transform_obj(std::shared_ptr<Shape> &shape, glm::mat4 const &matrix)
{
    shape->transform(matrix);
}

Ray rayThroughPixel(Camera const &cam, float x, float y, float width, float height)
{
    glm::vec3 origin{cam.eye_};
    glm::vec3 direction{x - width / 2, y - height / 2, (-width / 2) / tan(cam.fov_x_ / 2)}; //tan(Öffnungswinkel/2)=(width/2)/distance von Camera zum Bildebene.
    Ray rayCamera{origin, direction};
    return rayCamera;
}

std::shared_ptr<Material> findMaterialVector(std::string const &findName, vector<std::shared_ptr<Material>> const &material_vector)
{
    // Default material to return
    std::shared_ptr<Material> defaultMaterial(new Material);

    // find_if with a lambda that capture the needed name
    auto iterLambda = find_if(material_vector.begin(), material_vector.end(), [findName](std::shared_ptr<Material> const &material) {
        //capture findName by reference
        return material->name_ == findName;
    });

    // scope to show the material that was founded
    if (iterLambda == material_vector.end())
    {
        return defaultMaterial;
    }
    else
    {
        return *iterLambda;
    }
}

void load_sdf(std::string const &filename, Scene &scene)
{
    // Scene scene;
    std::ifstream ifs;
    std::string dir = "./sdf/" + filename;
    ifs.open(dir);

    if (ifs)
    {
        std::cout << "Sdf file loaded from: " << dir << endl;
        std::string line_buffer;
        glm::mat4 transform_anim{1.0f};
        bool must_animate = false;
        std::vector<string> animated_shapes;

        while (std::getline(ifs, line_buffer))
        {

            std::stringstream current_line_stream(line_buffer);

            std::string sdf_keyword;

            current_line_stream >> sdf_keyword;

            //Define all item (Material, geometry, camera etc)
            if ("define" == sdf_keyword)
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

                    scene.material_vector_.push_back(neu_material);
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
                                                                               findMaterialVector(mat_name, scene.material_vector_));

                        scene.shape_vector_.push_back(neu_box);
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
                                                                                     shape_name,
                                                                                     findMaterialVector(mat_name, scene.material_vector_));

                        scene.shape_vector_.push_back(neu_sphere);
                    }
                }

                else if ("light" == variable_name)
                {
                    std::string light_name;
                    current_line_stream >> light_name;

                    float light_att[7];

                    for (int i = 0; i < 7; i++)
                    {
                        current_line_stream >> light_att[i];
                    }

                    std::shared_ptr<Light> neu_light = std::make_shared<Light>(light_name,
                                                                               glm::vec3(light_att[0], light_att[1], light_att[2]),
                                                                               Color(light_att[3], light_att[4], light_att[5]),
                                                                               light_att[6]);

                    scene.light_vector_.push_back(neu_light);
                }
                else if ("camera" == variable_name)
                {
                    Camera temp;
                    std::string camera_name;

                    current_line_stream >> temp.name_;
                    current_line_stream >> temp.fov_x_;

                    scene.camera_ = temp;
                }
                else if ("ambient" == variable_name)
                {
                    float ambient_att[3];

                    for (int i = 0; i < 3; i++)
                    {
                        current_line_stream >> ambient_att[i];
                    }

                    Ambient temp{Color(ambient_att[0], ambient_att[1], ambient_att[2])};

                    scene.ambient_ = temp;
                }
            }

            //Tranform objects initial state
            else if ("transform" == sdf_keyword)
            {
                std::string obj_name;
                float rotation_angle;
                glm::vec3 transform_vector;
                current_line_stream >> obj_name;
                for (std::shared_ptr<Shape> shape : scene.shape_vector_)
                {

                    if (shape->getName() == obj_name)
                    {
                        std::string transform;

                        current_line_stream >> transform;
                        cout << "transforming " << shape->getName() << std::endl;

                        if ("scale" == transform)
                        {
                            current_line_stream >> transform_vector.x;
                            current_line_stream >> transform_vector.y;
                            current_line_stream >> transform_vector.z;
                            transform_obj(shape, glm::scale(transform_vector));
                        }

                        else if ("translate" == transform)
                        {
                            current_line_stream >> transform_vector.x;
                            current_line_stream >> transform_vector.y;
                            current_line_stream >> transform_vector.z;
                            transform_obj(shape, glm::translate(transform_vector));
                        }

                        else if ("rotate" == transform)
                        {
                            current_line_stream >> rotation_angle;
                            current_line_stream >> transform_vector.x;
                            current_line_stream >> transform_vector.y;
                            current_line_stream >> transform_vector.z;
                            transform_obj(shape, glm::rotate(rotation_angle, transform_vector));
                        }
                    }
                }

                if (scene.camera_.name_ == obj_name)
                {
                    std::string transform;
                    current_line_stream >> transform;

                    if ("translate" == transform)
                    {
                        glm::vec3 translate;
                        current_line_stream >> translate.x;
                        current_line_stream >> translate.y;
                        current_line_stream >> translate.z;
                        transform_obj(scene.camera_, glm::translate(translate));
                    }

                    else if ("rotate" == transform)
                    {
                        float raw;
                        glm::vec3 rotate;
                        current_line_stream >> raw;
                        current_line_stream >> rotate.x;
                        current_line_stream >> rotate.y;
                        current_line_stream >> rotate.z;
                        transform_obj(scene.camera_, glm::rotate(raw, rotate));
                    }
                }
            }

            //Animate the state of objects
            else if ("animate" == sdf_keyword)
            {
                std::string obj_name;
                float rotation_angle;
                glm::vec3 transform_vector;
                current_line_stream >> obj_name;

                if (scene.camera_.name_ == obj_name)
                {
                    must_animate = true;
                    std::string transform;
                    current_line_stream >> transform;

                    if ("translate" == transform)
                    {
                        glm::vec3 translate;
                        current_line_stream >> translate.x;
                        current_line_stream >> translate.y;
                        current_line_stream >> translate.z;
                        transform_anim = glm::translate(translate);
                    }

                    else if ("rotate" == transform)
                    {
                        float raw;
                        glm::vec3 rotate;
                        current_line_stream >> raw;
                        current_line_stream >> rotate.x;
                        current_line_stream >> rotate.y;
                        current_line_stream >> rotate.z;
                        transform_anim = glm::rotate(raw, rotate);
                    }
                }

                else
                {
                    for (std::shared_ptr<Shape> shape : scene.shape_vector_)
                    {

                        if (shape->getName() == obj_name)
                        {
                            must_animate = true;
                            std::string transform;
                            current_line_stream >> transform;

                            if ("scale" == transform)
                            {
                                current_line_stream >> transform_vector.x;
                                current_line_stream >> transform_vector.y;
                                current_line_stream >> transform_vector.z;
                                shape->animation_matrix_ *= glm::scale(transform_vector);
                            }

                            else if ("translate" == transform)
                            {
                                current_line_stream >> transform_vector.x;
                                current_line_stream >> transform_vector.y;
                                current_line_stream >> transform_vector.z;
                                shape->animation_matrix_ *= glm::translate(transform_vector);
                            }

                            else if ("rotate" == transform)
                            {
                                current_line_stream >> rotation_angle;
                                current_line_stream >> transform_vector.x;
                                current_line_stream >> transform_vector.y;
                                current_line_stream >> transform_vector.z;
                                shape->animation_matrix_ *= glm::rotate(rotation_angle, transform_vector);
                            }

                            animated_shapes.push_back(obj_name);
                        }
                    }
                }
            }

            //Render process all animation steps in a scene for every frame
            else if ("render" == sdf_keyword)
            {
                std::string camera_name;
                current_line_stream >> camera_name;

                if (camera_name == scene.camera_.name_)
                {
                    std::string file_ext(".sdf");
                    std::string type;
                    current_line_stream >> type;
                    std::string extension;
                    current_line_stream >> extension;
                    scene.name_ = filename.substr(0, filename.size() - file_ext.size());

                    std::string dir = scene.name_;
                    current_line_stream >> scene.width_;
                    current_line_stream >> scene.height_;

                    //Simple change direction command
                    chdir("output");

                    //Create a folder with corresponding scene's name before rendering all the ppm images
                    // mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); //for linux

                    mkdir(dir.c_str()); //for windows
                    
                    
                    //Then change the directory
                    chdir(dir.c_str());

                    if (must_animate)
                    {
                        for (int i = 1; i < 121; i++)
                        {

                            transform_obj(scene.camera_, transform_anim);
                            for (std::shared_ptr<Shape> shape : scene.shape_vector_)
                            {
                                for (std::string name : animated_shapes)
                                {
                                    if (name == shape->getName())
                                    {
                                        transform_obj(shape, shape->animation_matrix_);
                                    }
                                }
                            };

                            std::stringstream ss;
                            ss << type << std::setfill('0') << std::setw(3) << std::to_string(i) << extension;

                            //Use the stringstream to name each rendered .ppm files
                            Renderer renderer{scene.width_, scene.height_, ss.str()};
                            renderer.render(scene);
                        }

                        system("ffmpeg -r 24 -i image%03d.ppm animation.mp4");
                        system("vlc animation.mp4");
                    }
                    else
                    {
                        Renderer renderer{scene.width_, scene.height_, ("non-anim_" + scene.name_ + extension)};
                        renderer.render(scene);

                        Window window{{scene.width_, scene.height_}};

                        while (!window.should_close())
                        {
                            if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS)
                            {
                                window.close();
                            }
                            window.show(renderer.color_buffer());
                        }
                    }
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

Ray transformRay(glm::mat4 const &mat, Ray const &ray)
{
    glm::vec4 o{ray.origin_, 1.0f};    //Punkte
    glm::vec4 d{ray.direction_, 0.0f}; //Vector

    //Tranformierte
    glm::vec4 a{mat * o};
    glm::vec4 b{mat * d};

    glm::vec3 origin{a};
    glm::vec3 direction{b};

    return Ray{origin, direction};
};
