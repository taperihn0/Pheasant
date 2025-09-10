#pragma once

#include "defines.h"

#include <iostream>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

#ifdef PHS_OS_WINDOWS
#  include <Windows.h>
#endif

// Some libraries defines that, so undef them
#undef max
#undef min

// Alternative operator representations, like 'and', 'or', 'not' seems to not work well
// under Visual Studio somehow.
// This addictional #include solve it completely.
#include <iso646.h>
