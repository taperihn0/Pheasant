#pragma once

#include "opengl_swapchain.h"
#include "GLFW/glfw3.h"
#include "logger/log.h"

namespace Phs
{

SwapchainOpenGL::SwapchainOpenGL(GLFWwindow* window)
{
   PHS_ASSERT(window);
   _window = window;
   PHS_CORE_LOG_TRACE("Successfully initialized swapchain for OpenGL platform");
}

void SwapchainOpenGL::present()
{
   PHS_ASSERT(_window);
   glfwSwapBuffers(_window);
}

uint32_t SwapchainOpenGL::nextImage()
{
   PHS_ASSERT(_window);
   return 0;
}

uint32_t SwapchainOpenGL::imageCount() const
{
   return _GLImageCount;
}

} // namespace Phs
