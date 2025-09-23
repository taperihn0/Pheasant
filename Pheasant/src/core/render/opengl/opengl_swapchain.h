#pragma once

#include "render/render_swapchain.h"

// forward declaration of a platform-independent window.
extern struct GLFWwindow;

namespace Phs
{

/* Framebuffer manager (Swapchain) for OpenGL API.
*  Implementation of that is rather trivial, as long as we're relaying on GLFW library.
*/
class GL_Swapchain : public PlatformSwapchain
{
public:
   GL_Swapchain(GLFWwindow* native, uint width, uint height);
   bool     resize(uint width, uint height) override;
   void     present()                       override;
   uint32_t nextImage()                     override;
   uint32_t imageCount() const              override;
private:
   static constexpr uint              _GLImageCount = 2;
   static constexpr RenderGraphicsAPI _GraphicsPlatform = RENDER_GRAPHICS_API_OPENGL;
   /* SwapchainOpenGL instance holds GLFW native window pointer for framebuffer swapping:
   *  for now, it completely relies on GLFW library.
   */
   GLFWwindow*                        _platform_native_window = nullptr;
};

} // namespace Phs
