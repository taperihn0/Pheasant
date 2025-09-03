#include "precompile.h"
#include "application.h"
#include "logger/log.h"
#include "render/render_frontend.h"

#include "math/vec.h"

namespace Phs 
{

void Application::errorCallback(EventError ev)
{
	auto& err_data = ev.getErrorParams();
	PHS_CORE_LOG_ERROR("GLFW error detected: code {}, description \"{}\"", err_data.code, err_data.description);
}

void Application::windowResizeCallback(EventWindowResize ev)
{
	//auto& winsize = ev.getWindowSizeParams();
	//PHS_CORE_LOG_DEBUG("Window resize callback: width {}, height {}", winsize.width, winsize.height);
}

void Application::windowMoveCallback(EventWindowMove ev)
{
	//auto& winpos = ev.getWindowPosParams();
	//PHS_CORE_LOG_DEBUG("Window move callback: x {}, y {}", winpos.x, winpos.y);
}

void Application::windowFocusCallback(EventWindowFocus ev)
{
	auto& winfocus = ev.getWindowFocusParams();
	PHS_CORE_LOG_DEBUG("Window focus callback: focus {}", winfocus.value ? "gained" : "lost");
}

void Application::windowCloseCallback(PHS_UNUSED EventWindowClose ev)
{
	PHS_CORE_LOG_DEBUG("Window callback: Window close");
}

void Application::keyPressCallback(EventKeyPress ev)
{
	//auto& state = ev.getKeyboardKeyParams();
	//PHS_CORE_LOG_DEBUG("Key press callback: key {}, mods {}", state.key, state.mods);
}

void Application::keyReleaseCallback(EventKeyRelease ev)
{
	//auto& state = ev.getKeyboardKeyParams();
	//PHS_CORE_LOG_DEBUG("Key release callback: key {}, mods {}", state.key, state.mods);
}

void Application::keyRepeatCallback(EventKeyRepeat ev) 
{
	//auto& state = ev.getKeyboardKeyParams();
	//PHS_CORE_LOG_DEBUG("Key repeat callback: key {}, mods {}", state.key, state.mods);
}

void Application::keyTypeCallback(EventKeyType ev)
{
	//auto& state = ev.getKeyboardTypeParams();
	//PHS_CORE_LOG_DEBUG("Key type callback: code {}", static_cast<unsigned int>(state.code));
}

void Application::mousePressCallback(EventMousePress ev)
{ 
	//auto& mice = ev.getMouseButtonParams();
	//PHS_CORE_LOG_DEBUG("Mouse press callback: button {}, mods {}", mice.button, mice.mods);
}

void Application::mouseReleaseCallback(EventMouseRelease ev)
{
	//auto& mice = ev.getMouseButtonParams();
	//PHS_CORE_LOG_DEBUG("Mouse release callback: button {}, mods {}", mice.button, mice.mods);
}

void Application::mouseMoveCallback(EventMouseMove ev)
{
	//auto& cursor = ev.getCursorParams();
	//PHS_CORE_LOG_DEBUG("Mouse move callback: x {}, y {}", cursor.x, cursor.y);
}

void Application::mouseScrollCallback(EventMouseScroll ev)
{
	//auto& scroll = ev.getMouseScrollParams();
	//PHS_CORE_LOG_DEBUG("Mouse scoll callback: xoff {}, yoff {}", scroll.xoff, scroll.yoff);
}

Application::Application()
	: _window(std::make_unique<Window>())
	, _callbacks(std::make_unique<EventCallbacks>())
{
	// initialize logging system
	Log::init();

	// initialize window
	_window->init(800, 600, "Hello GLFW");

	// initialize callback functions 
	_callbacks->error_callback				= errorCallback;

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
	PHS_CORE_LOG_INFO("Welcome to Pheasant from Visual Studio with CMake!");

	while (_window->isOpen())
	{
		Render::drawFrame(RenderData{ 0 });
		_window->update();
	}
}

} // namespace Phs
