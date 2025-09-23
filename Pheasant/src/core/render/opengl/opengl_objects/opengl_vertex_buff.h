#pragma once

#include "render/opengl/opengl_types.h"

namespace Phs
{

/* 
*/
class GL_VertexBuffer
{
public:
   GL_VertexBuffer() = default;
   GL_VertexBuffer(GLenum target, const void* data, size_t byte_size, GLenum usage);
   ~GL_VertexBuffer();

   bool create(GLenum target, const void* data, size_t byte_size, GLenum usage);
   void bind()   const;
   void unbind() const;
   void destroy();
private:
   static constexpr GLuint _GlUndefVBO = 0;
   static constexpr GLenum _GlUndefUsage = 0;
   GLuint                  _gl_vbo_num = _GlUndefVBO;
   GLenum                  _gl_usage = _GlUndefUsage;
};

} // namespace Phs
