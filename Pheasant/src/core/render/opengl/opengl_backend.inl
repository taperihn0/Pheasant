#pragma once

#include "opengl_backend.h"

namespace Phs
{

PHS_INLINE bool BackendOpenGL::platformInitialize()
{
   return false;
}

PHS_INLINE void BackendOpenGL::platformShutdown()
{
   return;
}

PHS_INLINE void BackendOpenGL::platformWindowResize()
{
   return;
}

PHS_INLINE bool BackendOpenGL::platformBeginFrame(RenderData& data)
{
   return false;
}

PHS_INLINE bool BackendOpenGL::platformEndFrame(RenderData& data)
{
   return false;
}

} // namespace Phs
