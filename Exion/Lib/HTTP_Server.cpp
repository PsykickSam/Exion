#include "HTTP_Server.h"

HTTPServer::HTTPServer() 
{
	_socket = INVALID_SOCKET;
	
	util = Util();
}

HTTPServer::~HTTPServer() 
{
	// Destractor
}

// Public
void HTTPServer::initiate() 
{

	_i_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (is_found_error(NO_ERROR, OPERATOR::NOT_EQUALS)) log_message("WSAStartup failed: " + _i_result, true);

	_addrlen = sizeof(_address);
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = htonl(INADDR_ANY);
	_address.sin_port = htons(SOCKET_PORT);
	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	_i_result = _socket;
	if (is_found_error(INVALID_SOCKET, OPERATOR::EQUALS)) {
		WSACleanup();
		log_message("Socket initialization failed", true); 
	}
	
	_i_result = setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &SOCKET_OPT, sizeof(SOCKET_OPT));
	if (is_found_error(INVALID_SOCKET, OPERATOR::EQUALS)) log_message("Socket set socket opt failed", true);
	
	_i_result = bind(_socket, (SOCKADDR *)&_address, sizeof(_address));
	if (is_found_error(0, OPERATOR::LESS_THEN)) log_message("Socket binding failed", true);
	
	_i_result = listen(_socket, 3);
	if (is_found_error(0, OPERATOR::LESS_THEN)) log_message("Socket listening failed", true);
}

void HTTPServer::setter() 
{

}

void HTTPServer::start() 
{

}

void HTTPServer::loop() 
{
	while (is_running) 
	{
		log_message("--- Start ---", false);

		int new_socket = accept(_socket, (struct sockaddr*)&_address, (socklen_t*)&_addrlen);
		_i_result = new_socket;

		if (is_found_error(0, OPERATOR::LESS_THEN))
		{
			log_message("New socket error", true);
		}

		_valrecv = recv(new_socket, buffer, 1024, 0);
		log_message("Actual Buffer", false);
		log_message(buffer, false);

		std::string* parsed_buffer = util.parse_buffer(buffer, sizeof(buffer));
		std::string request_type = parsed_buffer[0];
		std::string base_url = parsed_buffer[1];
		std::string http_version = parsed_buffer[2];
		std::ifstream website_file;

		log_message("Request Type:  " + request_type, false);
		log_message("Base URL:      " + base_url, false);
		log_message("http_version:  " + http_version, false);

		if (base_url == "/")
		{// Send index.html file
			website_file.open("./Website/index.html", std::ios::binary);
		}
		else
		{// Send *.html file
			if (base_url.rfind(".")) 
			{
				website_file.open("./Website" + base_url, std::ios::binary);
			}
			else 
			{
				website_file.open("./Website" + base_url + "/index.html", std::ios::binary);
			}
		}

		if (website_file.is_open())
		{
			// Send website file to client
			std::string file_line;
			std::string file_lines;
			std::ifstream error_file;

			while (std::getline(website_file, file_line))
			{
				file_lines += file_line;
			}

			std::string final_result_str = header_text + file_lines;
			char* final_result = new char[final_result_str.size() + 1];
			std::copy(final_result_str.begin(), final_result_str.end(), final_result);
			final_result[final_result_str.size()] = '\0';

			_i_result = send(new_socket, final_result, strlen(final_result), 0);
			if (is_found_error(SOCKET_ERROR, OPERATOR::EQUALS))
			{
				log_message("Message Send failed: " + WSAGetLastError(), true);
			}
			else
			{
				log_message("Message sent", false);
			}
		}
		else 
		{
			// Send [Exion] 404 file not found error page
			std::string file_line;
			std::string file_lines;
			std::ifstream error_file;

			error_file.open("./Exion/pages/error.404.html", std::ios::binary);
			if (error_file.is_open()) {
				while (std::getline(error_file, file_line))
				{
					file_lines += file_line;
				}
			}

			std::string final_result_str = header_text + file_lines;
			char* final_result = new char[final_result_str.size() + 1];
			std::copy(final_result_str.begin(), final_result_str.end(), final_result);
			final_result[final_result_str.size()] = '\0';

			_i_result = send(new_socket, final_result, strlen(final_result), 0);
			if (is_found_error(SOCKET_ERROR, OPERATOR::EQUALS))
			{
				log_message("Message Send failed: " + WSAGetLastError(), true);
			}
			else
			{
				log_message("Message sent", false);
			}

			// Cleanup
			error_file.close();
			delete[] final_result;
		}

		// Cleanup
		closesocket(new_socket);
		website_file.close();
		util.free_parse_buffer();
		delete[] parsed_buffer;

		log_message("--- End ---", false);
	}
}

void HTTPServer::stop() 
{
	// TODO: LOG

	WSACleanup();
}

void HTTPServer::destroy() 
{

}

void HTTPServer::set_is_running(bool is_run) 
{
	is_running = is_run;
}

// Private
void HTTPServer::prepare_send() 
{

}

bool HTTPServer::is_found_error(int error_flag, OPERATOR op) 
{
	switch (op) {
	case OPERATOR::EQUALS:
		if (_i_result == error_flag) {
			return true;
		}
		break;
	case OPERATOR::NOT_EQUALS:
		if (_i_result != error_flag) {
			return true;
		}
		break;
	case OPERATOR::GREATER_EQUALS:
		if (_i_result > error_flag) {
			return true;
		}
		break;
	case OPERATOR::GREATER_THEN:
		if (_i_result >= error_flag) {
			return true;
		}
		break;
	case OPERATOR::LESS_EQUALS:
		if (_i_result <= error_flag) {
			return true;
		}
		break;
	case OPERATOR::LESS_THEN:
		if (_i_result < error_flag) {
			return true;
		}
		break;
	};

	return false;
}

void HTTPServer::log_message(const char* message, bool invoke_exit) 
{
	std::cout << (message) << std::endl;

	if (invoke_exit) {
		exit(EXIT_FAILURE);
	}
}

void HTTPServer::log_message(std::string message, bool invoke_exit)
{
	std::cout << (message) << std::endl;

	if (invoke_exit) {
		exit(EXIT_FAILURE);
	}
}

