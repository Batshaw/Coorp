#include <renderer.hpp>
#include <window.hpp>
//#include "mingw-std-threads/mingw.thread.h"
#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

int main(int argc, char* argv[])
{
  unsigned const image_width = 800;
  unsigned const image_height = 600;
  std::string const filename = "./checkerboard.ppm";

  Renderer renderer{image_width, image_height, filename};

  //create separate thread to see updates of pixels while rendering
  renderer.render();

  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  return 0;
}
