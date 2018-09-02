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
#include "Camera.hpp"
#include "ambient.hpp"

using namespace std;

struct Scene
{
    std::vector<std::shared_ptr<Material>> material_vector;
    std::vector<std::shared_ptr<Shape>> shape_vector;
    std::vector<std::shared_ptr<Light>> light_vector;

    unsigned _width;
    unsigned _height;
    std::string _name;

    Camera _camera;
    Ambient _ambient;

    //Default scene
    Scene() : material_vector{},
              shape_vector{std::vector<std::shared_ptr<Shape>>()},
              light_vector{std::vector<std::shared_ptr<Light>>()},
              _width{500},
              _height{500},
              _name{"default scene"},
              _camera{Camera{}},
              _ambient{Ambient{}} {};

    //Kopie Scene
    Scene(Scene const &scene) : material_vector{scene.material_vector},
                                shape_vector{scene.shape_vector},
                                light_vector{scene.light_vector},
                                _width{scene._width},
                                _height{scene._height},
                                _name{scene._name},
                                _camera{scene._camera},
                                _ambient{scene._ambient} {};
};

#endif
