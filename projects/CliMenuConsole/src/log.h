//============================================================================
// Name        : CliConsole.cpp
// Author      : Easwar
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Cpp based CLI Menu
//============================================================================

#include <iostream>
#include <map>
#include <functional>
#include <memory>
#include <limits>
#include "log.h"

using namespace std;

#ifndef LOGGING
#define LOGGING

#define LOG(...) std::cout , __VA_ARGS__
#define LOGN(...) std::cout , __VA_ARGS__ , std::endl

namespace {
	template <typename T>
	std::ostream& operator,(std::ostream& out, const T& t) {
	  out << t;
	  return out;
	}

	std::ostream& operator,(std::ostream& out, std::ostream&(*f)(std::ostream&)) {
	  out << f;
	  return out;
	}
}

#endif
