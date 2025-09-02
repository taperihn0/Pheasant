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
enum RenderGraphicsAPI : uint8_t
{
   RENDER_GRAPHICS_API_UNDEF   = 0,
   RENDER_GRAPHICS_API_OPENGL  = 1,
   RENDER_GRAPHICS_API_VULKAN  = 2,
   RENDER_GRAPHICS_API_DIRECTX = 3,
   RENDER_GRAPHICS_API_MAX     = 3,
};

static constexpr uint GraphicsPlatformCount = 4;

static constexpr PHS_INLINE uint8_t graphicsPlatformCode(RenderGraphicsAPI platform)
{
   return static_cast<uint8_t>(platform);
}

static std::string_view toStr(RenderGraphicsAPI platform)
{
   static constexpr std::string_view strbuff[GraphicsPlatformCount] = {
      "RENDER_GRAPHICS_API_UNDEF",
      "RENDER_GRAPHICS_API_OPENGL",
      "RENDER_GRAPHICS_API_VULKAN",
      "RENDER_GRAPHICS_API_DIRECTX"
   };

   return strbuff[graphicsPlatformCode(platform)];
}

static bool isValid(RenderGraphicsAPI platform)
{
   return platform != RENDER_GRAPHICS_API_UNDEF;
}

} // namespace Phs
