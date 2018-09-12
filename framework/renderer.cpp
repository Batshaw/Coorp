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

Renderer::Renderer(unsigned w, unsigned h, std::string const &file)
    : width_(w), height_(h), color_buffer_(w * h, Color(0.0, 0.0, 0.0)), filename_(file), ppm_(width_, height_)
{}

void Renderer::render(Scene const &scene)
{
  for (unsigned y = 0; y < height_; ++y)
  {
    for (unsigned x = 0; x < width_; ++x)
    {
      Pixel pixel(x, y);
      Ray ray = rayThroughPixel(scene.camera_, x, y, width_, height_);
      Ray trans_ray = transformRay(scene.camera_.world_transformation_, ray);
      pixel.color = trace(scene, trans_ray, 0);
      write(pixel);
    }
  }
  ppm_.save(filename_);
}

Color Renderer::trace(Scene const &scene, Ray const &ray, int depth)
{
  Camera camera = {scene.camera_};
  Color temp{1.0f, 1.0f, 1.0f};
  float distance;
  float dmin = std::numeric_limits<float>::max();

  bool is_intersect = true;
  int closetObjectIndex = -1;

  for (int i = 0; i < scene.shape_vector_.size(); ++i)
  {
    Hit objHit = (*scene.shape_vector_[i]).intersectHit(ray, distance);
    is_intersect = objHit.hit_;
    //distance = objHit.distance_;
    if (is_intersect)
    {
      if (distance < dmin)
      {
        dmin = distance;
        closetObjectIndex = i;
      }
    }
  }
  if (closetObjectIndex != -1)
  {
    Color cl = shade(scene, ray, closetObjectIndex, depth);
    // Ambiente Color
    Color ambColor = (scene.ambient_.color_) * (scene.shape_vector_[closetObjectIndex]->getMaterial()->ka_);
    
    //Tone mapping
    Color end = toneMapping(cl + ambColor);
    // Color end = cl + ambColor;
    return end;
  }
  else
    return Color{0.0f, 0.0f, 0.0f};
}

Color Renderer::shade(Scene const &scene, Ray const &ray, int closest, int depth)
{
  // Difusse Refektion
  float t;
  Hit h = scene.shape_vector_[closest]->intersectHit(ray, t);
  Color diffuColor = {0.0, 0.0, 0.0};
  Color spekColor = {0.0, 0.0, 0.0};
  Color reflecColor = {0.0, 0.0, 0.0};
  // Fuer beliebig vielen Lichtquellen
  for (int i = 0; i < scene.light_vector_.size(); ++i)
  {
    glm::vec3 lightVec = glm::normalize(scene.light_vector_[i]->origin_ - h.schnittPunkt_);
    Ray lightHitRay{h.schnittPunkt_, lightVec};
    lightHitRay.origin_ += lightHitRay.direction_ * (float)0.001;
    bool imSchatten = false;
    // float t;
    float t1;
    // Check if lightVec have intersection with another Shape
    for (int a = 0; a < scene.shape_vector_.size(); ++a)
    {
      if (a != closest && imSchatten != true)
      {
        imSchatten = scene.shape_vector_[a]->intersectHit(lightHitRay, t1).hit_;
        if (t1 < 0)
        {
          imSchatten = false;
        }
      }
    }

    // When no intersect, put light :D
    if (imSchatten == false)
    {
      float cosPhi = std::max(glm::dot(h.normalVector_, lightVec), 0.0f);
      Color lightIntensity{scene.light_vector_[i]->color_.r * scene.light_vector_[i]->brightness_, scene.light_vector_[i]->color_.g * scene.light_vector_[i]->brightness_, scene.light_vector_[i]->color_.b * scene.light_vector_[i]->brightness_};
      diffuColor += (lightIntensity) * (scene.shape_vector_[closest]->getMaterial()->kd_) * cosPhi;

      // Spekulare Licht
      glm::vec3 reflekLichtVektor = glm::normalize(2 * glm::dot(h.normalVector_, lightVec) * (h.normalVector_) - lightVec);
      float cosBeta = std::max(glm::dot(reflekLichtVektor, -ray.direction_), 0.0f);
      spekColor += (lightIntensity) * (scene.shape_vector_[closest]->getMaterial()->ks_) * std::pow(cosBeta, scene.shape_vector_[closest]->getMaterial()->m_);

      // Spiegelung
      if (depth >= 0)
      {
        if (scene.shape_vector_[closest]->getMaterial()->m_ > 0)
        {
          glm::vec3 reflecVec = glm::normalize(2 * glm::dot(h.normalVector_, ray.direction_) * (h.normalVector_) - ray.direction_);
          Ray reflecRay{h.schnittPunkt_, reflecVec};
          reflecRay.origin_ += reflecRay.direction_ * (float)0.001;
          depth -= 1;
          reflecColor = trace(scene, reflecRay, depth);
        }
      }
    }
  }

  // End color
  Color endColor = diffuColor + spekColor + reflecColor;
  return endColor;
}

Color Renderer::toneMapping(Color const &color)
{
  Color outColor = {0.0f, 0.0f, 0.0f};
  outColor.r = color.r / (color.r + 1);
  outColor.g = color.g / (color.g + 1);
  outColor.b = color.b / (color.b + 1);

  return outColor;
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
