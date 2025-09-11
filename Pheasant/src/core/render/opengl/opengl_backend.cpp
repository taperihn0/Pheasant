#pragma once

#include "opengl_backend.h"
#include "logger/log.h"

namespace Phs
{

static constexpr bool PhsGlSUCCESS = 1;
static constexpr bool PhsGlFAILURE = 0;

BackendOpenGL::GLContext BackendOpenGL::_gl_context;

bool BackendOpenGL::platformInitialize()
{
   // load OpenGL functions with GLAD loader
   bool glad_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

   if (!glad_status) {
      PHS_CORE_LOG_FATAL("Failed to initialize OpenGL context using GLAD!");
      return PhsGlFAILURE;
   }
   
   // store OpenGL state and report it to the console
   const uchar* vendor = glGetString(GL_VENDOR);
   const uchar* device = glGetString(GL_RENDERER);
   const uchar* version = glGetString(GL_VERSION);
   const uchar* shader_version = glGetString(GL_SHADING_LANGUAGE_VERSION);
   int gl_extension_count = 0;
   glGetIntegerv(GL_NUM_EXTENSIONS, &gl_extension_count);

   _gl_context.vendor = vendor;
   _gl_context.graphics_device = device;
   _gl_context.version = version;
   _gl_context.shader_lang_version = shader_version;
   _gl_context.extension_count = gl_extension_count;

   PHS_CORE_LOG_TRACE("OpenGL info: ");
   PHS_CORE_LOG_TRACE("\tGL implementation provided by: {}", _gl_context.vendor);
   PHS_CORE_LOG_TRACE("\tRenderer hardware: {}", _gl_context.graphics_device);
   PHS_CORE_LOG_TRACE("\tGL version: {}", _gl_context.version);
   PHS_CORE_LOG_TRACE("\tGL shader language version: {}", _gl_context.shader_lang_version);
   PHS_CORE_LOG_TRACE("\tCurrent available GL extension count (unloaded): {}", _gl_context.extension_count);

   PHS_CORE_LOG_INFO("Successfully loaded OpenGL context using GLAD.");
   return PhsGlSUCCESS;
}

void BackendOpenGL::platformShutdown()
{
   return;
}

bool BackendOpenGL::platformWindowResize(uint width, uint height)
{
   glViewport(0, 0, width, height);
   GLenum status = glGetError();
   PHS_CORE_LOG_TRACE("GL backend resize to ({}, {}): {}", width, height, status == GL_NO_ERROR ? "success" : "failure");
   return status == GL_NO_ERROR;
}

bool BackendOpenGL::platformBeginFrame(RenderData& data)
{
   return PhsGlFAILURE;
}

bool BackendOpenGL::platformEndFrame(RenderData& data)
{
   return PhsGlFAILURE;
}

bool BackendOpenGL::platformClearScreen(float32_t red, float32_t green,
                                        float32_t blue, float32_t alpha)
{
   glClearColor(red, green, blue, alpha);
   glClear(GL_COLOR_BUFFER_BIT);
   return PhsGlSUCCESS;
}

} // namespace Phs
