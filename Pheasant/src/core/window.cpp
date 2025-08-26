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
   , _input()
   , _close(false)
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

   // Initialize GLFW context
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

   _input.setWindow(_window);

   _initialized = true;
   return true;
}

Window::~Window()
{
   if (!_window)
      glfwDestroyWindow(_window);

   if (glfwIsInitialized())
      glfwTerminate();

   _initialized = false;
}

void Window::update()
{
   glfwPollEvents();
}

bool Window::isOpen()
{
   return !_close;
}

void Window::setEventCallbacks(EventCallbacks* callbacks)
{
   glfwSetWindowUserPointer(_window, reinterpret_cast<void*>(callbacks));

   glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height)
      {
         EventWindowResize ev;
         ev.winsize.width = width;
         ev.winsize.height = height;
         const EventCallbacks* callbacks = reinterpret_cast<EventCallbacks*>(glfwGetWindowUserPointer(window));
         callbacks->window_resize_callback(ev);
      }
   );
   
   glfwSetWindowPosCallback(_window, [](GLFWwindow* window, int xpos, int ypos)
      {
         EventWindowMove ev;
         ev.winpos.x = xpos;
         ev.winpos.y = ypos;
         const EventCallbacks* callbacks = reinterpret_cast<EventCallbacks*>(glfwGetWindowUserPointer(window));
         callbacks->window_move_callback(ev);
      }
   );
   
   glfwSetWindowFocusCallback(_window, [](GLFWwindow* window, int value)
      {
         EventWindowFocus ev;
         ev.winfocus.value = static_cast<bool>(value);
         const EventCallbacks* callbacks = reinterpret_cast<EventCallbacks*>(glfwGetWindowUserPointer(window));
         callbacks->window_focus_callback(ev);
      }
   );

   glfwSetWindowCloseCallback(_window, [](GLFWwindow* window)
      {
         EventWindowClose ev;
         const EventCallbacks* callbacks = reinterpret_cast<EventCallbacks*>(glfwGetWindowUserPointer(window));
         callbacks->window_close_callback(ev);
      }
   );

   glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, PHS_UNUSED int scancode, int action, int mods)
      {
         const EventCallbacks* callbacks = reinterpret_cast<EventCallbacks*>(glfwGetWindowUserPointer(window));

         switch (action)
         {
         case GLFW_PRESS:
         {
            EventKeyPress ev;
            ev.keybkeys.key = key;
            ev.keybkeys.mods = mods;
            callbacks->key_press_callback(ev);
            break;
         }
         case GLFW_REPEAT:
         {
            EventKeyRepeat ev;
            ev.keybkeys.key = key;
            ev.keybkeys.mods = mods;
            callbacks->key_repeat_callback(ev);
            break;
         }
         case GLFW_RELEASE:
         {
            EventKeyRelease ev;
            ev.keybkeys.key = key;
            ev.keybkeys.mods = mods;
            callbacks->key_release_callback(ev);
            break;
         }
         default: break;
         }
      }
   );

   glfwSetCharCallback(_window, [](GLFWwindow* window, unsigned int codepoint)
      {
         EventKeyType ev;
         ev.keybtype.code = static_cast<type_char_t>(codepoint);
         const EventCallbacks* callbacks = reinterpret_cast<EventCallbacks*>(glfwGetWindowUserPointer(window));
         callbacks->key_type_callback(ev);
      }
   );

   glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods)
      {
         const EventCallbacks* callbacks = reinterpret_cast<EventCallbacks*>(glfwGetWindowUserPointer(window));

         switch (action)
         {
         case GLFW_PRESS:
         {
            EventMousePress ev;
            ev.micekeys.button = button;
            ev.micekeys.mods = mods;
            callbacks->mouse_press_callback(ev);
            break;
         }
         case GLFW_REPEAT:
         {
            // Repeat action for mouse button currently 
            // not supported by GLFW nor Pheasant 
            break;
         }
         case GLFW_RELEASE:
         {
            EventMouseRelease ev;
            ev.micekeys.button = button;
            ev.micekeys.mods = mods;
            callbacks->mouse_release_callback(ev);
            break;
         }
         default: break;
         }
      }
   );

   glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xpos, double ypos)
      {
         EventMouseMove ev;
         ev.cursor.x = xpos;
         ev.cursor.y = ypos;
         const EventCallbacks* callbacks = reinterpret_cast<EventCallbacks*>(glfwGetWindowUserPointer(window));
         callbacks->mouse_move_callback(ev);
      }
   );

   glfwSetScrollCallback(_window, [](GLFWwindow* window, double xoffset, double yoffset)
      {
         EventMouseScroll ev;
         ev.micescroll.xoff = xoffset;
         ev.micescroll.yoff = yoffset;
         const EventCallbacks* callbacks = reinterpret_cast<EventCallbacks*>(glfwGetWindowUserPointer(window));
         callbacks->mouse_scroll_callback(ev);
      }
   );
}

void Window::errorCallback(int error, const char* description) 
{
   // TODO: Proper error handling by the app abstraction
   PHS_CORE_LOG_ERROR("GLFW error detected: code {}, description {}", error, description);
}

} // namespace Phs