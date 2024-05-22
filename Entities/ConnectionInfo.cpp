#include "ConnectionInfo.h"

nlohmann::json ConnectionInfo::ConvertToJson() const
{
    nlohmann::json result;
    result["identifier"] = Id;
    result["name"]       = Name;
    result["tenant"]     = Tenant;
    return result;
}

ConnectionInfo ConnectionInfo::Deserialize( const nlohmann::json& jsonData )
{
    ConnectionInfo result;
    result.Id = jsonData.at( "identifier" ).get<std::string>();
    result.Name = jsonData.at( "name" ).get<std::string>();
    result.Tenant = jsonData.at( "tenant" ).get<std::string>();

    return result;
}
