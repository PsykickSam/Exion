#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <WinSock2.h>
#include <WS2tcpip.h>

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#define SOCKET_HOST "127.0.0.1"
#define SOCKET_PORT 8888

class HTTPServer
{
private:
	enum class OPERATOR {
		LESS_THEN, GREATER_THEN, EQUALS, GREATER_EQUALS, LESS_EQUALS, NOT_EQUALS
	};

private: 
	char SOCKET_OPT = 1;

private:
	WSADATA wsa_data;
	SOCKET _socket;
	
	struct sockaddr_in _address;
	
	int _bind_socket;
	int _listen_socket;
	int _i_result;
	int _valrecv;
	int _addrlen;
	
	char buffer[1024] = { 0 };

	bool is_running = true; 

	const char* send_text = "HTTP/1.0 200 OK\n\nHello from Exion CPP";

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
	void prepare_send();
};

