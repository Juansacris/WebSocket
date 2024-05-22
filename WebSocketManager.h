#pragma once

#include <cpprest/ws_client.h>
#include <cpprest/json.h>


using namespace web;
using namespace web::websockets::client;

class WebSocketManager
{
public:
	WebSocketManager( const utility::string_t& serverUri);

	void wsConnect();
	void wsSend(const json::value & message);
	json::value wsRecieve();
	void wsClose();
	void suscribe();
	void sendMessage();
	

private:
	websocket_client client;
	utility::string_t serverUri;

};

