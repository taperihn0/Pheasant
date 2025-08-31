#include "render_frontend.h"
#include "render_backend.h"
#include "assert.h"
#include "logger/log.h"

namespace Phs
{

RenderGraphicsAPI        Render::_graphics_platform = RENDER_GRAPHICS_API_UNDEF;
bool                     Render::_initialized = false;
Render::BackendFunctions Render::_backend = {};

bool Render::initialize(RenderGraphicsAPI platform)
{
   PHS_ASSERT_LOG(!_initialized, "Trying to initialize already initialized render context!");
   PHS_ASSERT_LOG(isValid(platform), "Failed to load backend for undefined graphics API!");

   _graphics_platform = platform;
   loadBackend(platform);

   if (!_backend.initialize())
   {
      PHS_CORE_LOG_FATAL_FULL_INFO("Backend initialization resulted in error return code!");
      return false;
   }

   _initialized = true;
   return true;
}

void Render::shutdown()
{
   PHS_ASSERT_LOG(_initialized, "Trying to terminate uninitialized render context!");
   _backend.shutdown();
   _graphics_platform = RENDER_GRAPHICS_API_UNDEF;
   _initialized = false;
}

void Render::windowResize(uint width, uint height)
{
   PHS_ASSERT_LOG(_initialized, "Trying to call window resize on uninitialized render context!");
   _backend.resize();
}

bool Render::drawFrame(RenderData& data)
{
   PHS_ASSERT_LOG(_initialized, "Trying to call frame drawing on uninitialized render context!");

   bool beg_frame_status = _backend.begin_frame(data);

   if (!beg_frame_status)
   {
      PHS_CORE_LOG_FATAL_FULL_INFO("BeginFrame resulted in an error return code!");
      return false;
   }

   bool end_frame_status = _backend.end_frame(data);

   if (!end_frame_status)
   {
      PHS_CORE_LOG_FATAL_FULL_INFO("EndFrame resulted in an error return code!");
      return false;
   }

   return true;
}

void Render::loadBackend(RenderGraphicsAPI platform)
{
   PHS_ASSERT_LOG(isValid(platform), "Failed to load backend for undefined graphics API!");

   switch (platform)
   {
   case RENDER_GRAPHICS_API_OPENGL:
      _backend.initialize  = RenderBackend<RENDER_GRAPHICS_API_OPENGL>::backendInitialize;
      _backend.shutdown    = RenderBackend<RENDER_GRAPHICS_API_OPENGL>::backendShutdown;
      _backend.resize      = RenderBackend<RENDER_GRAPHICS_API_OPENGL>::backendWindowResize;
      _backend.begin_frame = RenderBackend<RENDER_GRAPHICS_API_OPENGL>::backendBeginFrame;
      _backend.end_frame   = RenderBackend<RENDER_GRAPHICS_API_OPENGL>::backendEndFrame;
      break;
   case RENDER_GRAPHICS_API_VULKAN:
      _backend.initialize  = RenderBackend<RENDER_GRAPHICS_API_VULKAN>::backendInitialize;
      _backend.shutdown    = RenderBackend<RENDER_GRAPHICS_API_VULKAN>::backendShutdown;
      _backend.resize      = RenderBackend<RENDER_GRAPHICS_API_VULKAN>::backendWindowResize;
      _backend.begin_frame = RenderBackend<RENDER_GRAPHICS_API_VULKAN>::backendBeginFrame;
      _backend.end_frame   = RenderBackend<RENDER_GRAPHICS_API_VULKAN>::backendEndFrame;
      break;
   case RENDER_GRAPHICS_API_DIRECTX:
      _backend.initialize  = RenderBackend<RENDER_GRAPHICS_API_DIRECTX>::backendInitialize;
      _backend.shutdown    = RenderBackend<RENDER_GRAPHICS_API_DIRECTX>::backendShutdown;
      _backend.resize      = RenderBackend<RENDER_GRAPHICS_API_DIRECTX>::backendWindowResize;
      _backend.begin_frame = RenderBackend<RENDER_GRAPHICS_API_DIRECTX>::backendBeginFrame;
      _backend.end_frame   = RenderBackend<RENDER_GRAPHICS_API_DIRECTX>::backendEndFrame;
      break;
   case RENDER_GRAPHICS_API_UNDEF:
   default:
      break;
   }
}

} // namespace Phs
