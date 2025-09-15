#pragma once

#include "precompile.h"
#include "defines.h"
#include "window/window.h"
#include "filesystem/filesystem.h"

namespace Phs
{

class PHEASANT_API Application
{
public:
	Application() = default;
	Application(int argc, char** argv);
	virtual		~Application() = default;

	// Main loop of a application
	void			run();
private:
	/* Writes program arguments and sets appropriate state:
	*	 - program path
	*   - working directory, which corresponds to the CMAKE_SOURCE_DIR from CMake 
	*     configuration file
	*  Seconds argument should be set to desired working directory
	*  of a program. Then, the directory is changed in runtime.
	*/
	void			loadExternalState(int argc, char** argv);

	static constexpr size_t _ProgramPathPlace = 0;
	static constexpr size_t _WorkingDirPlace  = 1;

	// Callbacks functions handling window events
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

	static constexpr size_t			  _ProgramArgCount = 2;
	FilePath								  _program_path;
	FilePath								  _working_dir;
};

Application* createApplication(int argc, char** argv);

} // namespace Phs
