#include "WebSocketManager.h"
#include "Entities/ConnectionInfo.h"
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

#include <boost/asio.hpp>



WebSocketManager::WebSocketManager(const std::string& serverUri) :
	sslContext{boost::asio::ssl::context::tlsv13_client},
	resolver{ io_context },
	ws{ io_context, sslContext },
	serverUri{ serverUri }
{
	

}

bool WebSocketManager::wsConnect()
{
	try
	{
		auto const results = resolver.resolve(serverUri, "443");
		
		boost::asio::connect(ws.next_layer().next_layer(), results);
		ws.next_layer().handshake(boost::asio::ssl::stream_base::client);
		ws.handshake(serverUri, "/repserver/notification/AgentHub");
		
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
	catch (const boost::system::system_error& exc)		
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
		std::cout << "Enviando mensaje " << std::endl;
		std::string                                         mensage = message.dump() += "";
		std::cout << mensage << std::endl;
		ws.write(boost::asio::buffer(mensage));		

		return true;
	}
	catch (const boost::system::system_error& exc)
	{
		std::cout << exc.what() << std::endl;
		return false;
	}
}

nlohmann::json WebSocketManager::wsRecieve()
{
	boost::beast::flat_buffer buffer;
	ws.read(buffer);

	std::string msgResponse = boost::beast::buffers_to_string(buffer.data());
	msgResponse.pop_back();

	std::cout << msgResponse << std::endl;

	return nlohmann::json::parse(msgResponse);

}

bool WebSocketManager::wsClose()
{
	try
	{
		ws.close(boost::beast::websocket::close_code::normal);
		return true;
	}
	catch (const boost::system::system_error& exc)
	{
		std::cout << exc.what() << std::endl;
		return false;
	}
}

bool WebSocketManager::suscribe()
{
	nlohmann::json suscribeReq;
	ConnectionInfo connectionInfo;
	connectionInfo.Id = "123456789";
	connectionInfo.Name = "cpp_boost";
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








