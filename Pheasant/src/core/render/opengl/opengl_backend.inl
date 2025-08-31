#pragma once

#include "opengl_backend.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "logger/log.h"

namespace Phs
{

PHS_INLINE bool BackendOpenGL::platformInitialize()
{
   bool glad_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

   if (!glad_status) {
      PHS_CORE_LOG_FATAL("Failed to initialize OpenGL context using GLAD!");
      return false;
   }

   PHS_CORE_LOG_INFO("Successfully loaded OpenGL context using GLAD.");
   return true;
}

PHS_INLINE void BackendOpenGL::platformShutdown()
{
   return;
}

PHS_INLINE void BackendOpenGL::platformWindowResize()
{
   return;
}

PHS_INLINE bool BackendOpenGL::platformBeginFrame(RenderData& data)
{
   return false;
}

PHS_INLINE bool BackendOpenGL::platformEndFrame(RenderData& data)
{
   return false;
}

} // namespace Phs
