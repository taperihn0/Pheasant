#pragma once

#include "opengl_shader.h"

namespace Phs
{

/* GLShaderUtils
*  Main shader assets manager.
*  Creates a shader object out of shader stages
*  and manages shader program.
*/
class GL_ShaderUtils
{
public:
   GL_ShaderUtils() = default;

   /* Loads, compiles and links distincts stage files
   *  creating a single shader object.
   *   - dir should be set to a shader assets directory
   *   - shader_name is name of the loaded shader.
   *  Every stage file is then searched.
   *  The file format should be: shader_name.appendix[vert|tessc|tesse|geom|frag|].extension[glsl]
   */
   bool loadShaderProgram(const FilePath& dir, const std::string& shader_name);
   bool bindShaderProgram();
private:
   static std::string _ShaderStageAppendix[ShaderStageCount];
   static std::string _GlslShaderStageExtension;
   GL_Shader           _shader_object;
};

} // namespace Phs
