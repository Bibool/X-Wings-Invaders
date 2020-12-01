#ifndef HELPERS_H
#define HELPERS_H

#include <cassert>
#include <crtdbg.h>
#include <iostream>
#include <random>

/////////////////////////////////////////
// Debug macros
// Assert to check pointers
// Console Out to print only during debug
// 03/12/2019 Improved std::cout macro

#ifdef _DEBUG
	#define ASSERT_CHECK(param) assert(param)
	#define CONSOLE_OUT std::cout <<
	#define TIME_TO_RUN std::cout << "Time elapsed after Constructor call: " << m_clock.getElapsedTime().asMilliseconds() << "\n";
#else
	#define ASSERT_CHECK(param)
	#define CONSOLE_OUT
	#define TIME_TO_RUN
#endif

// Safe Delete template
// Credits to Zaf
template <typename T> void safeDelete(T*& a)
{
	delete a;
	a = nullptr;
}

template <typename T> void safeDeleteArray(T*& a)
{
	delete[] a;
	a = nullptr;
}
#endif // !HELPERS_H
