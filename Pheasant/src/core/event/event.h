#pragma once

#include "types.h"
#include "input/input.h"

namespace Phs 
{

/* Numeric codes for Event class template.
*  Each group is numered that each of them contain different shared bit.
*/
enum EventCode : uint16_t
{
   // Invalid event
   EV_NONE                  = 0x0,

   // EV_WINDOW_MIN_VALUE is equivalent EV_WINDOW_RESIZE
   EV_WINDOW_MIN_VALUE      = 0x1 << 1,
   EV_WINDOW_RESIZE         = 0x1 << 1,
   EV_WINDOW_MOVE           = 0x3 << 1,
   EV_WINDOW_FOCUS          = 0x5 << 1,
   EV_WINDOW_CLOSE          = 0x7 << 1, 

   // EV_KEY_MIN_VALUE is equivalent to EV_KEY_PRESSED
   EV_KEY_MIN_VALUE         = 0x1 << 2,
   EV_KEY_PRESSED           = 0x1 << 2,
   EV_KEY_RELEASED          = 0x3 << 2,
   EV_KEY_REPEATED          = 0x5 << 2,
   EV_KEY_TYPED             = 0x7 << 2,

   // EV_MOUSE_MIN_VALUE is equivalent to EV_MOUSE_BUTTON_PRESSED
   EV_MOUSE_MIN_VALUE       = 0x1 << 3,
   EV_MOUSE_BUTTON_PRESSED  = 0x1 << 3,
   EV_MOUSE_BUTTON_RELEASED = 0x3 << 3,
   EV_MOUSE_MOVED           = 0x5 << 3,
   EV_MOUSE_SCROLLED        = 0x7 << 3,
};

/* Event categories raw numeric values.
*  Corresponds to minimal value of each of the groups representing
*  different event (action) codes.
*/
enum EventCategory : uint16_t 
{
   EV_CATEGORY_NONE         = EV_NONE,           
   EV_CATEGORY_WINDOW       = EV_WINDOW_MIN_VALUE, 
   EV_CATEGORY_KEY          = EV_KEY_MIN_VALUE,    
   EV_CATEGORY_MOUSE        = EV_MOUSE_MIN_VALUE,  
};

// Returns category classification of a given 'evcode' event code
constexpr EventCategory getEventCodeCategory(EventCode evcode)
{
   uint16_t numcode = static_cast<uint16_t>(evcode);
   return static_cast<EventCategory>(onebit(numcode));
}

/* Native, raw Event datatype.
*  Stores information as event numeric code, its category and current handling state.
*/
template <EventCode Code>
class Event 
{
public:
   Event() = default;

   struct WindowSizeParams;
   struct WindowPosParams;
   struct WindowFocusParams;
   struct KeyboardKeyParams;
   struct KeyboardTypeParams;
   struct MouseButtonParams;
   struct CursorParams;
   struct MouseScrollParams;

   static constexpr PHS_INLINE EventCategory getCategory()               { return _Category; }
   static constexpr PHS_INLINE bool          isCategory(EventCategory c) { return _Category == c; }

   PHS_INLINE void                           handle()                    { _handled = true;  }
   PHS_INLINE void                           unhandle()                  { _handled = false; }

   /* Get event data parameters laying inside event context memory.
   *  The return value is reference to data field, which can be modified.
   *  The example usage of a methods below is:
   *  -----------------------------------------
   *  auto& event_data = event.getWindowSizeParams();
   *  event_data.width = EXAMPLE_WIDTH;
   *  event_data.height = EXAMPLE_HEIGHT;
   *  -----------------------------------------
   *  Linking error indicates a method is not implemented for given event.
   */
   PHS_INLINE WindowSizeParams&              getWindowSizeParams();
   PHS_INLINE WindowPosParams&               getWindowPosParams();
   PHS_INLINE WindowFocusParams&             getWindowFocusParams();
   PHS_INLINE KeyboardKeyParams&             getKeyboardKeyParams();
   PHS_INLINE KeyboardTypeParams&            getKeyboardTypeParams();
   PHS_INLINE MouseButtonParams&             getMouseButtonParams();
   PHS_INLINE CursorParams&                  getCursorParams();
   PHS_INLINE MouseScrollParams&             getMouseScrollParams();

   /* Event can be treated in many ways.
   *  Event context helps with accesing memory
   *  representing different event states, like 
   *  position or key parameters.
   */

   struct alignas(16) WindowSizeParams
   {
      int width;
      int height;
   };

   struct alignas(16) WindowPosParams
   {
      int x;
      int y;
   };

   struct alignas(16) WindowFocusParams
   {
      bool value;
   };

   struct alignas(16) KeyboardKeyParams
   {
      key_int_t key;
      // int scancode; - unused for now
      key_mode_int_t mods;
   };

   struct alignas(16) KeyboardTypeParams
   {
      type_char_t code;
   };

   struct alignas(16) MouseButtonParams
   {
      mouse_button_key_int_t button;
      // Mouse button mods are the same as key mods,
      // so the datatype is the same.
      key_mode_int_t mods;
   };

   struct alignas(16) CursorParams
   {
      double x;
      double y;
   };

   struct alignas(16) MouseScrollParams
   {
      double xoff;
      double yoff;
   };
private:
   static constexpr EventCode     _EventCode = Code;
   static constexpr EventCategory _Category  = getEventCodeCategory(_EventCode);
   bool                           _handled   = false;

   union /* EventContext */
   {
      WindowSizeParams   winsize;
      WindowPosParams    winpos;
      WindowFocusParams  winfocus;
      KeyboardKeyParams  keybkeys;
      KeyboardTypeParams keybtype;
      MouseButtonParams  micekeys;
      CursorParams       cursor;
      MouseScrollParams  micescroll;

      // Event context is 16 bytes long (128 bits)
      byte __b[16];
   };
};

/* Aliases of Event class templates.
*  Each alias corresponds to type Event<EVENT_CODE>, which is native, raw Event type.
*/

using EventNone          = Event<EV_NONE>;

// Aliases for window-group events
using EventWindowResize = Event<EV_WINDOW_RESIZE>;
using EventWindowMove   = Event<EV_WINDOW_MOVE>;
using EventWindowFocus  = Event<EV_WINDOW_FOCUS>;
using EventWindowClose  = Event<EV_WINDOW_CLOSE>;

// Aliases for key-group events
using EventKeyPress     = Event<EV_KEY_PRESSED>;
using EventKeyRelease   = Event<EV_KEY_RELEASED>;
using EventKeyRepeat    = Event<EV_KEY_REPEATED>;
using EventKeyType      = Event<EV_KEY_TYPED>;

// Aliases for mouse-group events.
// Mouse button and mouse actions are not differentiated.
using EventMousePress   = Event<EV_MOUSE_BUTTON_PRESSED>;
using EventMouseRelease = Event<EV_MOUSE_BUTTON_RELEASED>;
using EventMouseMove    = Event<EV_MOUSE_MOVED>;
using EventMouseScroll  = Event<EV_MOUSE_SCROLLED>;

} // namespace Phs

#include "event.inl"
