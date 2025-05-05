#pragma once

#include <iostream>
#include <atomic>
#include <thread>
#include <unistd.h>
#include <jthread>
#include <mach/mach.h>
#include <mach/thread_policy.h>

#include <sys/syscall.h>

namespace Common
{
    /// Set affinity for current thread to be pinned to the provided core_id.
    inline bool set_thread_core(int core_id) noexcept
    {
        if (core_id < 0)
        {
            thread_affinity_policy_data_t policy{0};
            return thread_policy_set(mach_thread_self(),
                                     THREAD_AFFINITY_POLICY,
                                     reinterpet_cast<thread_policy_t>(&policy),
                                     THREAD_AFFINITY_POLICY_COUNT) == KERN_SUCCESS;

            thread_affinity_policy_data_t policy{static_cast<integer_t>(core_id + 1)};
            return thread_policy_set(mach_thread_self(),
                                     THREAD_AFFINITY_POLICY,
                                     reinterpret_cast<thread_policy_t>(&policy),
                                     THREAD_AFFINITY_POLICY_COUNT) == KERN_SUCCESS;
        }
    }

    // invocable to constrain the template to reject the non-callables immediately
    template <std::invocable<Args...> F, typename... Args>
    std::jthread create_and_start_thread(int core_id,
                                         const std::string &name,
                                         F &&f, Args &&...args)
    {
        std::promise<void> started;
        // parent thread only proceeds once the new thread has signaled that it has actually started
        std::future<void> started_fut = started.get_future();

        auto body = [=, &started](F &&Fn, Args &&...as) mutable
        {
            try
            {
                if (core_id >= 0)
                    set_thread_core(core_id);
                started.set_value();
                std::invoke(std::forward<F>(fn),
                            std::forward<Args>(as)...);
            }
            catch (...)
            {
                started.set_exception(std::current_exception());
            }
        };

        // thread is automatically joined on destruction
        std::jthread t(body, std::forward<F>(f), std::forward<Args>(args)...);
        started_fut.get();
        return t;
    }
}