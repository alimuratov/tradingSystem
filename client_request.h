#pragma once
#include <sstream>
#include "types.h"
#include "lf_queue.h"

using namespace Common;

namespace Exchange {
// to make sure the following structures are packed when they are sent over the network as flat binary structures
#pragma pack(push, 1)
    enum class ClientRequestType : uint8_t {
        INVALID = 0,
        NEW = 1,
        CANCEL = 2
    };

    inline auto clientRequestTypeToString(ClientRequestType type) -> std::string { 
        switch(type) {
            case ClientRequestType::INVALID: return "INVALID";
            case ClientRequestType::NEW: return "NEW";
            case ClientRequestType::CANCEL: return "CANCEL"; 
        }
        return "UNKNOWN";
    }

    struct MEClientRequest {
        ClientRequestType type_ = ClientRequestType::INVALID;
        ClientId client_id_ = ClientId_INVALID;
        TickerId ticker_id_ = TickerId_INVALID;
        OrderId order_id_ = OrderId_INVALID;
        Side side_ = Side::INVALID;
        Price price_ = Price_INVALID;
        Qty qty_ = Qty_INVALID;
        auto toString() const {
            std::stringstream ss;
            ss << "MEClientRequest: {"
               << "type: " << clientRequestTypeToString(type_) << ", "
               << "client_id: " << clientIdToString(client_id_) << ", "
               << "ticker_id: " << tickerIdToString(ticker_id_) << ", "
               << "order_id: " << orderIdToString(order_id_) << ", "
               << "side: " << sideToString(side_) << ", "
               << "price: " << priceToString(price_) << ", "
               << "qty: " << qtyToString(qty_) << "}";
            return ss.str();
        }
    };

#pragma pack(pop) // restoring default alignment setting for internal structure (not being sent over the network)
    // lock-free queue for sending client requests from the order gateway server to the matching engine
    typedef LFQueue<MEClientRequest> ClientRequestLFQueue;
}