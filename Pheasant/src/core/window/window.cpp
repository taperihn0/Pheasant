#include "window.h"
#include "assert.h"
#include "logger/log.h"
#include "render/render_frontend.h"
// TODO: make it configurable
#include "render/opengl/opengl_swapchain.h"

namespace Phs
{

static constexpr bool PhsWindowSUCCESS = 1;
static constexpr bool PhsWindowFAILURE = 0;

// specify default error handling code
template <EventCode EV_ERROR>
void __defaultEventCallback(EventError ev) 
{
   auto& err_data = ev.getErrorParams();
   PHS_CORE_LOG_ERROR("Error detected: code {}, description \"{}\"", err_data.code, err_data.description);
}

ErrorCallback EventCallbacks::error_callback = __defaultEventCallback<EV_ERROR>;

// https://github.com/glfw/glfw/issues/2036 by @wintertime
bool glfwIsInitialized() {
   (void)glfwGetKeyScancode(GLFW_KEY_0);
   return glfwGetError(nullptr) != GLFW_NOT_INITIALIZED;
}

Window::Window()
   : _native_window(nullptr)
   , _width(_InvalidWindowWidth)
   , _height(_InvalidWindowHeight)
   , _focus(false)
   , _suspended(true)
   , _title(_DefaultWindowTitle)
   , _initialized(false)
   , _input()
   , _close(false)
   , _swapchain(nullptr)
   , _callback_ptrs({ this, nullptr })
{}

Window::Window(uint width, uint height, const std::string& title)
   : Window()
{ 
   bool status = init(width, height, title);
   PHS_ASSERT_LOG(status, "Window initialization end with a failure");
}

bool Window::init(uint width, uint height, const std::string& title) 
{
   PHS_ASSERT_LOG(!_initialized, "Trying to initialize already initialized window!");

   // Initialize GLFW context
   if (!glfwInit())
   {
      PHS_CORE_LOG_FATAL("Failed to initialize GLFW context!");
      return false;
   }

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
   glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
   glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
   glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
   glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);
   glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
#ifdef PHS_DEBUG
   glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_TRUE);
#else
   glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_FALSE);
#endif
#ifdef PHS_OS_WINDOWS
   glfwWindowHint(GLFW_WIN32_KEYBOARD_MENU, GLFW_TRUE);
#elif defined(PHS_OS_MACOS)
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

   _width = width;
   _height = height;

   _native_window = glfwCreateWindow(_width, _height, title.c_str(), nullptr, nullptr);

   if (!_native_window)
   {
      PHS_CORE_LOG_FATAL("Failed to create a new GLFW window!");
      return PhsWindowFAILURE;
   }

   glfwMakeContextCurrent(_native_window);

   // _callback_ptrs lifetime is same as the lifetime of *this object.
   void* data = reinterpret_cast<void*>(&_callback_ptrs);
   glfwSetWindowUserPointer(_native_window, data);

   // initialize render state
   // TODO: make it configurable
   bool render_init_status = Render::initialize(RENDER_GRAPHICS_API_OPENGL);
   PHS_ASSERT_LOG(render_init_status, "Failed to initialize render");
   _swapchain = std::make_unique<SwapchainOpenGL>(_native_window, _width, _height);

   _input.setWindow(_native_window);

   // GLFW_FOCUSED set
   _focus = true;
   _suspended = false;
   _initialized = true;

   PHS_CORE_LOG_INFO("Successfully initialized a new GLFW window.");
   return PhsWindowSUCCESS;
}

Window::~Window()
{
   Render::shutdown();

   if (_native_window) 
      glfwDestroyWindow(_native_window);

   if (glfwIsInitialized())
      glfwTerminate();

   _initialized = false;
}

void Window::update()
{
   PHS_ASSERT(_initialized);
   _input.pollEvents();
   _swapchain->present();
}

