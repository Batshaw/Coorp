// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include <algorithm>
#include <cmath>

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
{}

// void Renderer::render()
// {
//   std::size_t const checker_pattern_size = 20;

//   for (unsigned y = 0; y < height_; ++y) {
//     for (unsigned x = 0; x < width_; ++x) {
//       Pixel p(x,y);
//       if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
//         p.color = Color(0.0, 1.0, float(x)/height_);
//       } else {
//         p.color = Color(1.0, 0.0, float(y)/width_);
//       }

//       write(p);
//     }
//   }
//   ppm_.save(filename_);
// }

void Renderer::render(Scene const& scene){
  filename_ = scene.name_;
  for(unsigned y = 0; y < height_; ++y){
    for(unsigned x = 0; x < width_; ++x){
      Pixel pixel(x, y);
      Ray ray = scene.camera_.rayThroughPixel(x, y, width_, height_);
      pixel.color = trace(scene, ray);
      write(pixel);
    }
  }
  ppm_.save(filename_);
}

Color Renderer::trace(Scene const& scene, Ray const& ray){
  Camera camera = {scene.camera_};
  Color temp{1.0f, 1.0f, 1.0f};
  float distance;
  float dmin = std::numeric_limits<float>::max();

  bool is_intersect = true;
  int closetObjectIndex = -1;

  for(int i = 0; i < scene.shape_vector_.size(); ++i){
    is_intersect = (*scene.shape_vector_[i]).intersect(ray, distance);
    if(is_intersect){
      if(distance < dmin){
        dmin = distance;
        closetObjectIndex = i;
        // return (scene.shape_vector[closetObjectIndex])->getMaterial()->ka_;
      }
    }
    // else return Color{0.0f, 0.0f, 0.0f};
  }
  if(closetObjectIndex != -1){
    // cout << "nicht intersection" << endl;
    // return (scene.shape_vector[closetObjectIndex])->getMaterial()->ka_;
    // Color cl = toneMapping(shade(scene, ray, closetObjectIndex));  Tone Mapping but ugly :((((
    Color cl = shade(scene, ray, closetObjectIndex);
    return cl;
  }
  else return Color{0.0f, 0.0f, 0.0f};
}

// Color Renderer::shade(Scene const& scene, Ray const& ray, Light const& light, int const closest){
//   // Difusse Refektion
//   Hit h = scene.shape_vector[closest]->intersectHit(ray);
//   glm::vec3 lightVec = glm::normalize(light._origin - h.schnittPunkt_);
//   float cosPhi = std::max(glm::dot(lightVec, h.normalVector_), 0.0f);
//   Color lightIntensity{lig ht._color.r*light._brightness, light._color.g*light._brightness, light._color.b*light._brightness};
//   // Color lightIntensity = light._color;
//   Color diffuColor = (lightIntensity)*(scene.shape_vector[closest]->getMaterial()->kd_)*cosPhi;

//   // Ambiente Color
//   Color ambColor = (scene.ambient.color_)*(scene.shape_vector[closest]->getMaterial()->ka_);

//   // Spekulare Licht
//   glm::vec3 reflekLichtVektor = glm::normalize(2*glm::dot(h.normalVector_, lightVec)*(h.normalVector_) - lightVec);
//   float cosBeta = std::max(glm::dot(reflekLichtVektor, -ray.direction), 0.0f);
//   Color spekColor = (scene.shape_vector[closest]->getMaterial()->ks_)*std::pow(cosBeta, scene.shape_vector[closest]->getMaterial()->m_);

//   Color endColor = diffuColor + ambColor + spekColor;
//   return endColor;
// }

Color Renderer::shade(Scene const& scene, Ray const& ray, int const closest){
  // Difusse Refektion
  Hit h = scene.shape_vector_[closest]->intersectHit(ray);
  Color diffuColor = {0.0, 0.0, 0.0};
  Color spekColor = {0.0, 0.0, 0.0};
  // Fuer beliebig vielen Lichtquellen
  for(int i = 0; i < scene.light_vector_.size(); ++i){
    glm::vec3 lightVec = glm::normalize(scene.light_vector_[i]->origin_ - h.schnittPunkt_);
    Ray lightHitRay{h.schnittPunkt_, lightVec};
    bool imSchatten = false;
    float t;
    // Check if lightVec have intersection with another Shape
    for(int a = 0; a < scene.shape_vector_.size(); ++a){
      if(a != closest && imSchatten != true){
        imSchatten = scene.shape_vector_[a]->intersect(lightHitRay, t);
        if(t < 0) {
          imSchatten = false;
        }
      }
      // if(a != closest){
      //   if(imSchatten != true){
      //     imSchatten = scene.shape_vector[a]->intersect(lightHitRay, t);
      //   }
      // }
    }

    // When no intersect, put light :D
    if(imSchatten == false){
      float cosPhi = std::max(glm::dot(h.normalVector_, lightVec), 0.0f);
      Color lightIntensity{scene.light_vector_[i]->color_.r*scene.light_vector_[i]->brightness_, scene.light_vector_[i]->color_.g*scene.light_vector_[i]->brightness_, scene.light_vector_[i]->color_.b*scene.light_vector_[i]->brightness_};
      // Color lightIntensity = light._color;
      diffuColor += (lightIntensity)*(scene.shape_vector_[closest]->get_material()->kd_)*cosPhi;

      // Spekulare Licht
      glm::vec3 reflekLichtVektor = glm::normalize(2*glm::dot(h.normalVector_, lightVec)*(h.normalVector_) - lightVec);
      float cosBeta = std::max(glm::dot(reflekLichtVektor, -ray.direction_), 0.0f);
      spekColor += (scene.shape_vector_[closest]->get_material()->ks_)*std::pow(cosBeta, scene.shape_vector_[closest]->get_material()->m_);
    }
  }
  // Ambiente Color
  Color ambColor = (scene.ambient_.color_)*(scene.shape_vector_[closest]->get_material()->ka_);

  // End color
  Color endColor = diffuColor + ambColor + spekColor;
  return endColor;
}

Color Renderer::toneMapping(Color const& color){
  Color outColor = {0.0f, 0.0f, 0.0f};
  outColor.r = color.r/(color.r + 1);
  outColor.g = color.g/(color.g + 1);
  outColor.b = color.b/(color.b + 1);
  
  return outColor;
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}
