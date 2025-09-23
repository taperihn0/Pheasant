#pragma once

#include "opengl_swapchain.h"
#include "logger/log.h"
#include "opengl_backend.h"
#include "window/window.h"

namespace Phs
{

GL_Swapchain::GL_Swapchain(GLFWwindow* native, uint width, uint height)
{
   PHS_ASSERT(native);

   _platform_native_window = native;

   bool status = resize(width, height);

   if (!status)
      PHS_CORE_LOG_FATAL_FULL_INFO("Failed to set size of the framebuffer");

   PHS_CORE_LOG_INFO("Successfully initialized swapchain for OpenGL platform");
}

bool GL_Swapchain::resize(uint width, uint height)
{
   PHS_ASSERT(_platform_native_window);
   bool status = GL_Backend::platformWindowResize(width, height);
   return status;
}

void GL_Swapchain::present()
{
   PHS_ASSERT(_platform_native_window);
   glfwSwapBuffers(_platform_native_window);
}

uint32_t GL_Swapchain::nextImage()
{
   PHS_ASSERT(_platform_native_window);
   return 0;
}

uint32_t GL_Swapchain::imageCount() const
{
   PHS_ASSERT(_platform_native_window);
   return _GLImageCount;
}

} // namespace Phs
