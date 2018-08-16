#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "Shape.hpp"
#include "Box.hpp"
#include "Sphere.hpp"
#include <fstream>
#include "material.hpp"
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include "Light.hpp"

using namespace std;

struct Scene
{
    std::vector<std::shared_ptr<Material>> material_vector;
    std::map<std::string, std::shared_ptr<Material>> material_map;
    std::set<std::shared_ptr<Material>> material_set;

    std::vector<std::shared_ptr<Shape>> shape_vector;

    std::vector<std::shared_ptr<Light>> light_vector;
     
    unsigned int _width;
    unsigned int _height;
    std::string _name = "default";

};


/* bool operator<(std::shared_ptr<Material> const &lhs, std::shared_ptr<Material> const &rhs)
{
    return lhs->name_ < rhs->name_;
};*/


/*

std::shared_ptr<Material> findMaterialSet(std::string const &findName, set<std::shared_ptr<Material>> const &material_set)
{
    auto iterLambda = find_if(material_set.begin(), material_set.end(), [findName](std::shared_ptr<Material> const &material) { //capture findName by reference
        return material->name_ == findName;
    });
    if (iterLambda == material_set.end())
    {
        std::cout << "Do not exist!!!!!\n";
        return nullptr;
    }
    else
    {
        std::cout << "Here's what u need from set: \n";
        std::cout << *(*iterLambda) << endl;
        return *iterLambda;
    }
}

std::shared_ptr<Material> findMaterialMap(std::string const &findName, map<std::string, std::shared_ptr<Material>> const &material_map)
{
    auto iter = material_map.find(findName);
    if (iter == material_map.end())
    {
        std::cout << "Do not exist!!!!!\n";
        return nullptr;
    }
    else
    {
        std::cout << "Here's what u need from map: \n";
        std::cout << *iter->second << endl;
        return iter->second;
    }
}; */

/* 
 */

#endif
