#pragma once

/* opengl_backend.h already includes crucial files
*  for managing graphics platform context.
*/ 
#include "render/render_types.h"
#include "opengl_types.h"

namespace Phs
{

/* Frontside of OpenGL, being managed by main renderer backend.
*/
class GL_Backend
{
public:
   /* Initialize OpenGL rendering context and store initialization data
   *  for future read.
   */
   static bool platformInitialize();
   static void platformShutdown();
   static bool platformWindowResize(uint width, uint height);
   static bool platformBeginFrame(RenderData& data);
   static bool platformEndFrame(RenderData& data);
   static bool platformClearScreen(float32_t red, 
                                   float32_t green, 
                                   float32_t blue, 
                                   float32_t alpha);
private:
   static constexpr RenderGraphicsAPI _GraphicsPlatform = RENDER_GRAPHICS_API_OPENGL;
   static GL_Context                  _gl_context;
};

} // namespace Phs
