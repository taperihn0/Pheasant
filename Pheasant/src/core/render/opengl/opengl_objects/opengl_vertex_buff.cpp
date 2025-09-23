#include "opengl_vertex_buff.h"

namespace Phs
{

GL_VertexBuffer::GL_VertexBuffer(GLenum target, const void* data, size_t byte_size, GLenum usage)
{
   create(target, data, byte_size, usage);
}

GL_VertexBuffer::~GL_VertexBuffer()
{
   glDeleteBuffers(1, &_gl_vbo_num);
}

bool GL_VertexBuffer::create(GLenum target, const void* data, size_t byte_size, GLenum usage)
{
   _gl_usage = usage;

   bind();
   glBufferData(target, byte_size, data, usage);

   return glGetError() != GL_NO_ERROR;
}

void GL_VertexBuffer::bind() const
{
   PHS_ASSERT(_gl_vbo_num != _GlUndefVBO);
   glBindBuffer(_gl_usage, _gl_vbo_num);
}

void GL_VertexBuffer::unbind() const
{
   PHS_ASSERT(_gl_vbo_num != _GlUndefVBO);
   glBindBuffer(_gl_usage, _GlUndefVBO);
}

void GL_VertexBuffer::destroy()
{
   PHS_ASSERT(_gl_vbo_num != _GlUndefVBO);
   glDeleteBuffers(1, &_gl_vbo_num);
   _gl_vbo_num = _GlUndefVBO;
   _gl_usage = _GlUndefUsage;
}

} // namespace Phs
