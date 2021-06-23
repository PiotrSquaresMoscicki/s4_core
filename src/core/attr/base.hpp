#pragma once

#include <core/ctti/ctti.hpp>

namespace core::attr {

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
template<typename... Bases>
class Base {
public:
    constexpr size_t size() const { return sizeof...(Bases); }

    template <typename T>
    constexpr bool has() const { return false; }

    // @todo implement get for templates 

    template <size_t idx = 0>
    constexpr auto get() const { return get_base_at<idx, Bases...>(); }

private:
    template <size_t idx, typename T, typename... Args>
    constexpr auto get_base_at() const
    {
        if constexpr (idx == 0)
            return ::core::ctti::get_type<T>();
        else
            return get_base_at<Args...>(idx - 1);
    }

}; // class Base

} // namespace core::attr 