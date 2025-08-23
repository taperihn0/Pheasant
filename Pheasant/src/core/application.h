#pragma once

#include "precompile.h"
#include "defines.h"
#include "window.h"

namespace Phs
{

class PHEASANT_API Application
{
public:
	Application();
	virtual ~Application() = default;
	void run();
private:
	std::unique_ptr<Window> _window;
	bool						   _running;
};

Application* createApplication();

} // namespace Phs
