#pragma once

#include <core/strings/constexpr_string.hpp>

namespace core::attr {

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
class Name : public ::core::ConstexprString
{
public:
    using ConstexprString::ConstexprString;

}; // class Name

} // namespace core::attr 