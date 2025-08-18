#include "application.h"

#include <iostream>

namespace Phs {

void Application::run()
{
#ifdef PHEASANT_PLATFORM_LINUX
	std::cout << "Welcome to Pheasant on Linux!\n";
#endif
	while (true);
}

} // namespace Phs
