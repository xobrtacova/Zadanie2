#pragma once

#include <fstream>
#include <ostream>

#include "defs.h"

namespace sort
{
	bool process(Order order, Filter filter, Case compare, Filtere space, std::istream & input, std::ostream & output);
	bool LessCaseSensitive(const std::string& a, const std::string& b);
}

