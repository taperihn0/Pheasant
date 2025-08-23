#pragma once

#include "defines.h"
#include "common.h"
#include "types.h"

#include <GLFW/glfw3.h>

namespace Phs
{

using PlatformWindow = GLFWwindow;

/* Cross-platform window handler class based on GLFW functionality.
*/
class PHEASANT_API Window
{
public:
   Window();
   Window(uint width, uint height, const std::string& title = std::string(_DefaultWindowTitle));
   ~Window();

   bool init(uint width, uint height, const std::string& title);

   void update();
private:
   static void errorCallback(int error, const char* description);

   static constexpr uint             _InvalidWindowWidth = 0;
   static constexpr uint             _InvalidWindowHeight = 0;
   static constexpr std::string_view _DefaultWindowTitle = "";

   PlatformWindow* _window;
   uint            _width;
   uint            _height;
   bool            _focus;
   std::string     _title;
   bool            _initialized;
};

} // namespace Phs
