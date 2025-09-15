#pragma once

#include "opengl_shader.h"

namespace Phs
{

class GLShaderUtils
{
public:
   GLShaderUtils() = default;
   bool loadShaderProgram(const FilePath& dir, const std::string& shader_name);
   bool bindShaderProgram();
private:
   static std::string _ShaderStageAppendix[ShaderStageCount];
   static std::string _GlslShaderStageExtension;
   GLShader           _shader_object;
};

} // namespace Phs
