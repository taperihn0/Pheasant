#include "window.h"
#include "assert.h"
#include "log.h"

namespace Phs
{

// https://github.com/glfw/glfw/issues/2036 by @wintertime
bool glfwIsInitialized() {
   (void)glfwGetKeyScancode(0);
   return glfwGetError(nullptr) != GLFW_NOT_INITIALIZED;
}

Window::Window()
   : _window(nullptr)
   , _width(_InvalidWindowWidth)
   , _height(_InvalidWindowHeight)
   , _focus(false)
   , _title(_DefaultWindowTitle)
   , _initialized(false)
{}

Window::Window(uint width, uint height, const std::string& title)
   : Window()
{ 
   bool status = init(width, height, title);
   PHS_ASSERT_LOG(status, "Window initialization end with a failure");
}

bool Window::init(uint width, uint height, const std::string& title) 
{
   PHS_CORE_LOG_INFO("Initializing a new Window...");

   // initialize GLFW context
   if (!glfwInit())
   {
      PHS_CORE_LOG_FATAL("Failed to initialize GLFW context!");
      return false;
   }

   glfwSetErrorCallback(errorCallback);

   // Using modern GLFW version (3)
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   _window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

   if (!_window)
   {
      PHS_CORE_LOG_FATAL("Failed to create a new GLFW window!");
      return false;
   }

   _initialized = true;
   return true;
}

Window::~Window()
{
   if (_window != nullptr)
      glfwDestroyWindow(_window);

   if (glfwIsInitialized())
      glfwTerminate();

   _initialized = false;
}

void Window::update()
{
   glfwPollEvents();
}

void Window::errorCallback(int error, const char* description) 
{
   // TODO: Proper error handling by the app abstraction
   PHS_CORE_LOG_ERROR("GLFW error detected: code {}, description {}", error, description);
}

} // namespace Phs