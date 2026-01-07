#pragma once

/* opengl_types.h:
*  Here, graphics context of a OpenGL is declared.
*  Also, we're including GLAD as also GLFW headers.
*/

#include "common.h"
#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Phs
{

PHS_DECLARE class GL_ShaderUtils;

/* Storage of crucial OpenGL context info.
*  GLContext object is managed by the OpenGL backend.
*  Currently, only one shader is handled at a time.
*/
struct GL_Context
{
   const uchar*      vendor;
   const uchar*      graphics_device;
   const uchar*      version;
   const uchar*      shader_lang_version;
   int               extension_count;
   int               context_profile_mask;
   int               context_features;
   bool              binary_shader_support;
   GL_ShaderUtils*   shader_man;
};

} // namespace Phs
