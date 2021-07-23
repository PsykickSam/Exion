#include "Util.h"

/**
* convert buffer array to 
* -> Request Type: GET, POST, PUT etc
* -> URL: url of the request 
* -> HTTP Version: http version
*/
std::string* Util::parse_buffer(char* buffer, int lenth)
{
	// Read the first line of the buffer
	int counter = 0;
	
	std::string* buffer_array = new std::string[3];
	std::string buffer_line;

	for (int i = 0; i < lenth; i++)
	{
		if (buffer[i] == ' ' || buffer[i] == '\n') 
		{
			buffer_array[counter] = buffer_line;
			buffer_line = "";
			counter += 1;
		}
		else buffer_line += buffer[i];
	
		if (buffer[i] == '\n') break;
	}

	return buffer_array;
}

void Util::free_parse_buffer() {
	delete[] buffer_array;
}