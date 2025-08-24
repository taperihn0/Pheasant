#pragma once

#include "defines.h"
#include "common.h"
#include "types.h"
#include "event.h"

#include <GLFW/glfw3.h>

namespace Phs
{

// Event callback type with one argument of Event<Code> type
template <EventCode Code>
using EventCallback = void(*)(Event<Code>);

using WindowResizeCallback  = EventCallback<EV_WINDOW_RESIZE>;
using WindowMoveCallback    = EventCallback<EV_WINDOW_MOVE>;
using WindowFocusCallback   = EventCallback<EV_WINDOW_FOCUS>;
using WindowCloseCallback   = EventCallback<EV_WINDOW_CLOSE>;

using KeyPressCallback      = EventCallback<EV_KEY_PRESSED>;
using KeyReleaseCallback    = EventCallback<EV_KEY_RELEASED>;
using KeyRepeateCallback   = EventCallback<EV_KEY_REPEATED>;
using KeyTypeCallback       = EventCallback<EV_KEY_TYPED>;

using MousePressCallback    = EventCallback<EV_MOUSE_BUTTON_PRESSED>;
using MouseReleaseCallback  = EventCallback<EV_MOUSE_BUTTON_RELEASED>;
using MouseMoveCallback     = EventCallback<EV_MOUSE_MOVED>;
using MouseScrollCallback   = EventCallback<EV_MOUSE_SCROLLED>;

template <EventCode Code>
void _defaultEventCallback(PHS_UNUSED Event<Code>) {}

struct EventCallbacks
{
   WindowResizeCallback  window_resize_callback  = _defaultEventCallback<EV_WINDOW_RESIZE>;
   WindowMoveCallback    window_move_callback    = _defaultEventCallback<EV_WINDOW_MOVE>;
   WindowFocusCallback   window_focus_callback   = _defaultEventCallback<EV_WINDOW_FOCUS>;
   WindowCloseCallback   window_close_callback   = _defaultEventCallback<EV_WINDOW_CLOSE>;

   KeyPressCallback      key_press_callback    = _defaultEventCallback<EV_KEY_PRESSED>;
   KeyReleaseCallback    key_release_callback   = _defaultEventCallback<EV_KEY_RELEASED>;
   KeyRepeateCallback    key_repeat_callback   = _defaultEventCallback<EV_KEY_REPEATED>;
   KeyTypeCallback       key_type_callback      = _defaultEventCallback<EV_KEY_TYPED>;

   MousePressCallback    mouse_press_callback    = _defaultEventCallback<EV_MOUSE_BUTTON_PRESSED>;
   MouseReleaseCallback  mouse_release_callback  = _defaultEventCallback<EV_MOUSE_BUTTON_RELEASED>;
   MouseMoveCallback     mouse_move_callback     = _defaultEventCallback<EV_MOUSE_MOVED>;
   MouseScrollCallback   mouse_scroll_callback   = _defaultEventCallback<EV_MOUSE_SCROLLED>;
};

using PlatformWindow = GLFWwindow;

/* Cross-platform window handler class based on GLFW library.
*/
class PHEASANT_API Window
{
public:
   Window();
   Window(uint width, uint height, 
          const std::string& title = std::string(_DefaultWindowTitle));
   ~Window();

   bool        init(uint width, uint height, const std::string& title);
   void        update();

   void        setEventCallbacks(EventCallbacks* callbacks);
private:
   static void errorCallback(int error, const char* description);

   static constexpr uint             _InvalidWindowWidth = 0;
   static constexpr uint             _InvalidWindowHeight = 0;
   static constexpr std::string_view _DefaultWindowTitle = "Title";

   PlatformWindow* _window;
   uint            _width;
   uint            _height;
   bool            _focus;
   std::string     _title;
   bool            _initialized;
};

} // namespace Phs
