#ifndef __LISTENER_H
#define __LISTENER_H

#include <boost/asio.hpp>
#include <memory>

class listener : public std::enable_shared_from_this<listener>{
	boost::asio::ip::tcp::acceptor acceptor;
	boost::asio::ip::tcp::socket socket;

	void on_accept(boost::system::error_code ec);

public:
	listener(boost::asio::io_context &ioc,
			boost::asio::ip::tcp::endpoint endpoint);

	void run();

};

#endif
