#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include "light.hpp"
#include "camera.hpp"
#include <glm/vec3.hpp>
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "material.hpp"
#include "ambient.hpp"

using namespace std;

struct Scene
{
    std::vector<std::shared_ptr<Material>> material_vector_;
    std::vector<std::shared_ptr<Shape>> shape_vector_;
    std::vector<std::shared_ptr<Light>> light_vector_;

    std::string name_ = "default_scene.ppm";
    unsigned width_;
    unsigned height_;
    Camera camera_;
    Ambient ambient_;
};

    // bool operator<(std::shared_ptr<Material> const &lhs, std::shared_ptr<Material> const &rhs)
    // {
    //     return lhs->name_ < rhs->name_;
    // };

    // std::shared_ptr<Material> findMaterialSet(std::string const &findName, set<std::shared_ptr<Material>> const &material_set)
    // {
    //     auto iterLambda = find_if(material_set.begin(), material_set.end(), [findName](std::shared_ptr<Material> const &material) { //capture findName by reference
    //         return material->name_ == findName;
    //     });
    //     if (iterLambda == material_set.end())
    //     {
    //         std::cout << "Do not exist!!!!!\n";
    //         return nullptr;
    //     }
    //     else
    //     {
    //         std::cout << "Here's what u need from set: \n";
    //         std::cout << *(*iterLambda) << endl;
    //         return *iterLambda;
    //     }
    // }

    // std::shared_ptr<Material> findMaterialMap(std::string const &findName, map<std::string, std::shared_ptr<Material>> const &material_map)
    // {
    //     auto iter = material_map.find(findName);
    //     if (iter == material_map.end())
    //     {
    //         std::cout << "Do not exist!!!!!\n";
    //         return nullptr;
    //     }
    //     else
    //     {
    //         std::cout << "Here's what u need from map: \n";
    //         std::cout << *iter->second << endl;
    //         return iter->second;
    //     }
    // };

#endif //SCENE_HPP