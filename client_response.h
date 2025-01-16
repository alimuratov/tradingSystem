#pragma once 
#include <sstream>
#include "types.h"
#include "lf_queue.h"

using namespace Common;
namespace Exchange {
#pragma pack(push, 1)
    enum class ClientResponseType : uint8_t {
        INVALID = 0,
        ACCEPTED = 1,
        CANCELED = 2,
        FILLED = 3, // order has been executed
        CANCEL_REJECTED = 4
    };

    inline auto clientResponseTypeToString(ClientResponseType type) -> std::string {
        switch(type) {
            case ClientResponseType::INVALID: return "INVALID";
            case ClientResponseType::ACCEPTED: return "ACCEPTED";
            case ClientResponseType::CANCELED: return "CANCELED";
            case ClientResponseType::FILLED: return "FILLED";
            case ClientResponseType::CANCEL_REJECTED: return "CANCEL_REJECTED";
        }
        return "UNKNOWN";
    }
}