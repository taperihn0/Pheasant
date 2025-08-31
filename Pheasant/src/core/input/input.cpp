#include "input.h"
#include "precompile.h"

// From glfw3.h
#define PHS_RELEASE 0 /* GLFW_RELEASE */
#define PHS_PRESS   1 /* GLFW_PRESS   */
#define PHS_REPEAT  2 /* GLFW_REPEAT  */

namespace Phs
{

Input::Input(GLFWwindow* window)
{
   setWindow(window);
}

void Input::setWindow(GLFWwindow* window)
{
   PHS_ASSERT(window);
   _window = window;
}

bool Input::isMouseButtonDown(mouse_button_key_int_t button)
{
   PHS_ASSERT(_window);
   state_int_t state = mouseButtonState(button);
   return state == PHS_RELEASE;
}

bool Input::isMouseButtonUp(mouse_button_key_int_t button)
{
   PHS_ASSERT(_window);
   state_int_t state = mouseButtonState(button);
   return state == PHS_PRESS;
}

double Input::mousePosX()
{
   PHS_ASSERT(_window);
   double x, y;
   glfwGetCursorPos(_window, &x, &y);
   return x;
}

double Input::mousePosY()
{
   PHS_ASSERT(_window);
   double x, y;
   glfwGetCursorPos(_window, &x, &y);
   return y;
}

bool Input::isKeyDown(key_int_t key)
{
   PHS_ASSERT(_window);
   state_int_t state = keyState(key);
   return state == PHS_PRESS;
}

bool Input::isKeyUp(key_int_t key)
{
   PHS_ASSERT(_window);
   state_int_t state = keyState(key);
   return state == PHS_RELEASE;
}

Input::state_int_t Input::mouseButtonState(mouse_button_key_int_t button)
{
   PHS_ASSERT(_window);
   state_int_t state = glfwGetMouseButton(_window, button);
   return state;
}

Input::state_int_t Input::keyState(key_int_t key)
{
   PHS_ASSERT(_window);
   state_int_t state = glfwGetKey(_window, key);
   return state;
}

} // namespace Phs
