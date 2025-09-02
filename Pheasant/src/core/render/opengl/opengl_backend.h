#pragma once

/* opengl_backend.h already includes crucial files
*  for managing graphics platform context.
*/ 
#include "glad/glad.h"
#include "GLFW/glfw3.h"
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
   static bool platformInitialize();
   static void platformShutdown();
   static void platformWindowResize(uint width, uint height);
   static bool platformBeginFrame(RenderData& data);
   static bool platformEndFrame(RenderData& data);
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
