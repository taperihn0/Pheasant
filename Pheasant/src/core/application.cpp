#include "precompile.h"
#include "application.h"
#include "log.h"

#include <GLFW/glfw3.h>

namespace Phs {

void Application::run()
{
	bool debug;

#ifdef PHS_DEBUG
	debug = true;
#else
	debug = false;
#endif

#ifdef GLFWAPI
	Log::init();
	PHS_CORE_LOG_TRACE("Welcome to Pheasant from Visual Studio with CMake! The build is: {}", debug ? "DEBUG" : "RELEASE");
	PHS_CORE_LOG_TRACE("GLFWAPI defined");
#endif

	glfwInit(); // Works!

	while (true);
}

} // namespace Phs
