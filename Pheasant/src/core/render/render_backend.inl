#include "render_backend.h"
#include "render/opengl/opengl_backend.h"

namespace Phs
{

static constexpr bool PhsBackendSUCCESS = 1;
static constexpr bool PhsBackendFAILURE = 0;

template <RenderGraphicsAPI GraphicsPlatform>
PHS_INLINE bool RenderBackend<GraphicsPlatform>::backendInitialize()
{
   bool status = PhsBackendFAILURE;

   if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_OPENGL)
   {
      status = GL_Backend::platformInitialize();
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_VULKAN)
   {
      // TODO: support VULKAN API
      status = PhsBackendFAILURE;
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_DIRECTX)
   {
      // TODO: support DIRECTX API
      status = PhsBackendFAILURE;
   }

   return status;
}

template <RenderGraphicsAPI GraphicsPlatform>
PHS_INLINE void RenderBackend<GraphicsPlatform>::backendShutdown()
{
   if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_OPENGL)
   {
      GL_Backend::platformShutdown();
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
PHS_INLINE bool RenderBackend<GraphicsPlatform>::backendWindowResize(uint width, uint height)
{
   bool status = PhsBackendFAILURE;

   if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_OPENGL)
   {
      status = GL_Backend::platformWindowResize(width, height);
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_VULKAN)
   {
      // TODO: support VULKAN API
      return PhsBackendFAILURE;
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_DIRECTX)
   {
      // TODO: support DIRECTX API
      return PhsBackendFAILURE;
   }

   return status;
}

template <RenderGraphicsAPI GraphicsPlatform>
PHS_INLINE bool RenderBackend<GraphicsPlatform>::backendBeginFrame(RenderData& data)
{
   bool status = PhsBackendFAILURE;

   if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_OPENGL)
   {
      status = GL_Backend::platformBeginFrame(data);
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_VULKAN)
   {
      // TODO: support VULKAN API
      return PhsBackendFAILURE;
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_DIRECTX)
   {
      // TODO: support DIRECTX API
      return PhsBackendFAILURE;
   }

   return status;
}

template <RenderGraphicsAPI GraphicsPlatform>
PHS_INLINE bool RenderBackend<GraphicsPlatform>::backendEndFrame(RenderData& data)
{
   bool status = PhsBackendFAILURE;

   if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_OPENGL)
   {
      status = GL_Backend::platformEndFrame(data);
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_VULKAN)
   {
      // TODO: support VULKAN API
      return PhsBackendFAILURE;
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_DIRECTX)
   {
      // TODO: support DIRECTX API
      return PhsBackendFAILURE;
   }

   return status;
}

template <RenderGraphicsAPI GraphicsPlatform>
PHS_INLINE bool RenderBackend<GraphicsPlatform>::backendClearScreen(float32_t red, float32_t green,
                                                                    float32_t blue, float32_t alpha)
{
   bool status = PhsBackendFAILURE;

   if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_OPENGL)
   {
      status = GL_Backend::platformClearScreen(red, green, blue, alpha);
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_VULKAN)
   {
      // TODO: support VULKAN API
      return PhsBackendFAILURE;
   }
   else if constexpr (GraphicsPlatform == RENDER_GRAPHICS_API_DIRECTX)
   {
      // TODO: support DIRECTX API
      return PhsBackendFAILURE;
   }

   return status;
}

} // namespace Phs