bool Window::isOpen()
{
   PHS_ASSERT(_initialized);
   return !_close;
}

bool Window::isSuspended()
{
   PHS_ASSERT(_initialized);
   return _suspended;
}

void Window::__setWidth(uint width)
{
   PHS_ASSERT(_initialized);
   _width = width;
}

void Window::__setHeight(uint height)
{
   PHS_ASSERT(_initialized);
   _height = height;
}

void Window::__setFocus(bool value)
{
   PHS_ASSERT(_initialized);
   _focus = value;
}

void Window::__setSuspended(bool value)
{
   PHS_ASSERT(_initialized);
   _suspended = value;
}

void Window::__setClose(bool value)
{
   PHS_ASSERT(_initialized);
   _close = value;
}

uint Window::getWidth()
{
   PHS_ASSERT(_initialized);
   return _width;
}

uint Window::getHeight()
{
   PHS_ASSERT(_initialized);
   return _height;
}

void Window::setEventCallbacks(EventCallbacks* callbacks)
{
   PHS_ASSERT(_initialized);

   // GLFW user pointer is already binded, just change callbacks to these provided by the external caller
   _callback_ptrs.callbacks = callbacks;

   glfwSetErrorCallback(
      [](int code, const char* desc)
      {
         EventError ev;
         auto& err_data = ev.getErrorParams();
         err_data.code = code;
         err_data.description = desc;

         EventCallbacks::error_callback(ev);
      }
   );

   glfwSetWindowSizeCallback(_native_window,
      [](GLFWwindow* platform_native_window, int width, int height)
      {
         EventWindowResize ev;
         auto& winsize = ev.getWindowSizeParams();
         winsize.width = width;
         winsize.height = height;

         Window::__CallbackData* data = reinterpret_cast<Window::__CallbackData*>(glfwGetWindowUserPointer(platform_native_window));
         Window* window = data->window;
         const EventCallbacks* callbacks = data->callbacks;

         window->__setWidth(width);
         window->__setHeight(height);

         bool suspend = !width and !height;
         window->__setSuspended(suspend);
         
         if (suspend)
            PHS_CORE_LOG_TRACE("Window suspended");

         bool status = Render::windowResize(width, height);

         if (!status)
            PHS_CORE_LOG_FATAL_FULL_INFO("Got error code from resize code!");

         callbacks->window_resize_callback(ev);
      }
   );
   
   glfwSetWindowPosCallback(_native_window, 
      [](GLFWwindow* platform_native_window, int xpos, int ypos)
      {
         EventWindowMove ev;
         auto& winpos = ev.getWindowPosParams();
         winpos.x = xpos;
         winpos.y = ypos;
         
         Window::__CallbackData* data = reinterpret_cast<Window::__CallbackData*>(glfwGetWindowUserPointer(platform_native_window));
         PHS_UNUSED Window* window = data->window;
         const EventCallbacks* callbacks = data->callbacks;

         callbacks->window_move_callback(ev);
      }
   );
   
   glfwSetWindowFocusCallback(_native_window, 
      [](GLFWwindow* platform_native_window, int value)
      {
         EventWindowFocus ev;
         auto& winfocus = ev.getWindowFocusParams();
         winfocus.value = static_cast<bool>(value);
         
         Window::__CallbackData* data = reinterpret_cast<Window::__CallbackData*>(glfwGetWindowUserPointer(platform_native_window));
         Window* window = data->window;
         const EventCallbacks* callbacks = data->callbacks;

         window->__setFocus(value);

         callbacks->window_focus_callback(ev);
      }
   );

   glfwSetWindowCloseCallback(_native_window, 
      [](GLFWwindow* platform_native_window)
      {
         EventWindowClose ev;
         
         Window::__CallbackData* data = reinterpret_cast<Window::__CallbackData*>(glfwGetWindowUserPointer(platform_native_window));
         Window* window = data->window;
         const EventCallbacks* callbacks = data->callbacks;

         window->__setClose(true);

         callbacks->window_close_callback(ev);
      }
   );

   glfwSetKeyCallback(_native_window, 
      [](GLFWwindow* platform_native_window, int key, PHS_UNUSED int scancode, int action, int mods)
      {
         Window::__CallbackData* data = reinterpret_cast<Window::__CallbackData*>(glfwGetWindowUserPointer(platform_native_window));
         PHS_UNUSED Window* window = data->window;
         const EventCallbacks* callbacks = data->callbacks;

         switch (action)
         {
         case GLFW_PRESS:
         {
            EventKeyPress ev;
            auto& state = ev.getKeyboardKeyParams();
            state.key = key;
            state.mods = mods;
            callbacks->key_press_callback(ev);
            break;
         }
         case GLFW_REPEAT:
         {
            EventKeyRepeat ev;
            auto& state = ev.getKeyboardKeyParams();
            state.key = key;
            state.mods = mods;
            callbacks->key_repeat_callback(ev);
            break;
         }
         case GLFW_RELEASE:
         {
            EventKeyRelease ev;
            auto& state = ev.getKeyboardKeyParams();
            state.key = key;
            state.mods = mods;
            callbacks->key_release_callback(ev);
            break;
         }
         default: break;
         }
      }
   );

   glfwSetCharCallback(_native_window, 
      [](GLFWwindow* platform_native_window, unsigned int codepoint)
      {
         EventKeyType ev;
         auto& state = ev.getKeyboardTypeParams();
         state.code = static_cast<type_char_t>(codepoint);
         
         Window::__CallbackData* data = reinterpret_cast<Window::__CallbackData*>(glfwGetWindowUserPointer(platform_native_window));
         PHS_UNUSED Window* window = data->window;
         const EventCallbacks* callbacks = data->callbacks;

         callbacks->key_type_callback(ev);
      }
   );

   glfwSetMouseButtonCallback(_native_window, 
      [](GLFWwindow* platform_native_window, int button, int action, int mods)
      {
         Window::__CallbackData* data = reinterpret_cast<Window::__CallbackData*>(glfwGetWindowUserPointer(platform_native_window));
         PHS_UNUSED Window* window = data->window;
         const EventCallbacks* callbacks = data->callbacks;

         switch (action)
         {
         case GLFW_PRESS:
         {
            EventMousePress ev;
            auto& state = ev.getMouseButtonParams();
            state.button = button;
            state.mods = mods;
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
            auto& state = ev.getMouseButtonParams();
            state.button = button;
            state.mods = mods;
            callbacks->mouse_release_callback(ev);
            break;
         }
         default: break;
         }
      }
   );

   glfwSetCursorPosCallback(_native_window, 
      [](GLFWwindow* platform_native_window, double xpos, double ypos)
      {
         EventMouseMove ev;
         auto& cursor = ev.getCursorParams();
         cursor.x = xpos;
         cursor.y = ypos;
         
         Window::__CallbackData* data = reinterpret_cast<Window::__CallbackData*>(glfwGetWindowUserPointer(platform_native_window));
         PHS_UNUSED Window* window = data->window;
         const EventCallbacks* callbacks = data->callbacks;

         callbacks->mouse_move_callback(ev);
      }
   );

   glfwSetScrollCallback(_native_window, 
      [](GLFWwindow* platform_native_window, double xoffset, double yoffset)
      {
         EventMouseScroll ev;
         auto& scroll = ev.getMouseScrollParams();
         scroll.xoff = xoffset;
         scroll.yoff = yoffset;
         
         Window::__CallbackData* data = reinterpret_cast<Window::__CallbackData*>(glfwGetWindowUserPointer(platform_native_window));
         PHS_UNUSED Window* window = data->window;
         const EventCallbacks* callbacks = data->callbacks;

         callbacks->mouse_scroll_callback(ev);
      }
   );
}

} // namespace Phs
