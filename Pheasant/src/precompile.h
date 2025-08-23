#pragma once

#include "defines.h"

#include <iostream>
#include <string>
#include <string_view>
#include <tuple>

#ifdef PHS_OS_WINDOWS
#  include <Windows.h>
#endif

// Alternative operator representations, like 'and', 'or', 'not' seems to not work well
// under Visual Studio somehow.
// This addictional #include solve it completely.
#include <iso646.h>
