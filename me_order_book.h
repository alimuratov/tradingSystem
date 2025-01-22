#pragma once

#include "types.h"
#include "mem_pool.h"
#include "logging.h"
#include "client_response.h"
#include "market_update.h"

#include "me_order.h"

using namespace Common;

namespace Exchange {
    class MatchingEngine; 

    // handles client order requests forwarded from the matching engine
    class MEOrderBook final {
    public:
        explicit MEOrderBook(TickerId ticker_id, Logger *logger, MatchingEngine *matching_engine);
        ~MEOrderBook();

        MEOrderBook() = delete;
        MEOrderBook(const MEOrderBook &) = delete;
        MEOrderBook(const MEOrderBook &&) = delete;
        MEOrderBook &operator=(const MEOrderBook &) = delete;
        MEOrderBook &operator=(const MEOrderBook &&) = delete;

    private:
        // to publish order responses and market data updates to
        MatchingEngine *matching_engine_ = nullptr;
        ClientOrderHashMap cid_oid_to_order_;

        MemPool<MEOrdersAtPrice> orders_at_price_pool_;
        MEOrdersAtPrice* bids_by_price_ = nullptr;
        MEOrdersAtPrice* asks_by_price_ = nullptr;

        OrdersAtPriceHashMap price_orders_at_price_;

        MemPool<MEOrder> order_pool_;

        // instrument for this order book
        TickerId ticker_id_ = TickerId_INVALID;
        OrderId next_market_order_id_ = 1;

        MEClientResponse client_response_;
        MEMarketUpdate market_update_;

        std::string time_str_;
        Logger *logger_ = nullptr;
        
    private:
        auto generateNewMarketOrderId() noexcept -> OrderId {
            return next_market_order_id_++;
        }

        auto getOrdersAtPrice(Price price) const noexcept -> MEOrdersAtPrice * {
            return price_orders_at_price_.at(priceToIndex(price));
        }

        auto priceToIndex(Price price) const noexcept {
        return (price % ME_MAX_PRICE_LEVELS);
        }

    }

    typedef std::array<MEOrderBook *, ME_MAX_TICKERS> OrderBookHashMap;
}