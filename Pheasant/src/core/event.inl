#include "event.h"
#include "precompile.h"

namespace Phs
{

template <EventCode Code>
Event<Code>::Event() 
   : _handled(false) 
{}

template <EventCode Code>
template <EventCode HandledEvent, typename Func>
PHS_INLINE void Event<Code>::dispatch(Func& handler)
{
   PHS_STATIC_ASSERT((isSameType<Func, bool()>()));

   if constexpr (HandledEvent == _EventCode)
   { 
      bool handled = handler();
      if (handled) handle();
   }
}

} // namespace Phs
