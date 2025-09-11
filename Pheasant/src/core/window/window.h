#pragma once

#include "defines.h"
#include "common.h"
#include "event/event.h"
#include "input/input.h"
#include "render/render_swapchain.h"

namespace Phs
{

// Event callback type with one argument of Event<Code> type
template <EventCode Code>
using EventCallback = void(*)(Event<Code>);

using WindowErrorCallback   = EventCallback<EV_NONE>;

using ErrorCallback         = EventCallback<EV_ERROR>;

using WindowResizeCallback  = EventCallback<EV_WINDOW_RESIZE>;
using WindowMoveCallback    = EventCallback<EV_WINDOW_MOVE>;
using WindowFocusCallback   = EventCallback<EV_WINDOW_FOCUS>;
using WindowCloseCallback   = EventCallback<EV_WINDOW_CLOSE>;

using KeyPressCallback      = EventCallback<EV_KEY_PRESSED>;
using KeyReleaseCallback    = EventCallback<EV_KEY_RELEASED>;
using KeyRepeateCallback    = EventCallback<EV_KEY_REPEATED>;
using KeyTypeCallback       = EventCallback<EV_KEY_TYPED>;

using MousePressCallback    = EventCallback<EV_MOUSE_BUTTON_PRESSED>;
using MouseReleaseCallback  = EventCallback<EV_MOUSE_BUTTON_RELEASED>;
using MouseMoveCallback     = EventCallback<EV_MOUSE_MOVED>;
using MouseScrollCallback   = EventCallback<EV_MOUSE_SCROLLED>;

// default code for handling each event
// does nothing for default (except error event - see template specialization in window.cpp)
template <EventCode Code>
void __defaultEventCallback(PHS_UNUSED Event<Code>) {}

struct EventCallbacks
{
   static ErrorCallback  error_callback;

   WindowResizeCallback  window_resize_callback = __defaultEventCallback<EV_WINDOW_RESIZE>;
   WindowMoveCallback    window_move_callback   = __defaultEventCallback<EV_WINDOW_MOVE>;
   WindowFocusCallback   window_focus_callback  = __defaultEventCallback<EV_WINDOW_FOCUS>;
   WindowCloseCallback   window_close_callback  = __defaultEventCallback<EV_WINDOW_CLOSE>;

   KeyPressCallback      key_press_callback     = __defaultEventCallback<EV_KEY_PRESSED>;
   KeyReleaseCallback    key_release_callback   = __defaultEventCallback<EV_KEY_RELEASED>;
   KeyRepeateCallback    key_repeat_callback    = __defaultEventCallback<EV_KEY_REPEATED>;
   KeyTypeCallback       key_type_callback      = __defaultEventCallback<EV_KEY_TYPED>;

   MousePressCallback    mouse_press_callback   = __defaultEventCallback<EV_MOUSE_BUTTON_PRESSED>;
   MouseReleaseCallback  mouse_release_callback = __defaultEventCallback<EV_MOUSE_BUTTON_RELEASED>;
   MouseMoveCallback     mouse_move_callback    = __defaultEventCallback<EV_MOUSE_MOVED>;
   MouseScrollCallback   mouse_scroll_callback  = __defaultEventCallback<EV_MOUSE_SCROLLED>;
};

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
   bool        isOpen();
   bool        isSuspended();

   /* __setWidth / __setHeight methods do not really *resize* the window, but
   *  rather change internal state fields to match the actual size.
   *  Used internally by callbacks function on resize event.
   */
   void        __setWidth(uint width);
   void        __setHeight(uint height);
   /* Internal usage method.
   *  For more explanations, see Phs::Window::__setWidth and Phs::Window::__setHeight.
   */
   void        __setFocus(bool value);
   /* Internal usage method.
   *  For more explanations on internal usage, see Phs::Window::__setWidth and Phs::Window::__setHeight.
   */
   void        __setSuspended(bool value);
   /* Internal usage method.
   *  For more explanations on internal usage, see Phs::Window::__setWidth and Phs::Window::__setHeight.
   */
   void        __setClose(bool value);

   uint        getWidth();
   uint        getHeight();

   void        setEventCallbacks(EventCallbacks* callbacks);

   /* Internal data for callbacks.
   *  window pointer should be set to this.
   */
   struct __CallbackData
   {
      Window* const   window;
      EventCallbacks* callbacks;
   };
private:
   static constexpr uint              _InvalidWindowWidth = 0;
   static constexpr uint              _InvalidWindowHeight = 0;
   static constexpr std::string_view  _DefaultWindowTitle = "Title";

   GLFWwindow*                        _native_window;
   uint                               _width;
   uint                               _height;
   bool                               _focus;
   bool                               _suspended;
   std::string                        _title;
   bool                               _initialized;
   Input                              _input;
   bool                               _close;
   std::unique_ptr<PlatformSwapchain> _swapchain;
   __CallbackData                     _callback_ptrs;
};

} // namespace Phs
