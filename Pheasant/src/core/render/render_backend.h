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
   static PHS_INLINE void backendWindowResize();

   /* Calls platform-specific frame drawing.
   */
   static PHS_INLINE bool backendBeginFrame(RenderData& data);

   /* Calls platform-specific frame termination.
   */
   static PHS_INLINE bool backendEndFrame(RenderData& data);
};

} // namespace Phs

#include "render_backend.inl"
