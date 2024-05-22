#include "WebSocketManager.h"
#include "Entities/ConnectionInfo.h"



WebSocketManager::WebSocketManager(const utility::string_t& serverUri) :client(), serverUri(serverUri) {}

bool WebSocketManager::wsConnect()
{
	try
	{
		client.connect(serverUri).wait();

		nlohmann::json handshake;
		handshake["protocol"] = "json";
		handshake["version"] = 1;
		
		if (wsSend(handshake))
		{
			nlohmann::json response = wsRecieve();
			if (response.size() == 0)
			{
				return true;
				
			}
		}
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
		return false;
	}
	return false;
}

bool WebSocketManager::wsSend(const nlohmann::json& message)
{
	try
	{
		web::websockets::client::websocket_outgoing_message msg;
		std::string                                         mensage = message.dump() += "";
		msg.set_utf8_message(mensage);
		client.send(msg).wait();

		return true;
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
		return false;
	}
}

nlohmann::json WebSocketManager::wsRecieve()
{
	auto receiveTask = client.receive();
	receiveTask.wait();
	auto        message = receiveTask.get();
	std::string msgResponse = message.extract_string().get();
	msgResponse.pop_back();

	return nlohmann::json::parse(msgResponse);

}

bool WebSocketManager::wsClose()
{
	try
	{
		client.close().wait();
		return true;
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
		return false;
	}
}

bool WebSocketManager::suscribe()
{
	nlohmann::json suscribeReq;
	ConnectionInfo connectionInfo;
	connectionInfo.Id = "guid";
	connectionInfo.Name = "name";
	connectionInfo.Tenant = "0";

	suscribeReq["arguments"] = nlohmann::json::array({ connectionInfo.ConvertToJson() });
	suscribeReq["invocationId"] = "0";
	suscribeReq["target"] = "SuscribeAgent";
	suscribeReq["type"] = 1;
	

	if (wsSend(suscribeReq))
	{
		nlohmann::json response = wsRecieve();
		std::cout <<  response.dump() << std::endl;
		if (response.contains("type") && response["type"] == 3)
		{
			if (response.contains("result"))
			{
				return true;
			}
			else if (response.contains("error"))
			{
				std::cout << response.value("error", "") << std::endl;
			}
		}
	}
	else
	{
		std::cout << "Failure to subscribe to the sevidor" << std::endl;
	}
	return false;
}

void WebSocketManager::sendMessage()
{
	nlohmann::json messageRequest1;
	nlohmann::json arg2;
	arg2[0] = "134567321";
	arg2[1]
		= "Mensaje recibido procesando informacion.";
	messageRequest1["arguments"] = arg2;
	messageRequest1["invocationId"] = "0";
	messageRequest1["target"] = "sendMessageDevice";
	messageRequest1["type"] = 1;

	wsSend(messageRequest1);
}








