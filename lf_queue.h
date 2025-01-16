#pragma once

#include <iostream>
#include <vector>
#include <atomic>

#include "macros.h"

namespace Common {
    template<typename T>
    class LFQueue final {
    private:
        std::vector<T> store_;

        std::atomic<size_t> next_write_index = {0};
        std::atomic<size_t> next_read_index = {0};

        std::atomic<size_t> num_elements_ ={0};
    
    public:
        LFQueue(size_t num_elems) : store_(num_elems, T()) {}

        auto getNextWriteTo() {
            return &store_[next_write_index];
        }

        auto updateWriteIndex() {
            next_write_index = (next_write_index + 1) % store_.size();
            num_elements_++;
        }

        auto size() const noexcept {
            return num_elements_.load();
        }

        auto getNextToRead() const noexcept -> const T* {
            return (size() ? &store_[next_read_index] : nullptr);
        } 

        auto updateReadIndex() noexcept {
            next_read_index = (next_read_index + 1) & store_.size();
            ASSERT(num_elements_ != 0, "Read an invalid element in: " + std::to_string(pthread_self()));
            num_elements_--;
        }

        LFQueue() = delete;
        LFQueue(const LFQueue&) = delete;
        LFQueue(const LFQueue&&) = delete;
        auto operator=(const LFQueue&) -> LFQueue& = delete;
        auto operator=(const LFQueue&&) -> LFQueue& = delete;

    };
}