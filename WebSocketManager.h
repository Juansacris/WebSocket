#pragma once
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/ssl/ssl_stream.hpp>
#include <iostream>
#include <nlohmann/json.hpp>


class WebSocketManager
{

private:
	boost::asio::io_context io_context;
	boost::asio::ssl::context sslContext;
	boost::asio::ip::tcp::resolver resolver;
	boost::beast::websocket::stream<boost::beast::ssl_stream<boost::asio::ip::tcp::socket>> ws;
	std::string serverUri;	

public:
	WebSocketManager( const std::string& serverUri);

	bool wsConnect();
	bool wsSend(const nlohmann::json& message);
	nlohmann::json wsRecieve();
	bool wsClose();
	bool suscribe();
	void sendMessage();
	

};

