#include "precompile.h"
#include "application.h"
#include "log.h"

namespace Phs {

Application::Application()
	: _window(std::make_unique<Window>())
	, _running(true)
{
	// TODO: Move that instuction to a safe place.
	Log::init();
	_window->init(800, 600, "Hello GLFW");
}

void Application::run()
{
	PHS_CORE_LOG_TRACE("Welcome to Pheasant from Visual Studio with CMake!");

	while (_running)
	{
		_window->update();
	}
}

} // namespace Phs
