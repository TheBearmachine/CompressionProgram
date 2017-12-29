#pragma once
#include <chrono>
#include "SequiturCompression.h"

class Test
{
public:
	Test();
	~Test();

	void runTests();

private:
	typedef std::chrono::high_resolution_clock Clock;

	SequiturCompression mSeqComp;
};