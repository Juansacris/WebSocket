
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "WebSocketManager.h"
#include "Entities/RequestInfo.h"
#include <iostream>
#include <string>
#include <cstddef>
#include <algorithm>
#include <fstream>
#include <vector>


int main()
{
    std::string url = "wa-dev-adm-je.azurewebsites.net";


    try
    {
        WebSocketManager webSocketManager(url);

        RequestInfo                 requestInfo;



        if (webSocketManager.wsConnect())
        {

            if (webSocketManager.suscribe())
            {

                int count = 0;

                while (true)
                {
                    nlohmann::json  response = webSocketManager.wsRecieve();
                    if (response.contains("type") && response["type"] == 1)
                    {
                        if (response.contains("target")
                            && response.value("target", "")
                            == "OnMessage")
                        {
                            if (response.contains("arguments"))
                            {
                                nlohmann::json  jsonArray = response["arguments"];
                                nlohmann::json  arguments = jsonArray[0];
                                requestInfo = RequestInfo::Deserialize(jsonArray[0]);

                                std::cout << "El contenido del mensaje es: " << requestInfo.Data << std::endl;
                                if (requestInfo.Data == "Close")
                                {
                                    webSocketManager.wsClose();
                                    break;
                                }
                            }
                            webSocketManager.sendMessage();
                            continue;
                        }
                        else if (response.contains("type") && response["type"] == 6)
                        {
                            std::cout << "El contenido del mensaje es: " << requestInfo.Data << std::endl;
                            continue;
                        }

                    }
                    count++;
                }
            }
            webSocketManager.wsClose();
        }
    }
    catch (const std::exception& exc)
    {
        std::cout << exc.what() << std::endl;
    }

    return 0;

}
























/*
int main()
{
    websocket_client client;
    
    json::value handshake;

    handshake[U("protocol")] = json::value::string(L"json");
    handshake[U("version")] = json::value::number(1);

    std::cout << utility::conversions::to_utf8string(handshake.serialize()).append("") << std::endl;
    
    websocket_outgoing_message reqMsg;
    reqMsg.set_utf8_message(utility::conversions::to_utf8string(handshake.serialize()).append(""));
    
    client.connect(U("wss://wa-manuel-avs.azurewebsites.net/chat/chatHub")).wait();
    
    client.send(reqMsg).wait();

    while (true)
    {
        auto recieveTask = client.receive();

        auto status = recieveTask.wait();

        if (status == pplx::completed)
        {
            auto message = recieveTask.get();
            std::string msgResponse = message.extract_string().get();
            msgResponse.pop_back();
            std::cout << msgResponse << std::endl;
            json::value response = json::value::parse(msgResponse);

            if (response.has_field(U("type")))
            {
                if (response.at(U("type")) == 6)
                {
                    std::cout << "Coneccion establecida" << std::endl;
                    break;
                }
            }
        }
    }

    json::value suscribeReq;
    json::value arg;
    arg[0] = json::value::string(L"123456789");
    arg[1] = json::value::string(L"JuanCpp");
    suscribeReq[U("arguments")] = arg;
    suscribeReq[U("invocationId")] = json::value::string(L"0");
    suscribeReq[U("target")] = json::value::string(L"suscribeDevice");
    suscribeReq[U("type")] = json::value::number(1);

    std::cout << utility::conversions::to_utf8string(suscribeReq.serialize()).append("") << std::endl;

    websocket_outgoing_message susMsg;
    susMsg.set_utf8_message(utility::conversions::to_utf8string(suscribeReq.serialize()).append(""));

    client.send(susMsg).wait();


    while (true)
    {
        auto recieveTask = client.receive();

        auto status = recieveTask.wait();

        if (status == pplx::completed)
        {
            auto message = recieveTask.get();
            std::string msgResponse = message.extract_string().get();
            msgResponse.pop_back();
            std::cout << msgResponse << std::endl;
            json::value response = json::value::parse(msgResponse);

            if (response.has_field(U("type")))
            {
                if (response.at(U("type")) == 3)
                {
                    if (response.has_field(U("result")))
                    {
                        json::value result = response[U("result")];                
                                                
                        if (result[U("success")].as_bool() == true)
                        {
                            std::cout << "Se suscribio correctamente ahora podra enviar y recibir mensajes" << std::endl;
                            break;

                        }
                    }
                }
            }
        }
    }

    // Close the connection
   client.close().wait();
   
    
}
*/

/*
* 
*     while(true) {
        client.receive().then([](websocket_incoming_message const& msg) {
            return msg.extract_string();
            }).then([](std::string body) {
                body.pop_back();
                std::cout << body << std::endl;

                json::value response = json::value::parse(body);

                if (response.has_field(U("type")))
                {
                    if (response.at(U("type")) == 6)
                    {
                        std::cout << "Coneccion establecida" << std::endl;       
                        return true;              

                    }
                }               
                }).wait();
    }
* 
*/