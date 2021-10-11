#pragma once

#include <istream>

template<typename T>
T read(std::istream & in)
{
	T input;
	in >> input;
	return input;
}