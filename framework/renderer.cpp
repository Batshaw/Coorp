// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(Scene const &scene)
    : scene_(scene), width_(scene._width), height_(scene._height), color_buffer_(scene._width * scene._height, Color(0.0, 0.0, 0.0)), filename_(scene._name), ppm_(scene._width, scene._height){};

/* void Renderer::render()
void Renderer::render()
{
  std::size_t const checker_pattern_size = 20;

  for (unsigned y = 0; y < height_; ++y)
  {
    for (unsigned x = 0; x < width_; ++x)
    {
      Pixel p(x, y);
      if (((x / checker_pattern_size) % 2) != ((y / checker_pattern_size) % 2))
      {
        p.color = Color(0.0, 1.0, float(x) / height_);
      }
      else
      {
        p.color = Color(1.0, 0.0, float(y) / width_);
      }

      write(p);
    }
  }
  ppm_.save(filename_);
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

  Color temp{0.0, 0.0, 0.0};
  float dist = 0;
  float dmin = 1000;

  float is_intersect = true;
  int closest_object_index = -1;

  for (int i = 0; i < scene_.shape_vector.size(); ++i)
  {
    is_intersect = (*scene_.shape_vector[i]).intersect(ray, dist);
    //cout<<distance<<endl;
    if (is_intersect)
    {
      cout << "true" << endl;

      if (dist < dmin)
      {
        dmin = dist;
        closest_object_index = i;
      }
    }
  }
  if (closest_object_index != -1)
  {
    cout << "nicht intersection" << endl;
    return (scene_.shape_vector[closest_object_index])->get_material_()->ka_;
  }

  else
  {
    return Color{0, 0, 0};
  }
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
