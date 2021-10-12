#pragma once

#include <istream>

// Definitions
template<typename T>
T read(std::istream& in);


// Implementation
template<typename T>
T read(std::istream & in)
{
	T input;
	in >> input;
	return input;
}