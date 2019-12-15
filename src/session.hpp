#ifndef __SESSION_H
#define __SESSION_H

#include <boost/beast/http/message.hpp>
#include <boost/system/error_code.hpp>
#include <memory>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

class session : public std::enable_shared_from_this<session>{
	class ws_session {
		public:
			boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws;
			ws_session(boost::asio::ip::tcp::socket socket):
				ws(std::move(socket)){}
	};
	boost::asio::ip::tcp::socket socket;
	boost::beast::flat_buffer buffer;
	boost::beast::http::request<boost::beast::http::string_body> request;
	bool is_upgraded = false;
	std::shared_ptr<ws_session> ws_sess;

	
	void on_read(boost::system::error_code, size_t);
	void on_ws_accept(boost::system::error_code);
	void on_ws_read(boost::system::error_code, size_t b_transferred);
	void on_ws_write(boost::system::error_code, size_t b_transferred);

public:
	session(boost::asio::ip::tcp::socket socket);
	void run();

};

#endif
