#pragma once

#include "core.h"

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
