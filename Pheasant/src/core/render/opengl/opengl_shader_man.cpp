#include "opengl_shader_man.h"

namespace Phs
{

static constexpr bool PhsGlShaderManSUCCESS = 1;
static constexpr bool PhsGlShaderManFAILURE = 0;

std::string GL_ShaderUtils::_ShaderStageAppendix[ShaderStageCount] =
{
   "vert", "tessc", "tesse", "geom", "frag"
};
std::string GL_ShaderUtils::_GlslShaderStageExtension = "glsl";

bool GL_ShaderUtils::loadShaderProgram(const FilePath& dir, const std::string& shader_name)
{
   FilePath stage_file;

   for (ShaderStage_int_t stagei = SHADER_STAGE_MIN; stagei <= SHADER_STAGE_MAX; stagei++)
   {
      // shader stage files are of the format:
      // shader_name.appendix.extension
      std::string shader_stage_name = shader_name 
                                      + '.' + _ShaderStageAppendix[stagei] 
                                      + '.' + _GlslShaderStageExtension;

      stage_file = dir.stepInto(shader_stage_name);

      PHS_CORE_LOG_INFO("Looking for shader stage file: {}...", stage_file);

      File_Read file;

      if (!file.open(stage_file, FILE_MODE_BINARY))
      {
         PHS_CORE_LOG_ERROR("Failed to load shader stage source: {}", stage_file);
         continue;
      }
      
      std::unique_ptr<FileToken> source_content;
      size_t size;

      if (!file.read(source_content, size))
      {
         PHS_CORE_LOG_ERROR("Failed to read shader stage source: {}", stage_file);
         continue;
      }

      ShaderStage shader_stage = static_cast<ShaderStage>(stagei);

      if (!_shader_object.compileAttachStage(stage_file.toCStr(), reinterpret_cast<const char*>(source_content.get()), shader_stage))
      {
         PHS_CORE_LOG_ERROR("Failed to compile and attach shader stage");
         return PhsGlShaderManFAILURE;
      }
   }

   PHS_CORE_LOG_TRACE("Successfully loaded shader program.");
   return PhsGlShaderManSUCCESS;
}

bool GL_ShaderUtils::bindShaderProgram()
{
   return _shader_object.bind();
}

} // namespace Phs
