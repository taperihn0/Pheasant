#pragma once

#include "common.h"
#include "precompile.h"

namespace Phs
{

/* Platform agnostic shader stages.
*/
enum ShaderStage : uint8_t
{
   SHADER_STAGE_MIN             = 0,
   SHADER_STAGE_VERTEX          = 0,
   SHADER_STAGE_TESS_CONTROL    = 1,
   SHADER_STAGE_TESS_EVALUATION = 2,
   SHADER_STAGE_GEOMETRY        = 3,
   SHADER_STAGE_FRAGMENT        = 4,
   SHADER_STAGE_MAX             = 4,
   SHADER_STAGE_UNDEF           = 5,
};

using ShaderStage_int_t = uint8_t;

static constexpr size_t ShaderStageCount = SHADER_STAGE_MAX + 1;

} // namespace Phs
