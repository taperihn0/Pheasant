#include "application.h"

#include <iostream>

namespace Phs {

void Application::run()
{
#ifdef PHEASANT_PLATFORM_WINDOWS
	std::cout << "Welcome to Pheasant on Windows!\n";
#endif
	while (true);
}

} // namespace Phs
