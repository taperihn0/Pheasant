#include "render_backend.h"
#include "render/opengl/opengl_backend.h"

namespace Phs
{

template <RenderGraphicsAPI GraphicsPlatform>
PHS_INLINE bool RenderBackend<GraphicsPlatform>::backendInitialize()
{
   bool success = false;

   if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_OPENGL)
   {
      success = BackendOpenGL::platformInitialize();
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_VULKAN)
   {
      // TODO: support VULKAN API
      success = false;
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_DIRECTX)
   {
      // TODO: support DIRECTX API
      success = false;
   }

   return success;
}

template <RenderGraphicsAPI GraphicsPlatform>
PHS_INLINE void RenderBackend<GraphicsPlatform>::backendShutdown()
{
   if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_OPENGL)
   {
      BackendOpenGL::platformInitialize();
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_VULKAN)
   {
      // TODO: support VULKAN API
      return;
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_DIRECTX)
   {
      // TODO: support DIRECTX API
      return;
   }
}

template <RenderGraphicsAPI GraphicsPlatform>
PHS_INLINE void RenderBackend<GraphicsPlatform>::backendWindowResize()
{
   if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_OPENGL)
   {
      BackendOpenGL::platformInitialize();
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_VULKAN)
   {
      // TODO: support VULKAN API
      return;
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_DIRECTX)
   {
      // TODO: support DIRECTX API
      return;
   }
}

template <RenderGraphicsAPI GraphicsPlatform>
PHS_INLINE bool RenderBackend<GraphicsPlatform>::backendBeginFrame(RenderData& data)
{
   bool success = false;

   if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_OPENGL)
   {
      success = BackendOpenGL::platformBeginFrame(data);
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_VULKAN)
   {
      // TODO: support VULKAN API
      return false;
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_DIRECTX)
   {
      // TODO: support DIRECTX API
      return false;
   }

   return success;
}

template <RenderGraphicsAPI GraphicsPlatform>
PHS_INLINE bool RenderBackend<GraphicsPlatform>::backendEndFrame(RenderData& data)
{
   bool success = false;

   if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_OPENGL)
   {
      success = BackendOpenGL::platformEndFrame(data);
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_VULKAN)
   {
      // TODO: support VULKAN API
      return false;
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_DIRECTX)
   {
      // TODO: support DIRECTX API
      return false;
   }

   return success;
}

} // namespace Phs
