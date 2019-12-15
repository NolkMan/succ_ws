#ifndef __WEB_SOCKET_SERVER_H
#define __WEB_SOCKET_SERVER_H

#include <string>

namespace wsserv{
	extern std::string data_path;
	std::string responce_for_request(std::string request);

}

#endif
