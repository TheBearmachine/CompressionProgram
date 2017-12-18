#pragma once
#include <string>

class SequiturCompression
{
public:
	SequiturCompression();
	~SequiturCompression();

	void compress(std::string &string);
	void decompress(std::string &string);

	const std::string& getString() const;

private:
	std::string mString;
};