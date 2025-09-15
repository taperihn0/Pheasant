#pragma once

#include "filesystem/filesystem.h"
#include "precompile.h"
#include "opengl_types.h"
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

   bool compile(const char* path, const char* source_content, ShaderStage shader_type);
   bool close();
   bool isCompiled() const;
   bool attachTo(GLuint gl_shader_program) const;
   bool detach(GLuint gl_shader_program) const;
private:
   bool compileSource(const char* path, const char* source_content, GLenum gl_shader_type);

   static constexpr GLenum _UndefGlShaderStage = 0;
   static constexpr GLuint _UndefGlShaderNum = 0;
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
   bool compileAttachStage(const char* source_path, const char* source, ShaderStage stage);
   bool linkProgram();
   bool bind();
private:
   GLStageObject           _shader_stages[ShaderStageCount];
   GLuint                  _gl_shader_program;
   bool                    _linked;
};

} // namespace Phs
