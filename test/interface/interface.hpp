#pragma once

#include <core/str/string_id.hpp>

namespace test {

    using namespace core::str;

    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    class ITestInterface {
    public:
        virtual ~ITestInterface() = default;

        virtual StringId register_string(const std::string& src) = 0;

    }; // class ITestInterface

} // namespace test