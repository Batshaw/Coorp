  Renderer::Renderer(Scene const& scene)
  : width_(scene._width)
  , height_(scene._height)
  , color_buffer_(scene._width*scene._height, Color(0.0, 0.0, 0.0))
  , filename_(scene._name)
  , ppm_(scene._width, scene._height)
{}
