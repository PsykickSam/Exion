#include "HTTP_Server.h"

HTTPServer::HTTPServer() {
	_socket = INVALID_SOCKET;
}

HTTPServer::~HTTPServer() {
	// Destractor
}

// Public
void HTTPServer::initiate() {

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

void HTTPServer::setter() {

}

void HTTPServer::start() {

}

void HTTPServer::loop() {
	while (is_running) {
		int new_socket = accept(_socket, (struct sockaddr*)&_address, (socklen_t*)&_addrlen);

		if (new_socket < 0) {
			perror("accept");
			exit(EXIT_FAILURE);
		}

		_valrecv = recv(new_socket, buffer, 1024, 0);
		printf("%s\n", buffer);
		
		_i_result = send(new_socket, send_text, strlen(send_text), 0);
		if (_i_result == SOCKET_ERROR) {
			wprintf(L"send failed with error: %d\n", WSAGetLastError());
			closesocket(new_socket);
		}
		else 
		{
			printf("message send\n");
		}

		closesocket(new_socket);
	}
}

void HTTPServer::stop() {
	// TODO: LOG

	WSACleanup();
}

void HTTPServer::destroy() {

}

void HTTPServer::set_is_running(bool is_run) {
	is_running = is_run;
}

// Private
void HTTPServer::prepare_send() {

}

bool HTTPServer::is_found_error(int error_flag, OPERATOR op) {
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

void HTTPServer::log_message(const char* message, bool invoke_exit) {
	std::cout << (message) << std::endl;

	if (invoke_exit) {
		exit(EXIT_FAILURE);
	}

}

