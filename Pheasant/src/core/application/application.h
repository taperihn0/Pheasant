#pragma once

#include "precompile.h"
#include "defines.h"
#include "window/window.h"

namespace Phs
{

class PHEASANT_API Application
{
public:
	Application();
	virtual		~Application() = default;

	void			run();
private:
	static void errorCallback(EventError ev);

	static void windowResizeCallback(EventWindowResize ev);
	static void windowMoveCallback(EventWindowMove ev);
	static void windowFocusCallback(EventWindowFocus ev);
	static void windowCloseCallback(EventWindowClose ev);

	static void keyPressCallback(EventKeyPress ev);
	static void keyReleaseCallback(EventKeyRelease ev);
	static void keyRepeatCallback(EventKeyRepeat ev);
	static void keyTypeCallback(EventKeyType ev);

	static void mousePressCallback(EventMousePress ev);
	static void mouseReleaseCallback(EventMouseRelease ev);
	static void mouseMoveCallback(EventMouseMove ev);
	static void mouseScrollCallback(EventMouseScroll ev);

	std::unique_ptr<Window>			  _window;
	std::unique_ptr<EventCallbacks> _callbacks;
};

Application* createApplication();

} // namespace Phs
