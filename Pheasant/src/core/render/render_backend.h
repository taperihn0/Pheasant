#pragma once

#include "common.h"
#include "render_types.h"

namespace Phs
{

/* Render backend:
*  Manages communication between a main Renderer API and 
*  each of the graphics platform (OpenGL, Vulkan, DirectX)
*  specific calls.
*  'GraphicsPlatform' template parameter specifies which API to use.
*/
template <RenderGraphicsAPI GraphicsPlatform>
class RenderBackend
{
public:
   /* Calls platform-specific initialization policy.
   */
   static PHS_INLINE bool backendInitialize();

   /* Calls platform-specific termination policy.
   */
   static PHS_INLINE void backendShutdown();

   /* Calls platform-specific resize policy.
   */
   static PHS_INLINE bool backendWindowResize(uint width, uint height);

   /* Calls platform-specific frame drawing.
   */
   static PHS_INLINE bool backendBeginFrame(RenderData& data);

   /* Calls platform-specific frame termination.
   */
   static PHS_INLINE bool backendEndFrame(RenderData& data);

   /* Calls platform-specific screen clearing functions.
   */
   static PHS_INLINE bool backendClearScreen(float32_t red, float32_t green, 
                                             float32_t blue, float32_t alpha);
};

} // namespace Phs

#include "render_backend.inl"
