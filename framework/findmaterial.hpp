#ifndef FINDMATERIAL_HPP
#define FINDMATERIAL_HPP

#include <vector>
#include "material.hpp"
#include <string>
#include <memory>
#include <algorithm>


std::shared_ptr<Material> findMaterialVector(std::string const &findName, std::vector<std::shared_ptr<Material>> const &material_vector)
{
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
};

#endif