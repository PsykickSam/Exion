#pragma once

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

#include <WinSock2.h>
#include <WS2tcpip.h>

#include "../Utility/Util.h"

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#define SOCKET_HOST "127.0.0.1"
#define SOCKET_PORT 8888

class HTTPServer
{
// Variables
private:
	enum class OPERATOR {
		LESS_THEN, GREATER_THEN, EQUALS, GREATER_EQUALS, LESS_EQUALS, NOT_EQUALS
	};

private: 
	char SOCKET_OPT = 1;

private:
	WSADATA wsa_data;
	SOCKET _socket;

	std::string header_text			= "HTTP/1.0 200 OK\n\n";
	std::string content_type_html	= "Content-Type: text/html\n\n";
	std::string content_type_css	= "Content-Type: text/css\n\n";
	std::string content_type_js		= "Content-Type: text/js\n\n";
	std::string send_text			= "Hello from Exion CPP";
	
	struct sockaddr_in _address;
	char buffer[1024] = { 0 };
	bool is_running = true;
	int _bind_socket;
	int _listen_socket;
	int _i_result;
	int _valrecv;
	int _addrlen;

	Util util;

	

// Methods
public:
	HTTPServer();
	~HTTPServer();

	void initiate();
	void setter();
	void start();
	void loop();
	void stop();
	void destroy();

	void set_is_running(bool is_run);

private:
	bool is_found_error(int error_flag, OPERATOR op);
	void log_message(const char* message, bool invoke_exit);
	void log_message(std::string message, bool invoke_exit);

private:
	void prepare_send();
};

