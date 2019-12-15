#include<boost/asio.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>

#include "listener.hpp"
#include "web_socket_server.hpp"

int main(int argc, char ** argv){
	if (argc < 3){
		std::cout << "./server <address> <port>\n";
		return 0;
	}

	boost::asio::io_context ioc;
	auto address = boost::asio::ip::make_address(argv[1]);
	auto port = static_cast<unsigned short>(std::atoi(argv[2]));

	if (argc >= 4){
		wsserv::data_path = argv[3];
	}

	std::make_shared<listener>(
			ioc,
			boost::asio::ip::tcp::endpoint{address, port})->run();


	ioc.run();

	return 0;
}
