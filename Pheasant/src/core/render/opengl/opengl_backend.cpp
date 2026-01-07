#include "opengl_backend.h"
#include "logger/log.h"
#include "opengl_shader_man.h"

namespace Phs
{

static constexpr bool PhsGlSUCCESS = 1;
static constexpr bool PhsGlFAILURE = 0;

GL_Context GL_Backend::_gl_context;

bool GL_Backend::platformInitialize()
{
   // load OpenGL functions with GLAD loader
   bool glad_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

   if (!glad_status) {
      PHS_CORE_LOG_FATAL("Failed to initialize OpenGL context using GLAD!");
      return PhsGlFAILURE;
   }
   
   // store OpenGL state and report it to the console. For further reading see: 
   // https://www.khronos.org/opengl/wiki/OpenGL_Context#Context_information_queries
   const uchar* vendor = glGetString(GL_VENDOR);
   const uchar* device = glGetString(GL_RENDERER);
   const uchar* version = glGetString(GL_VERSION);
   const uchar* shader_version = glGetString(GL_SHADING_LANGUAGE_VERSION);

   int extension_count = 0;
   int profile_mask = 0;
   int features = 0;
   int binary_shader_num = 0;

   glGetIntegerv(GL_NUM_EXTENSIONS, &extension_count);
   glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile_mask);
   glGetIntegerv(GL_CONTEXT_FLAGS, &features);
   glGetIntegerv(GL_NUM_SHADER_BINARY_FORMATS, &binary_shader_num);

   _gl_context.vendor = vendor;
   _gl_context.graphics_device = device;
   _gl_context.version = version;
   _gl_context.shader_lang_version = shader_version;
   _gl_context.extension_count = extension_count;
   _gl_context.context_profile_mask = profile_mask;
   _gl_context.context_features = features;
   _gl_context.binary_shader_support = binary_shader_num;

   static constexpr std::string_view ContextProfileStr[2] = 
   {
      "GL_CONTEXT_CORE_PROFILE_BIT",
      "GL_CONTEXT_COMPATIBILITY_PROFILE_BIT"
   };

   PHS_CORE_LOG_TRACE("OpenGL info: ");
   PHS_CORE_LOG_TRACE("\tGL implementation provided by: {}", _gl_context.vendor);
   PHS_CORE_LOG_TRACE("\tGL hardware: {}", _gl_context.graphics_device);
   PHS_CORE_LOG_TRACE("\tGL version: {}", _gl_context.version);
   PHS_CORE_LOG_TRACE("\tGL shader language version: {}", _gl_context.shader_lang_version);
   PHS_CORE_LOG_TRACE("\tGL extension count (unloaded): {}", _gl_context.extension_count);
   PHS_CORE_LOG_TRACE("\tGL context profile: {}", ContextProfileStr[_gl_context.context_profile_mask]);

   std::string features_str;

   if (_gl_context.context_features & GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT)
      features_str +=  "GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT";
   if (_gl_context.context_features & GL_CONTEXT_FLAG_DEBUG_BIT)
      features_str += " GL_CONTEXT_FLAG_DEBUG_BIT";
   if (_gl_context.context_features & GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT)
      features_str += " GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT";
   if (_gl_context.context_features & GL_CONTEXT_FLAG_NO_ERROR_BIT)
      features_str += " GL_CONTEXT_FLAG_NO_ERROR_BIT";

   PHS_CORE_LOG_TRACE("\tGL context features: {}", features_str);
   PHS_CORE_LOG_TRACE("\tGL binary shader loading: {}", _gl_context.binary_shader_support ? "SUPPORTED" : "NOT SUPPORTED");

   PHS_CORE_LOG_INFO("Successfully loaded OpenGL context using GLAD.");

   // allocate shader manager
   _gl_context.shader_man = new GL_ShaderUtils;

   // Load shaders assets, compile and link them
   const FilePath shader_assets_path = FilePath::getCurrentDirectory()
                                                 .stepInto("assets")
                                                 .stepInto("shaders");

   bool status = _gl_context.shader_man->loadShaderProgram(shader_assets_path, "default_shader");

   return status;
}

void GL_Backend::platformShutdown()
{
   PHS_CORE_LOG_TRACE("GL backend: shuting down");
   // deallocate shader manager
   delete _gl_context.shader_man;
}

bool GL_Backend::platformWindowResize(uint width, uint height)
{
   glViewport(0, 0, width, height);
   GLenum status = glGetError();
   PHS_CORE_LOG_TRACE("GL backend resize to ({}, {}): {}", width, height, status == GL_NO_ERROR ? "success" : "failure");
   return status == GL_NO_ERROR;
}

bool GL_Backend::platformBeginFrame(RenderData& data)
{
   return PhsGlFAILURE;
}

bool GL_Backend::platformEndFrame(RenderData& data)
{
   return PhsGlFAILURE;
}

bool GL_Backend::platformClearScreen(float32_t red, float32_t green,
                                        float32_t blue, float32_t alpha)
{
   glClearColor(red, green, blue, alpha);
   glClear(GL_COLOR_BUFFER_BIT);
   return PhsGlSUCCESS;
}

} // namespace Phs
