#include "Lib/HTTP_Server.h"

int main() {

	HTTPServer http_server = HTTPServer();
	http_server.initiate();
	http_server.loop();

}
