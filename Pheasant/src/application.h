#pragma once

#include "core.h"

class PHEASANT_API Application
{
public:
	Application() = default;
	virtual ~Application() = default;
	void run();
};

Application* createApplication();
