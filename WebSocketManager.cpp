#include "WebSocketManager.h"


WebSocketManager::WebSocketManager(const utility::string_t& serverUri) :client(), serverUri(serverUri) {}

void WebSocketManager::wsConnect()
{
	client.connect(serverUri).wait();
}

void WebSocketManager::wsSend(const json::value& message)
{
	websocket_outgoing_message msg;
	msg.set_utf8_message(utility::conversions::to_utf8string(message.serialize()).append(""));
	client.send(msg).wait();
}

json::value WebSocketManager::wsRecieve()
{
	auto receiveTask = client.receive();
	receiveTask.wait();
	auto message = receiveTask.get();
	std::string msgResponse = message.extract_string().get();
	msgResponse.pop_back();
	//std::cout << msgResponse << std::endl;

	return json::value::parse(msgResponse);

}

void WebSocketManager::wsClose()
{
	client.close().wait();
}

void WebSocketManager::suscribe()
{
	json::value suscribeReq;
	json::value arg;
	arg[0] = json::value::string(L"123456789");
	arg[1] = json::value::string(L"JuanCpp");
	suscribeReq[U("arguments")] = arg;
	suscribeReq[U("invocationId")] = json::value::string(L"0");
	suscribeReq[U("target")] = json::value::string(L"suscribeDevice");
	suscribeReq[U("type")] = json::value::number(1);

	wsSend(suscribeReq);
	std::cout << "Suscrito" << std::endl;
}

void WebSocketManager::sendMessage()
{

	json::value messageRequest1;
	json::value arg2;
	arg2[0] = json::value::string(utility::conversions::to_string_t(L"134567321"));
	arg2[1] = json::value::string(utility::conversions::to_string_t(L"Mensaje recibido procesando informacion."));
	messageRequest1[U("arguments")] = arg2;
	messageRequest1[U("invocationId")] = json::value::string(L"0");
	messageRequest1[U("target")] = json::value::string(L"sendMessageDevice");
	messageRequest1[U("type")] = json::value::number(1);

	wsSend(messageRequest1);
}








