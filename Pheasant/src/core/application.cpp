#include "precompile.h"
#include "application.h"
#include "log.h"

namespace Phs 
{

void Application::windowResizeCallback(EventWindowResize ev)
{
	PHS_CORE_LOG_DEBUG("Window resize callback: width {}, height {}", ev.winsize.width, ev.winsize.height);
}

void Application::windowMoveCallback(EventWindowMove ev)
{
	PHS_CORE_LOG_DEBUG("Window move callback: x {}, y {}", ev.winpos.x, ev.winpos.y);
}

void Application::windowFocusCallback(EventWindowFocus ev)
{
	PHS_CORE_LOG_DEBUG("Window focus callback: focus {}", ev.winfocus.value ? "gained" : "lost");
}

void Application::windowCloseCallback(PHS_UNUSED EventWindowClose ev)
{
	PHS_CORE_LOG_DEBUG("Window callback: CLOSE");
}

void Application::keyPressCallback(EventKeyPress ev)
{
	PHS_CORE_LOG_DEBUG("Key press callback: key {}", ev.keybkeys.key);
}

void Application::keyReleaseCallback(EventKeyRelease ev)
{
	PHS_CORE_LOG_DEBUG("Key release callback: key {}", ev.keybkeys.key);
}

void Application::keyRepeatCallback(EventKeyRepeat ev) 
{
	PHS_CORE_LOG_DEBUG("Key repeat callback: key {}", ev.keybkeys.key);
}

void Application::keyTypeCallback(EventKeyType ev)
{
	PHS_CORE_LOG_DEBUG("Key type callback: code {}", ev.keybtype.code);
}

void Application::mousePressCallback(EventMousePress ev)
{ 
	PHS_CORE_LOG_DEBUG("Mouse press callback: button {}, mods {}", ev.micekeys.button, ev.micekeys.mods);
}

void Application::mouseReleaseCallback(EventMouseRelease ev)
{
	PHS_CORE_LOG_DEBUG("Mouse release callback: button {}, mods {}", ev.micekeys.button, ev.micekeys.mods);
}

void Application::mouseMoveCallback(EventMouseMove ev)
{
	PHS_CORE_LOG_DEBUG("Mouse move callback: x {}, y {}", ev.cursor.x, ev.cursor.y);
}

void Application::mouseScrollCallback(EventMouseScroll ev)
{
	PHS_CORE_LOG_DEBUG("Mouse scoll callback: xoff {}, yoff {}", ev.micescroll.xoff, ev.micescroll.yoff);
}

Application::Application()
	: _window(std::make_unique<Window>())
	, _callbacks(std::make_unique<EventCallbacks>())
{
	// TODO: Move that instuction to a safe place.
	Log::init();
	_window->init(800, 600, "Hello GLFW");

	_callbacks->window_resize_callback  = windowResizeCallback;
	_callbacks->window_move_callback    = windowMoveCallback;
	_callbacks->window_focus_callback   = windowFocusCallback;
	_callbacks->window_close_callback   = windowCloseCallback;

	_callbacks->key_press_callback      = keyPressCallback;
	_callbacks->key_release_callback    = keyReleaseCallback;
	_callbacks->key_repeat_callback     = keyRepeatCallback;
	_callbacks->key_type_callback		   = keyTypeCallback;

	_callbacks->mouse_press_callback    = mousePressCallback;
	_callbacks->mouse_release_callback  = mouseReleaseCallback;
	_callbacks->mouse_move_callback     = mouseMoveCallback;
	_callbacks->mouse_scroll_callback   = mouseScrollCallback;

	_window->setEventCallbacks(_callbacks.get());
}

void Application::run()
{
	PHS_CORE_LOG_TRACE("Welcome to Pheasant from Visual Studio with CMake!");

	while (_window->isOpen())
	{
		_window->update();
	}
}

} // namespace Phs
