#include "ChunckInfo.h"

nlohmann::json ChunkInfo::ConvertToJson() const
{
    nlohmann::json result;

    result["partitionId"]    = Id;
    result["partitionTotal"] = Total;
    result["actionCode"]     = ActionCode;
    result["actionId"]       = ActionId;

    return result;
}

ChunkInfo ChunkInfo::Deserialize( const nlohmann::json& jsonData )
{
    ChunkInfo result;

    result.Id         = jsonData.at( "partitionId" ).get<std::uint32_t>();
    result.Total      = jsonData.at( "partitionTotal" ).get<std::uint32_t>();
    result.ActionCode = jsonData.at( "actionCode" ).get<std::uint32_t>();
    result.ActionId   = jsonData.at( "actionId" ).get<std::string>();

    return result;
}
