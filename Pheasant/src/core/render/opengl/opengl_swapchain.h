#pragma once

#include "common.h"
#include "render/render_swapchain.h"

extern struct GLFWwindow;

namespace Phs
{

/* Framebuffer manager (Swapchain) for OpenGL API.
*  Implementation of that is rather trivial, as long as we're relaying on GLFW library.
*/
class SwapchainOpenGL : public PlatformSwapchain
{
public:
   SwapchainOpenGL(GLFWwindow* window);
   void     present() override;
   uint32_t nextImage() override;
   uint32_t imageCount() const override;
private:
   static constexpr uint              _GLImageCount = 2;
   static constexpr RenderGraphicsAPI _GraphicsPlatform = RENDER_GRAPHICS_API_OPENGL;
   GLFWwindow*                        _window = nullptr;
};

} // namespace Phs
