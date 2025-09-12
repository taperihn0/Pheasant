#pragma once

#include "common.h"

namespace Phs
{

struct GLContext
{
   const uchar* vendor;
   const uchar* graphics_device;
   const uchar* version;
   const uchar* shader_lang_version;
   int          extension_count;
   int          context_profile_mask;
   int          context_features;
   bool         binary_shader_support;
};

} // namespace Phs
