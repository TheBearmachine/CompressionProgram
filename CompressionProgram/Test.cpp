#include "Test.h"

Test::Test()
{
}

Test::~Test()
{
}

void Test::runTests()
{
	size_t durationNanoSec = 0;
	double durationSec = 0;
	size_t sizeUncompressed = 0, sizeCompressed = 0;
	float compRatio = 0.0f;


	auto startTime = Clock::now();
	// Run first test

	auto endTime = Clock::now();
	durationNanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
	durationSec = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();


	// Print results
	compRatio = 0;
	if (sizeUncompressed != 0)
		compRatio = ((float)sizeCompressed / (float)sizeUncompressed);
	printf("First test with 100 x 100 tiles concluded:\nBytes uncompressed: %zu\nBytes compressed: %zu\nCompression ratio: %f\n\n", sizeUncompressed, sizeCompressed, compRatio);
	printf("Run time in nano seconds: %zu\nIn seconds: %f", durationNanoSec, durationSec);


	startTime = Clock::now();
	// Run second test

	endTime = Clock::now();
	durationNanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
	durationSec = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

	// Print results
	compRatio = 0;
	if (sizeUncompressed != 0)
		compRatio = ((float)sizeCompressed / (float)sizeUncompressed);
	printf("Second test with 1000 x 1000 tiles concluded:\nBytes uncompressed: %zu\nBytes compressed: %zu\nCompression ratio: %f\n\n", sizeUncompressed, sizeCompressed, compRatio);
	printf("Run time in nano seconds: %zu\nIn seconds: %f", durationNanoSec, durationSec);
}
