#include "render_frontend.h"
#include "render_backend.h"
#include "assert.h"
#include "logger/log.h"

namespace Phs
{

static constexpr bool PhsFrontendSUCCESS = true;
static constexpr bool PhsFrontendFAILURE = false;

RenderGraphicsAPI        Render::_graphics_platform = RENDER_GRAPHICS_API_UNDEF;
bool                     Render::_initialized = false;
Render::BackendFunctions Render::_backend;

bool Render::initialize(RenderGraphicsAPI platform)
{
   PHS_ASSERT_LOG(!_initialized, "Trying to initialize already initialized render context!");
   PHS_ASSERT_LOG(isValid(platform), "Failed to load backend for undefined graphics API!");

   _graphics_platform = platform;
   loadBackend(platform);

   if (!_backend.initialize())
   {
      PHS_CORE_LOG_FATAL_FULL_INFO("Backend initialization resulted in error return code!");
      return PhsFrontendFAILURE;
   }

   _initialized = true;
   return PhsFrontendSUCCESS;
}

void Render::shutdown()
{
   PHS_ASSERT_LOG(_initialized, "Trying to terminate uninitialized render context!");
   _backend.shutdown();
   _graphics_platform = RENDER_GRAPHICS_API_UNDEF;
   _initialized = false;
}

bool Render::windowResize(uint width, uint height)
{
   PHS_ASSERT_LOG(_initialized, "Trying to call window resize on uninitialized render context!");
   return _backend.resize(width, height);
}

bool Render::drawFrame(RenderData& data)
{
   PHS_ASSERT_LOG(_initialized, "Trying to call frame drawing on uninitialized render context!");

   bool beg_frame_status = _backend.begin_frame(data);

   if (!beg_frame_status)
   {
      PHS_CORE_LOG_FATAL_FULL_INFO("BeginFrame resulted in an error return code!");
      return PhsFrontendFAILURE;
   }

   bool end_frame_status = _backend.end_frame(data);

   if (!end_frame_status)
   {
      PHS_CORE_LOG_FATAL_FULL_INFO("EndFrame resulted in an error return code!");
      return PhsFrontendFAILURE;
   }

   return PhsFrontendSUCCESS;
}

bool Render::clearScreen(float32_t red, float32_t green,
                         float32_t blue, float32_t alpha)
{
   PHS_ASSERT_LOG(_initialized, "Trying to call screen clearing on uninitialized render context!");
   return _backend.clear_scr(red, green, blue, alpha);
}

template <RenderGraphicsAPI GraphicsPlatform>
void Render::BackendFunctions::initializePlatformCallbacks()
{
   initialize  = RenderBackend<GraphicsPlatform>::backendInitialize;
   shutdown    = RenderBackend<GraphicsPlatform>::backendShutdown;
   resize      = RenderBackend<GraphicsPlatform>::backendWindowResize;
   begin_frame = RenderBackend<GraphicsPlatform>::backendBeginFrame;
   end_frame   = RenderBackend<GraphicsPlatform>::backendEndFrame;
   clear_scr   = RenderBackend<GraphicsPlatform>::backendClearScreen;
}

void Render::loadBackend(RenderGraphicsAPI platform)
{
   PHS_ASSERT_LOG(isValid(platform), "Failed to load backend for undefined graphics API!");

   switch (platform)
   {
   case RENDER_GRAPHICS_API_OPENGL:
      _backend.initializePlatformCallbacks<RENDER_GRAPHICS_API_OPENGL>();
      break;
   case RENDER_GRAPHICS_API_VULKAN:
      _backend.initializePlatformCallbacks<RENDER_GRAPHICS_API_VULKAN>();
      break;
   case RENDER_GRAPHICS_API_DIRECTX:
      _backend.initializePlatformCallbacks<RENDER_GRAPHICS_API_DIRECTX>();
      break;
   case RENDER_GRAPHICS_API_UNDEF:
   default:
      break;
   }
}

} // namespace Phs
