#pragma once

#include "common.h"
#include "render_types.h"

namespace Phs
{

/* Main rendering class.
*  Provides API for rendering resources.
*/
class Render 
{
public:
   /* Initializing rendering state.
   *  It is required to call this function before actually drawing anything.
   *  'platform' argument should be:
   *   - RENDER_GRAPHICS_API_OPENGL, 
   *   - RENDER_GRAPHICS_API_VULKAN,
   *   - RENDER_GRAPHICS_API_DIRECTX
   *  Returns true if context is initialized correctly, else false
   */
   static bool initialize(RenderGraphicsAPI platform);

   /* Clearing initialized state.
   *  Required to call this function before terminating.
   */
   static void shutdown();

   /* Adjusting rendering window to a new width and height.
   *  Required to call this function on window resize event.
   */
   static bool windowResize(uint width, uint height);

   /* Main rendering utility -
   *  submits a frame with a given data.
   */
   static bool drawFrame(RenderData& data);

   /* Clearing the screen.
   */
   static bool clearScreen(float32_t red, 
                           float32_t green, 
                           float32_t blue, 
                           float32_t alpha);
private:
   static void loadBackend(RenderGraphicsAPI platform);

   static RenderGraphicsAPI _graphics_platform;
   static bool              _initialized;

   /* Wraps specific backend template calls.
   */
   struct BackendFunctions 
   {
      template <RenderGraphicsAPI GraphicsPlatform>
      void initializePlatformCallbacks();

      using backend_initialize_func          = bool(*)();
      using backend_shutdown_func            = void(*)();
      using backend_window_resize_func       = bool(*)(uint, uint);
      using backend_begin_frame_func         = bool(*)(RenderData&);
      using backend_end_frame_func           = bool(*)(RenderData&);
      using backend_clear_func               = bool(*)(float32_t, float32_t, float32_t, float32_t);

      backend_initialize_func    initialize  = nullptr;
      backend_shutdown_func      shutdown    = nullptr;
      backend_window_resize_func resize      = nullptr;
      backend_begin_frame_func   begin_frame = nullptr;
      backend_end_frame_func     end_frame   = nullptr;
      backend_clear_func         clear_scr   = nullptr;
   };

   static BackendFunctions _backend;
};

} // namespace Phs
