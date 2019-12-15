#include "listener.hpp"
#include "session.hpp"
#include <boost/asio/io_context.hpp>
#include <boost/asio/socket_base.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>
#include "utils.hpp"

using error_code = boost::system::error_code;
using tcp = boost::asio::ip::tcp;

listener::listener(boost::asio::io_context &ioc,
		tcp::endpoint endpoint): acceptor(ioc),socket(ioc){
	error_code ec;

	acceptor.open(endpoint.protocol(), ec);
	if (ec){
		fail(ec, "open");
		return;
	}

	acceptor.set_option(boost::asio::socket_base::reuse_address(true));
	acceptor.bind(endpoint, ec);
	if (ec){
		fail(ec, "bind");
		return;
	}
	acceptor.listen(boost::asio::socket_base::max_listen_connections, ec);
	if (ec){
		fail(ec, "listen");
		return;
	}
}

void listener::run(){
	acceptor.async_accept(
			socket,
			[self = shared_from_this()](error_code ec){
				self->on_accept(ec);
			});
}

void listener::on_accept(error_code ec){
	if (ec){
		fail(ec, "on_accept");
		return;
	}
	else {
		std::cout << "Made a session" << std::endl;
		std::make_shared<session>(std::move(socket))->run();
	}

	acceptor.async_accept(
			socket,
			[self = shared_from_this()](error_code ec){
			self->on_accept(ec);
			});
}
