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

  Color background{0.0, 0.0, 0.0};

  Hit hit = get_closest(scene_, ray);

  if (hit.isHit_)
  {
    Color current_color = (hit.obj_)->get_material_()->ka_;
    return current_color;
  }
  else
  {
    return background;
  }

  /*   float dist = 0;
  float dmin = 1000;

  bool is_intersect = true;
  int closest_object_index = -1;

  //Get closest object that is hit by ray
  for (int i = 0; i < scene_.shape_vector.size(); ++i)
  {
    is_intersect = (*scene_.shape_vector[i]).intersect(ray, dist);
    //cout<<distance<<endl;
    if (is_intersect)
    {
#if PRINT_DEBUG_INFO
      cout << "true" << endl;
#endif

      if (dist < dmin)
      {
        dmin = dist;
        closest_object_index = i;
      }
    }
  }

  if (closest_object_index != -1)
  {
#if PRINT_DEBUG_INFO
    cout << "nicht intersection" << endl;
#endif

    return (scene_.shape_vector[closest_object_index])->get_material_()->ka_;
  }

  else
  {
    return Color{0, 0, 0};
  } */
}

Hit Renderer::get_closest(Scene const &scene_, Ray const &ray) const
{

  Hit current_hit;
  Hit closest_hit;

  for (std::shared_ptr<Shape> shapes_ptr : scene_.shape_vector)
  {
    current_hit = (*shapes_ptr).intersect(ray);

    if (current_hit.distance_ < closest_hit.distance_)
    {
      closest_hit = current_hit;
    }
  }

  return closest_hit;
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

Color Renderer::shade(std::shared_ptr<Shape> const &shape, Ray const &ray, float &distance) const
{
  glm::vec3 x_point = get_point(distance,ray);

  return Color{1.0, 1.0, 1.0};
}

Color Renderer::evaluate_diffusion(Light const &light, std::shared_ptr<Shape> const &shape, Ray const &ray, float &distance) const
{
  glm::vec3 normal = get_point(distance,ray);
  return Color{1.0, 1.0, 1.0};
}

Color Renderer::evaluate_color(std::shared_ptr<Shape> const &shape, glm::vec3 const &cut, glm::vec3 const &normal, Scene const &scene, Ray const &ray) const
{
  Color result{1.0f, 1.0f, 1.0f};
  return result;
}