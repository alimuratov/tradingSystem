#pragma once

#include <cstring>
#include <iostream>

#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)

inline auto ASSERT(bool condition, const std::string& message) noexcept {
    if (UNLIKELY(!condition)) {
        std::cerr << "ASSERT: " << message << std::endl;
        exit(EXIT_FAILURE);
    }
}

inline auto FATAL(const std::string& message) noexcept {
    std::cerr << "FATAL: " << message << std::endl;

    exit(EXIT_FAILURE);
}