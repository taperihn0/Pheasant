#pragma once

#include "filesystem/filesystem.h"
#include "opengl_types.h"
#include "precompile.h"
#include "render/render_shader_types.h"

namespace Phs
{

/* Represents OpenGL specific shader stage object.
*  shader_type can be one of these:
*  - SHADER_STAGE_VERTEX          (GL_VERTEX_SHADER)
*  - SHADER_STAGE_TESS_CONTROL    (GL_TESS_CONTROL_SHADER)
*  - SHADER_STAGE_TESS_EVALUATION (GL_TESS_EVALUATION_SHADER)
*  - SHADER_STAGE_GEOMETRY        (GL_GEOMETRY_SHADER)
*  - SHADER_STAGE_FRAGMENT        (GL_FRAGMENT_SHADER)
*  Uses SPIR-V during the compilation process.
*/
class GLStageObject
{
public:
   GLStageObject();
   GLStageObject(std::string_view path, ShaderStage shader_type);

   bool compile(std::string_view path, ShaderStage shader_type);
   bool close();
   bool isCompiled() const;
   bool attachTo(GLuint gl_shader_program) const;
   bool detach(GLuint gl_shader_program) const;
private:
   bool compileSource(const char* source_content, GLenum gl_shader_type);

   static constexpr GLenum _UndefGlShaderStage = 0;
   static constexpr GLuint _UndefGlShaderNum = 0;
   FilePath                _path;
   GLuint                  _gl_shader_stage;
   GLenum                  _gl_shader_type;
   bool                    _compiled;
};

/* OpenGL shader program.
*  Represents rendering pipeline and allows to specify 
*  programable pipeline stages.
*  GLShader object got its OpenGL number during the initialization,
*  and it can be used until the object is not destroyed by the program scope/heap deallocation.
*  That means even after calling close() the program can be freely used with another stages.
*/
class GLShader
{
public:
   GLShader();
   ~GLShader();

   bool close();
   bool specifyStage(std::string_view path, ShaderStage stage);
   bool linkProgram();
private:
   static constexpr GLuint _UndefGlShaderProgramNum = 0;
   static constexpr size_t _ShaderStageCount = 5;
   GLStageObject           _shader_stages[_ShaderStageCount];
   GLuint                  _gl_shader_program;
   bool                    _linked;
};

} // namespace Phs
