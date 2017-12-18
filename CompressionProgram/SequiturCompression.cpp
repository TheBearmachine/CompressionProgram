#include "SequiturCompression.h"
#include <fstream>

SequiturCompression::SequiturCompression() :
	mString(NULL)
{
}

SequiturCompression::~SequiturCompression()
{
}

void SequiturCompression::compress(std::string & string)
{
	string.size();
}

void SequiturCompression::decompress(std::string & string)
{

}

const std::string & SequiturCompression::getString() const
{
	return mString;
}
