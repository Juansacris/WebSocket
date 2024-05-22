#include "RequestInfo.h"

nlohmann::json RequestInfo::ConvertToJson() const
{
    nlohmann::json result;
    result["data"]   = Data;
    result["source"] = Source.ConvertToJson();
    result["target"] = Target.ConvertToJson();
    result["messageType"]   = Type;
    return result;
}

RequestInfo RequestInfo::Deserialize( const nlohmann::json& json )
{
    RequestInfo result;

    result.Data   = json.at( "data" ).get<std::string>();
    result.Source = ConnectionInfo::Deserialize( json.at( "source" ) );
    result.Target = ConnectionInfo::Deserialize( json.at( "target" ) );
    result.Type   = json.at( "messageType" ).get<std::int32_t>();

    return result;
}
