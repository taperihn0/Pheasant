#pragma once

#include "common.h"
#include "precompile.h"

namespace Phs
{
   
/* Frame rendering data containing crucial information about 
*  rendering policy.
*/
struct RenderData
{
   float delta_time;
};

/* Graphics API used by render backend side.
*/
enum RenderGraphicsAPI
{
   RENDER_GRAPHICS_API_UNDEF   = 0,
   RENDER_GRAPHICS_API_OPENGL  = 1,
   RENDER_GRAPHICS_API_VULKAN  = 2,
   RENDER_GRAPHICS_API_DIRECTX = 3,
};

static std::string_view toStr(RenderGraphicsAPI platform)
{
   switch (platform)
   {
   case RENDER_GRAPHICS_API_OPENGL:
      return "RENDER_GRAPHICS_API_OPENGL";
   case RENDER_GRAPHICS_API_VULKAN:
      return "RENDER_GRAPHICS_API_VULKAN";
   case RENDER_GRAPHICS_API_DIRECTX:
      return "RENDER_GRAPHICS_API_DIRECTX";
   case RENDER_GRAPHICS_API_UNDEF:
   default:
      break;
   }

   return "RENDER_GRAPHICS_API_UNDEF";
}

static bool isValid(RenderGraphicsAPI platform)
{
   return platform != RENDER_GRAPHICS_API_UNDEF;
}

} // namespace Phs
