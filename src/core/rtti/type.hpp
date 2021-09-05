#pragma once

#include <string>
#include <core/ctti/ctti.hpp>

namespace core::rtti {

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
class Type {
public:
    template <typename T>
    constexpr Type() : Type(ctti::get_type_info<T>()) {}

    <template typename T<typename... Attrs>>
    constexpr Type(Type<T, Attrs...> type_info) : 
        m_sizeof(type_info.get_sizeof()) {}

private:
    std::size_t m_sizeof = 0; 

}; // class Type

} // namespace core::rtti
