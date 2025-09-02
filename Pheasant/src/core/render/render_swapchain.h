#pragma once

#include "common.h"
#include "render/render_types.h"

namespace Phs
{

/* Base class for future implementations for different graphics platforms.
*  The base class is designed to match the lowest common denominator, which is 
*  Vulkan API in that specific case.
*/
class PlatformSwapchain
{
public:
   virtual bool     resize(uint width, uint height) = 0;
   virtual void     present()                       = 0;
   virtual uint32_t nextImage()                     = 0;
   virtual uint32_t imageCount() const              = 0;
private:
   static constexpr RenderGraphicsAPI _GraphicsPlatform = RENDER_GRAPHICS_API_UNDEF;
};

} // namespace Phs
