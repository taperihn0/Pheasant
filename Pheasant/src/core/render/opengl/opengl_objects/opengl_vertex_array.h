#pragma once

#include "render/opengl/opengl_types.h"

namespace Phs
{

/* OpenGL's Vertex Array Object abstraction.
*/
class GL_VertexArray
{
public:
   GL_VertexArray() = default;
   ~GL_VertexArray();

   void create();
   void bind();
   void unbind();
   void destroy();
private:
   static constexpr GLuint _GlUndefVAO = 0;
   GLuint _gl_vao_num = _GlUndefVAO;
};

} // namespace Phs
