#pragma once

#include "precompile.h"
#include "defines.h"

namespace Phs
{

class PHEASANT_API Application
{
public:
	Application() = default;
	virtual ~Application() = default;
	void run();
};

Application* createApplication();

} // namespace Phs
