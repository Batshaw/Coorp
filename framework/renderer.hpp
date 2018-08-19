// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "Scene.hpp"
#include "color.hpp"
#include "Ray.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "Scene.hpp"
#include <string>
#include <glm/glm.hpp>
#include "Hit.hpp"
#include "Camera.hpp"

class Renderer
{
public:
  //Renderer(unsigned w, unsigned h, std::string const& file);
  Renderer(Scene const &scene);

  void render();
  void render(Scene const &scene);
  void render_test(Camera const &camera, Material const &material, Sphere const &sphere, Color const &ambiente, Light const &light);

  Color trace(Ray const &ray, unsigned int depth_) const;
  void write(Pixel const &p);

  inline std::vector<Color> const &color_buffer() const
  {
    return color_buffer_;
  }

private:
  Scene scene_;
  unsigned width_;
  unsigned height_;
  Scene scene_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
};

#endif // #ifndef BUW_RENDERER_HPP
