#pragma once

#include <string>
#include "ConnectionInfo.h"
#include <nlohmann/json.hpp>


struct RequestInfo
{
    std::string Data;
    ConnectionInfo Source;
    ConnectionInfo Target;
    std::int32_t Type;

    nlohmann::json ConvertToJson() const;
    static RequestInfo    Deserialize( const nlohmann::json& json );
};
