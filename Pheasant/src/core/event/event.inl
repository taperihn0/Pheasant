#include "event.h"
#include "precompile.h"

namespace Phs
{

template <>
PHS_INLINE EventError::ErrorParams& EventError::getErrorParams()
{
   return _error;
}

template <>
PHS_INLINE EventWindowResize::WindowSizeParams& EventWindowResize::getWindowSizeParams()
{
   return _winsize;
}

template <>
PHS_INLINE EventWindowMove::WindowPosParams& EventWindowMove::getWindowPosParams()
{
   return _winpos;
}

template <>
PHS_INLINE EventWindowFocus::WindowFocusParams& EventWindowFocus::getWindowFocusParams()
{
   return _winfocus;
}

template <EventCode Code>
PHS_INLINE typename Event<Code>::KeyboardKeyParams& Event<Code>::getKeyboardKeyParams()
{
   PHS_STATIC_ASSERT(Code == EV_KEY_PRESSED  or
                     Code == EV_KEY_RELEASED or
                     Code == EV_KEY_REPEATED);
   return _keybkeys;
}

template <>
PHS_INLINE EventKeyType::KeyboardTypeParams& EventKeyType::getKeyboardTypeParams()
{
   return _keybtype;
}

template <EventCode Code>
PHS_INLINE typename Event<Code>::MouseButtonParams& Event<Code>::getMouseButtonParams()
{
   PHS_STATIC_ASSERT(Code == EV_MOUSE_BUTTON_PRESSED or
                     Code == EV_MOUSE_BUTTON_RELEASED);
   return _micekeys;
}

template <>
PHS_INLINE EventMouseMove::CursorParams& EventMouseMove::getCursorParams()
{
   return _cursor;
}

template <>
PHS_INLINE EventMouseScroll::MouseScrollParams& EventMouseScroll::getMouseScrollParams()
{
   return _micescroll;
}

} // namespace Phs
