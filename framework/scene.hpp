#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include "light.hpp"
#include "camera.hpp"
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "material.hpp"
#include "ambient.hpp"

#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>

using namespace std;

struct Scene
{

    //Member variable
    std::vector<std::shared_ptr<Material>> material_vector_;
    std::vector<std::shared_ptr<Shape>> shape_vector_;
    std::vector<std::shared_ptr<Light>> light_vector_;

    std::string name_ = "default_scene.ppm";
    unsigned width_;
    unsigned height_;
    Camera camera_;
    Ambient ambient_;
};

void transform_obj(std::shared_ptr<Shape>& shape, glm::mat4 const &matrix);
void transform_obj(Camera &cam, glm::mat4 const &matrix);
Ray rayThroughPixel(Camera const& cam, float x, float y, float width, float height);
void load_sdf(std::string const &filename, Scene &scene);
std::shared_ptr<Material> findMaterialVector(std::string const &findName, vector<std::shared_ptr<Material>> const &material_vector);
Ray transformRay(glm::mat4 const& mat, Ray const& ray);

#endif //SCENE_HPP
