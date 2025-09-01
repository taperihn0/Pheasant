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
   /* Initialize OpenGL rendering context and store initialization data
   *  for future read.
   */
   static            bool platformInitialize();
   static PHS_INLINE void platformShutdown();
   static PHS_INLINE void platformWindowResize();
   static PHS_INLINE bool platformBeginFrame(RenderData& data);
   static PHS_INLINE bool platformEndFrame(RenderData& data);
private:
   struct GLContext
   {
      const uchar* vendor;
      const uchar* graphics_device;
      const uchar* version;
      const uchar* shader_lang_version;
      int          extension_count;
   };

   static GLContext                   _gl_context;
   static constexpr RenderGraphicsAPI _GraphicsPlatform = RENDER_GRAPHICS_API_OPENGL;
};

} // namespace Phs

#include "opengl_backend.inl"
