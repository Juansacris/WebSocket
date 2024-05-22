#pragma once

#include <string>
#include <nlohmann/json.hpp>


struct ConnectionInfo
{
    std::string Id;
    std::string Name;
    std::string Tenant;

    nlohmann::json ConvertToJson() const;
    static ConnectionInfo Deserialize( const nlohmann::json& jsonData );
                
};


