#pragma once
#include <sstream>
#include "types.h"
#include "lf_queue.h"

using namespace Common;
namespace Exchange {
#pragma pack(push, 1)
    // MarketUpdateType represents the update action in the Market Update object for an order
    enum class MarketUpdateType : uint8_t {
        INVALID = 0,
        ADD = 1,
        MODIFY = 2,
        CANCEL = 3, 
        TRADE = 4
    };
    inline std::string marketUpdateToString(MarketUpdateType type) {
        switch(type) {
            case MarketUpdateType::INVALID: return "INVALID";
            case MarketUpdateType::ADD: return "ADD";
            case MarketUpdateType::MODIFY: return "MODIFY";
            case MarketUpdateType::CANCEL: return "CANCEL";
            case MarketUpdateType::TRADE: return "TRADE";
        }
        return "UNKNOWN";
    }
    // MEMarketUpdate is a communication unit between matching engine and market data publishing component
    struct MEMarketUpdate {
        MarketUpdateType type_ = MarketUpdateType::INVALID;
        OrderId order_id = OrderId_INVALID;
        TickerId ticker_id = TickerId_INVALID;
        Side side_ = Side::INVALID;
        Price price_ = Price_INVALID;
        Qty qty_ = Qty_INVALID;
        Priority priority_ = Priority_INVALID;
        auto toString() const {
            std::stringstream ss;
            ss << "MEMarketUpdate: {"
               << "type: " << marketUpdateToString(type_) << ", "
               << "orderId: " << orderIdToString(order_id) << ", "
               << "tickerId: " << tickerIdToString(ticker_id) << ", "
               << "side: " << sideToString(side_) << ", "
               << "price: " << priceToString(price_) << ", "
               << "qty: " << qtyToString(qty_) << ", "
               << "priority: " << priorityToString(priority_) << "}";
            return ss.str();
        }
    };
#pragma pack(pop)
    typedef LFQueue<MEMarketUpdate> MEMarketUpdateLFQueue;
}