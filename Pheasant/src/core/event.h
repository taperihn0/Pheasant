#pragma once

#include "types.h"
#include "common.h"

namespace Phs 
{

enum EventCode : uint16_t
{
   // Invalid event
   EV_NONE                  = 0x0,

   // EV_WINDOW_MIN_VALUE is equivalent EV_WINDOW_RESIZE
   EV_WINDOW_MIN_VALUE      = 0x1 << 1,
   EV_WINDOW_RESIZE         = 0x1 << 1,
   EV_WINDOW_MOVE           = 0x3 << 1,
   EV_WINDOW_FOCUS          = 0x5 << 1,
   EV_WINDOW_UNFOCUS        = 0x7 << 1,
   EV_WINDOW_CLOSE          = 0x9 << 1, 

   // EV_KEY_MIN_VALUE is equivalent to EV_KEY_PRESSED
   EV_KEY_MIN_VALUE         = 0x1 << 2,
   EV_KEY_PRESSED           = 0x1 << 2,
   EV_KEY_RELEASED          = 0x3 << 2,
   EV_KEY_TYPED             = 0x5 << 2,

   // EV_MOUSE_MIN_VALUE is equivalent to EV_MOUSE_BUTTON_PRESSED
   EV_MOUSE_MIN_VALUE       = 0x1 << 3,
   EV_MOUSE_BUTTON_PRESSED  = 0x1 << 3,
   EV_MOUSE_BUTTON_RELEASED = 0x3 << 3,
   EV_MOUSE_MOVED           = 0x5 << 3,
   EV_MOUSE_SCROLLED        = 0x7 << 3,
};

enum EventCategory : uint16_t 
{
   EV_CATEGORY_NONE         = EV_NONE,           
   EV_CATEGORY_WINDOW       = EV_WINDOW_MIN_VALUE, 
   EV_CATEGORY_KEY          = EV_KEY_MIN_VALUE,    
   EV_CATEGORY_MOUSE        = EV_MOUSE_MIN_VALUE,  
};

EventCategory getEventCodeCategory(EventCode ev)
{
   uint16_t numcode = static_cast<uint16_t>(ev);
   return static_cast<EventCategory>(onebit(numcode));
}

template <EventCode Code>
class Event 
{
public:
   Event();

   static constexpr PHS_INLINE EventCategory getCategory()               { return _Category; }
   static constexpr PHS_INLINE bool          isCategory(EventCategory c) { return _Category == c; }

   PHS_INLINE void                           handle()                    { _handled = true;  }
   PHS_INLINE void                           unhandle()                  { _handled = false; }

   template <EventCode HandledEvent, typename Func>
   void dispatch(Func& handler);
private:
   static constexpr EventCode     _EventCode = Code;
   static constexpr EventCategory _Category = getEventCodeCategory(_EventCode);
   bool                           _handled;
};

using EventNone          = Event<EV_NONE>;

using EventWindowResize  = Event<EV_WINDOW_RESIZE>;
using EventWindowMove    = Event<EV_WINDOW_MOVE>;
using EventWindowFocus   = Event<EV_WINDOW_FOCUS>;
using EventWindowUnfocus = Event<EV_WINDOW_UNFOCUS>;
using EventWindowClose   = Event<EV_WINDOW_CLOSE>;

using EventKeyPressed    = Event<EV_KEY_PRESSED>;
using EventKeyReleased   = Event<EV_KEY_RELEASED>;
using EventKeyTyped      = Event<EV_KEY_TYPED>;

using EventMousePressed  = Event<EV_MOUSE_BUTTON_PRESSED>;
using EventMouseReleased = Event<EV_MOUSE_BUTTON_RELEASED>;
using EventMouseMoved    = Event<EV_MOUSE_MOVED>;
using EventMouseScrolled = Event<EV_MOUSE_SCROLLED>;

} // namespace Phs

#include "event.inl"
