#include "opengl_vertex_array.h"

namespace Phs
{

GL_VertexArray::~GL_VertexArray()
{
   glDeleteVertexArrays(1, &_gl_vao_num);
}

void GL_VertexArray::create()
{
   glGenVertexArrays(1, &_gl_vao_num);
   PHS_ASSERT(_gl_vao_num != _GlUndefVAO);
}

void GL_VertexArray::bind()
{
   PHS_ASSERT(_gl_vao_num != _GlUndefVAO);
   glBindVertexArray(_gl_vao_num);
}

void GL_VertexArray::unbind()
{
   PHS_ASSERT(_gl_vao_num != _GlUndefVAO);
   glBindVertexArray(_GlUndefVAO);
}

void GL_VertexArray::destroy()
{
   PHS_ASSERT(_gl_vao_num != _GlUndefVAO);
   glDeleteVertexArrays(1, &_gl_vao_num);
   _gl_vao_num = _GlUndefVAO;
}

} // namespace Phs
