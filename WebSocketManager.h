#pragma once

#include <cpprest/ws_client.h>
#include <cpprest/json.h>
#include <nlohmann/json.hpp>


using namespace web;
using namespace web::websockets::client;


class WebSocketManager
{

private:
	websocket_client client;
	utility::string_t serverUri;

public:
	WebSocketManager( const utility::string_t& serverUri);

	bool wsConnect();
	bool wsSend(const nlohmann::json& message);
	nlohmann::json wsRecieve();
	bool wsClose();
	bool suscribe();
	void sendMessage();
	

};

