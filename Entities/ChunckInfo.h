#pragma once

#include <string>
#include <nlohmann/json.hpp>


struct ChunkInfo
{
    std::int32_t Id;
    std::int32_t Total;
    std::int32_t ActionCode;
    std::string  ActionId;

    nlohmann::json   ConvertToJson() const;
    static ChunkInfo Deserialize( const nlohmann::json& jsonData );
};
