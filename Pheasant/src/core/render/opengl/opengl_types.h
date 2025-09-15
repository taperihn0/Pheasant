#pragma once

#include "common.h"

#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Phs
{

extern class GLShaderUtils;

struct GLContext
{
   const uchar*      vendor;
   const uchar*      graphics_device;
   const uchar*      version;
   const uchar*      shader_lang_version;
   int               extension_count;
   int               context_profile_mask;
   int               context_features;
   bool              binary_shader_support;
   GLShaderUtils*    shader_man;
};

} // namespace Phs
