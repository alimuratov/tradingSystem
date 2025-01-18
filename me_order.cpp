#include "me_order.h"
namespace Exchange {
    auto MEOrder::toString() const -> std::string {
        std::stringstream ss;
        ss << "MEOrder: {"
           << "ticker_id: " << tickerIdToString(ticker_id_) << ", "
           << "client_id: " << clientIdToString(client_id_) << ", "
           << "client_order_id: " << orderIdToString(client_order_id_) << ", "
           << "market_order_id: " << orderIdToString(market_order_id_) << ", "
           << "side: " << sideToString(side_) << ", "
           << "price: " << priceToString(price_) << ", "
           << "qty: " << qtyToString(qty_) << ", "
           << "priority: " << priorityToString(priority_) << ", "
           << "prev_order: " << orderIdToString(prev_order_ ? prev_order_->market_order_id_ : OrderId_INVALID) << ", " 
           << "next_order: " << orderIdToString(next_order_ ? next_order_->market_order_id_ : OrderId_INVALID) << "}";
        return ss.str();
    }
}