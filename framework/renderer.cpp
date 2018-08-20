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
  for(unsigned y = 0; y < height_; ++y){
    for(unsigned x = 0; x < width_; ++x){
      Pixel pixel(x, y);
      Ray ray = scene.camera.rayThroughPixel(x, y, width_, height_);
      pixel.color = trace(scene, ray);
      write(pixel);
    }
  }
  ppm_.save(filename_);
}

Color Renderer::trace(Scene const& scene, Ray const& ray){
  Camera camera = {scene.camera};
  Color temp{1.0f, 1.0f, 1.0f,};
  float distance = 0;
  float dmin = 1000;

  bool is_intersect = true;
  int closetObjectIndex = -1;

  for(int i = 0; i < scene.shape_vector.size(); ++i){
    is_intersect = (*scene.shape_vector[i]).intersect(ray, distance);
    if(is_intersect){
      if( distance < dmin){
        dmin = distance;
        closetObjectIndex = i;
        return (scene.shape_vector[closetObjectIndex])->getMaterial()->kd_;
      }
    }
    else return Color{0.0f, 0.0f, 0.0f};
  }
  // if(closetObjectIndex != -1){
  //   cout << "nicht intersection" << endl;
  //   return (scene.shape_vector[closetObjectIndex])->getMaterial()->kd_;
  // }
  // else return Color{0.0f, 0.0f, 0.0f};
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
