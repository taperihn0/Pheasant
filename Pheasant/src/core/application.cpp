#include "application.h"

namespace Phs {

void Application::run()
{
#ifdef PHS_WINDOWS
	std::cout << "Welcome to Pheasant on Windows!\n";
#endif
	while (true);
}

} // namespace Phs
