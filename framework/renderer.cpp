// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

#define PRINT_DEBUG_INFO 0

Renderer::Renderer(Scene const &scene)
    : scene_(scene),
      width_(scene._width),
      height_(scene._height),
      color_buffer_(scene._width * scene._height, Color(0.0, 0.0, 0.0)),
      filename_(scene._name),
      ppm_(scene._width, scene._height){};

/* Renderer::Renderer(unsigned w, unsigned h, std::string const &file)
    : width_(w), height_(h), color_buffer_(w * h, Color(0.0, 0.0, 0.0)), filename_(file), ppm_(width_, height_)
{
} */
//Aufgabe 7.1 - von Scene gefundenen Shapes zu rendern
void Renderer::render()
{

  for (unsigned y = 0; y < height_; ++y)
  {
    for (unsigned x = 0; x < width_; ++x)
    {
      Pixel p(x, y);
      Ray ray = scene_._camera.rayThroughPixel(x, y, width_, height_);
      p.color = trace(ray);
      write(p);
    }
  }
  ppm_.save(filename_);
}

//Aufgabe 7.1 - raytrace

Color Renderer::trace(Ray const &ray) const
{
  Camera cam1 = {scene_._camera};

  float dist;
  float dmin = 1000;

  bool is_intersect = true;
  int closest_object_index = -1;

  //Get closest object that is hit by ray
  for (int i = 0; i < scene_.shape_vector.size(); ++i)
  {
    is_intersect = (*scene_.shape_vector[i]).intersect(ray, dist);
    if (is_intersect && dist < dmin)
    {
      dmin = dist;
      closest_object_index = i;
    }
  }

  if (closest_object_index != -1)
  {
    Color col = shade(ray, closest_object_index);
    Color temp = (scene_.shape_vector[closest_object_index])->get_material_()->ka_;
    return col;
  }

  else
  {
    return Color{0.4f, 0.4f, 0.4f};
  }
}

Color Renderer::shade(Ray const& ray, int& closest) const{
  // Difusse Refektion
  Hit h = scene_.shape_vector[closest]->intersect_hit(ray);
  Color diffuColor = {0.0, 0.0, 0.0};
  Color spekColor = {0.0, 0.0, 0.0};
  // Fuer beliebig vielen Lichtquellen
  for(int i = 0; i < scene_.light_vector.size(); ++i){
    glm::vec3 lightVec = glm::normalize(scene_.light_vector[i]->_origin - h.coor_);
    Ray lightHitRay{scene_.light_vector[i]->_origin, lightVec};
    bool imSchatten = false;
    // Check if lightVec have intersection with another Shape
    for(int a = 0; a < scene_.shape_vector.size(); ++a){
      if(a != closest && imSchatten != true){
        float t = 0;
        imSchatten = scene_.shape_vector[a]->intersect(lightHitRay, t);
      }
    }
    // When no intersect, put light :D
    if(imSchatten == false){
      float cosPhi = std::max(glm::dot(lightVec, h.normal_), 0.0f);
      Color lightIntensity{scene_.light_vector[i]->_color.r*scene_.light_vector[i]->_brightness, scene_.light_vector[i]->_color.g*scene_.light_vector[i]->_brightness, scene_.light_vector[i]->_color.b*scene_.light_vector[i]->_brightness};
      // Color lightIntensity = light._color;
      diffuColor += (lightIntensity)*(scene_.shape_vector[closest]->get_material_()->kd_)*cosPhi;

      // Spekulare Licht
      glm::vec3 reflekLichtVektor = glm::normalize(2*glm::dot(h.normal_, lightVec)*(h.normal_) - lightVec);
      float cosBeta = std::max(glm::dot(reflekLichtVektor, -ray.direction), 0.0f);
      spekColor += (scene_.shape_vector[closest]->get_material_()->ks_)*std::pow(cosBeta, scene_.shape_vector[closest]->get_material_()->m_);
    }
  }
  // Ambiente Color
  Color ambColor = (scene_._ambient.color_)*(scene_.shape_vector[closest]->get_material_()->ka_);

  // End color
  Color endColor = diffuColor + ambColor + spekColor;
  return endColor;
}

void Renderer::write(Pixel const &p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_ * p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0)
  {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
              << "pixel out of ppm_ : "
              << (int)p.x << "," << (int)p.y
              << std::endl;
  }
  else
  {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}

//Checkerboard
/* void Renderer::render()
{
  std::size_t const checker_pattern_size = 20;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = Color(0.0, 1.0, float(x)/height_);
      } else {
        p.color = Color(1.0, 0.0, float(y)/width_);
      }

      write(p);
    }
  }
  ppm_.save(filename_);
} */