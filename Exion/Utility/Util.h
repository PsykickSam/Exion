#pragma once

#include <string>

class Util {

// Variables
private:
	std::string* buffer_array;

// Methods
public:
	std::string* parse_buffer(char* buffer, int lenth);
	void free_parse_buffer();
};