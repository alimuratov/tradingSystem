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

    struct MEClientResponse {
        ClientResponseType type_ = ClientResponseType::INVALID;
        ClientId clientId = ClientId_INVALID;
        TickerId ticker_id = TickerId_INVALID;
        OrderId client_order_id_ = OrderId_INVALID;
        OrderId market_order_id_ = OrderId_INVALID;
        Side side_ = Side::INVALID;
        Price price_ = Price_INVALID;
        Qty exec_qty_ = Qty_INVALID;
        Qty leaves_qty = Qty_INVALID;
        auto toString() const {
            std::stringstream ss;
            ss << "MEClientResponse: {"
               << "type: " << clientResponseTypeToString(type_) << ", "
               << "clientId: " << clientIdToString(clientId) << ", "
               << "tickerId: " << tickerIdToString(ticker_id) << ", "
               << "clientOrderId: " << orderIdToString(client_order_id_) << ", "
               << "marketOrderId: " << orderIdToString(market_order_id_) << ", "
               << "side: " << sideToString(side_) << ", "
               << "price: " << priceToString(price_) << ", "
               << "execQty: " << qtyToString(exec_qty_) << ", "
               << "leavesQty: " << qtyToString(leaves_qty) << "}";
            return ss.str();
        }
    };
    #pragma pack(pop)
    typedef LFQueue<MEClientResponse> ClientResponseLFQueue;
}