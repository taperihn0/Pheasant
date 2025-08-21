#include "precompile.h"
#include "application.h"
#include "log.h"

namespace Phs {

void Application::run()
{
#ifdef PHS_WINDOWS
	Log::init();
	std::string tmp = "HERE I AM";
	Log::message(Log::MSG_INFO, "Welcome to Pheasant on Windows: {}, {", tmp);
#endif
	while (true);
}

} // namespace Phs
