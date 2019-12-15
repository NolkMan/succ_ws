#include "session.hpp"

#include <boost/asio.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/system/error_code.hpp>
#include "utils.hpp"
#include "web_socket_server.hpp"

using tcp = boost::asio::ip::tcp;
using error_code = boost::system::error_code;
namespace beast = boost::beast;

session::session(tcp::socket socket):
	socket(std::move(socket))
{
}

void session::run(){
	auto self = shared_from_this();

	boost::beast::http::async_read(socket, buffer, request,
			[self]
			(error_code ec, size_t s){
				self->on_read(ec,s);
			});
}

void session::on_read(error_code ec, size_t size){
	if (ec == beast::http::error::end_of_stream){
		socket.shutdown(tcp::socket::shutdown_send, ec);
		return;
	}

	if (ec){
		fail(ec, "session read");
		return;
	}

	if (beast::websocket::is_upgrade(request)){
		is_upgraded = true;
		ws_sess = std::make_shared<ws_session>(std::move(socket));
		ws_sess->ws.async_accept(request,
				[self = this->shared_from_this()](error_code ec){
					self->on_ws_accept(ec);
				});
	}

}

// Web socket code

void session::on_ws_accept(error_code ec){
	if (ec){
		fail(ec, "ws accept");
		return;
	}

	ws_sess->ws.async_read(
			buffer,
			[self = this->shared_from_this()](error_code ec, size_t bytes){
				self->on_ws_read(ec, bytes);
			});
}

void session::on_ws_read(error_code ec, size_t){
	if (ec){
		fail(ec, "ws read");
		return;
	}

	std::string str = beast::buffers_to_string(buffer.data());
	buffer.consume(buffer.size());

	ws_sess->ws.async_write(boost::asio::buffer(wsserv::responce_for_request(str)),
			[self = shared_from_this()] (error_code ec, size_t bytes){
				self->on_ws_write(ec,bytes);
				});

	ws_sess->ws.async_read(
			buffer,
			[self = this->shared_from_this()](error_code ec, size_t bytes){
				self->on_ws_read(ec, bytes);
			});
}

void session::on_ws_write(error_code ec, size_t){
}
