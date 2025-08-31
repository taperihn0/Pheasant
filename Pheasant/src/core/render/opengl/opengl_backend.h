#pragma once

#include "common.h"
#include "render/render_types.h"

namespace Phs
{

/* Frontside of OpenGL, being managed by main renderer backend.
*/
class BackendOpenGL
{
public:
   static PHS_INLINE bool platformInitialize();
   static PHS_INLINE void platformShutdown();
   static PHS_INLINE void platformWindowResize();
   static PHS_INLINE bool platformBeginFrame(RenderData& data);
   static PHS_INLINE bool platformEndFrame(RenderData& data);
private:
   static constexpr RenderGraphicsAPI GraphicsPlatform = RENDER_GRAPHICS_API_OPENGL;
};

} // namespace Phs

#include "opengl_backend.inl"
